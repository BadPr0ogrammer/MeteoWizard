#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <list>

#include "inc.h"
#include "supl.h"

#include "atmrad.h"
#include "region.h"

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/*
						  VIS006    VIS008    IR_016    IR_039    WV_062   WV_073    IR_087  IR_097   IR_108     IR_120     IR_134
*/
const double NUCW[T_13_4] = { 0,        0,        0,        2569.09,  1598.57,  1362.14,  1149.08, /*1034.35,*/  930.66,   839.66,    752.38 };
const double BIAS[T_13_4] = { 0,        0,        0,        3.471,    2.219,    0.485,    0.181,   /*0.060,*/    0.627,    0.397,     0.576 };
const double SLOP[T_13_4] = { 0.02295,  0.02922,  0.02328,  0.00366,  0.0083,   0.03862,  0.12674, /*0.10396,*/  0.20503,  0.22231,   0.15761 };
const double OFFS[T_13_4] = { -1.17046, -1.49001, -1.18724, -0.18659, -0.42422, -1.96972, -6.46392, /*-5.30202,*/ -10.45676,-11.33788, -8.03795 };

void AtmradGetTb(cv::Mat* v, int dt, cv::Mat* watt)
{
	if (dt <= T_12_0) {
		const double C1 = 1.19104e-5;
		const double C2 = 1.43877;

		int i = dt - 1;
		double nucw = NUCW[i];

		v->convertTo(*watt, watt->type(), SLOP[i], OFFS[i]);
		cv::divide(C1 * nucw * nucw * nucw, *watt, *watt);
		*watt += cv::Scalar(1);
		cv::log(*watt, *watt);
		cv::divide(C2 * nucw, *watt, *watt);
		*watt += cv::Scalar(-BIAS[i]);
	}
	else {
		printf("%s:%d", __FILE__, __LINE__);
	}
}

void Gamma(cv::Mat* src, cv::Mat* dst, double gamma)
{
	int i;
	uchar table[256];
	cv::Mat m(1, 256, CV_8UC1, table);

	for (i = 0; i < 256; i++)
		table[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);

	cv::LUT(*src, m, *dst);
}

cv::Mat* AtmradMakeDif(slot_c* src, double* thresh, int* chnls)
{
	cv::Mat* map = NULL;
	int ret = FALSE;
	int w = src->m_img[chnls[0]]->cols;
	int h = src->m_img[chnls[0]]->rows;

	cv::Mat tmp[4] = { cv::Mat(h, w, CV_8UC1), cv::Mat(h, w, CV_8UC1), cv::Mat(h, w, CV_8UC1), cv::Mat(h, w, CV_8UC1) };
	cv::Mat* rgb = new cv::Mat(h, w, CV_8UC4);
	cv::Mat tmp32(h, w, CV_32F), b32(h, w, CV_32F);
	tmp[3] = 255;
	if (!rgb)
		goto end;
	{
		for (int i = 0; i < 3; i++) {
			double min0 = thresh[3 * i];
			double max0 = thresh[3 * i + 1];
			double gamma = thresh[3 * i + 2];
			int t1 = chnls[2 * i];
			int t2 = chnls[2 * i + 1];
			int inv = FALSE;
			if (min0 > max0) {
				double m = min0;
				min0 = max0;
				max0 = m;
				inv = TRUE;
			}
			if (!src->m_img[t1])
				goto end;

			if (t1 > T_01_6) // && t1 != T_HRV)
				AtmradGetTb(src->m_img[t1], t1, &tmp32);
			else
				src->m_img[t1]->convertTo(tmp32, CV_32F);

			if (t2 != T_NONE) {
				AtmradGetTb(src->m_img[t2], t2, &b32);
				tmp32 -= b32;
			}
			if (max0 < 1000)
				tmp32.convertTo(tmp[i], CV_8UC1, 255. / (max0 - min0), -255. / (max0 - min0) * min0);
			else {
				double m0, m1, x0, x1;
				cv::minMaxLoc(tmp32, &m0, &m1);
				x0 = m0 + (m1 - m0) * min0 / 10000;
				x1 = m0 + (m1 - m0) * max0 / 10000;
				tmp32.convertTo(tmp[i], CV_8UC1, 255. / (x1 - x0), -255. / (x1 - x0) * x0);
			}
			if (inv)
				cv::bitwise_not(tmp[i], tmp[i]);
			if (gamma != 1.0)
				Gamma(&tmp[i], &tmp[i], gamma);
		}

		cv::merge(tmp, 4, *rgb);
		ret = TRUE;
	}
end:
	if (!ret) {
		delete rgb;
		printf("%s:%d", __FILE__, __LINE__);
		return NULL;
	}
	return rgb;
}
