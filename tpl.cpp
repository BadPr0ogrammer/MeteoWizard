#include <Windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "supl.h"
#include "tpl.h"
#include "region.h"

using namespace cv;

void uv_c::rotateRpl(cv::Mat* tplb, cv::Mat* tpla, double a, double s, cv::Mat* tpl)
{
	float m[6];
	CvMat mat = cvMat(2, 3, CV_32F, m);
	m[4] = m[0] = (float)(s * cos(a));
	m[3] = -(m[1] = (float)(s * sin(a)));
	m[2] = (float)(tplb->cols / 2.);
	m[5] = (float)(tplb->cols / 2.);
	cvGetQuadrangleSubPix(tplb, tpla, &mat);

	if (tpl) {
		cv::Mat* roi = new cv::Mat((*tpla)(Rect((tpla->cols - tpl->cols) / 2, (tpla->rows - tpl->rows) / 2, tpl->cols, tpl->rows)));
		*tpl = roi->clone();

		delete roi;
	}
}

Point uv_c::tplMatch(cv::Mat& schi, cv::Mat& wini, const cv::Mat* prev, const cv::Mat* next, const Rect& sch, const calc_c& calc, cv::Mat* ret32)
{
	Point pt0, pt1, ret = { 0, 0 };
	int m_method = calc.m_method == 0 ? cv::TM_SQDIFF_NORMED : calc.m_method == 1 ? cv::TM_CCORR_NORMED : cv::TM_CCOEFF_NORMED;
	double thr = 0, mthr = 0;

	(*next)(sch).copyTo(schi);

	Rect rc(sch.x + sch.width / 2 - calc.m_tmplSz.width / 2, sch.y + sch.height / 2 - calc.m_tmplSz.height / 2, calc.m_tmplSz.width, calc.m_tmplSz.height);

	(*prev)(rc).copyTo(wini);

	matchTemplate(schi, wini, *ret32, m_method);

	GaussianBlur(*ret32, *ret32, Size(3, 3), 0);
	minMaxLoc(*ret32, &thr, &mthr, &pt0, &pt1);

	if (m_method == cv::TM_SQDIFF_NORMED) {
		ret.x = pt0.x - ret32->cols / 2;
		ret.y = pt0.y - ret32->rows / 2;
	}
	else {
		ret.x = pt1.x - ret32->cols / 2;
		ret.y = pt1.y - ret32->rows / 2;
	}

	if (calc.m_func) {
		if (m_method == cv::TM_SQDIFF_NORMED)
			*ret32 = *ret32 * (10. / (mthr - thr)) - 10. / (mthr - thr) * thr;
		else
			*ret32 = *ret32 * (1. / (mthr - thr)) - 1. / (mthr - thr) * thr;
	}
	return ret;
}

bool uv_c::tplMatchTpl(const cv::Mat* const prev_img, const cv::Mat* const cur_img, int step_x, int step_y, const calc_c& calc, cv::Mat** p_other)
{
	cv::Mat ret32(Size(calc.m_srchSz.width - calc.m_tmplSz.width + 1, calc.m_srchSz.height - calc.m_tmplSz.height + 1), CV_32FC1);

	cv::Mat* other = nullptr, * preprev = nullptr;
	if (calc.m_func && p_other) {
		*other = cur_img->clone();
		*p_other = other;
	}

	cv::Mat* rez = nullptr;

	int w0 = (int)(cur_img->cols / step_x) - 1;
	int h0 = (int)(cur_img->rows / step_y) - 1;

	m_u = new cv::Mat(h0, w0, CV_8UC1);
	m_v = new cv::Mat(h0, w0, CV_8UC1);

	if (!calc.m_rot) {
		m_rot = new cv::Mat(h0, w0, CV_32FC1);
	}

	int i, j;
	int w = cur_img->cols;
	int h = cur_img->rows;
	cv::Mat schi(calc.m_srchSz, CV_32FC1);
	cv::Mat wini(calc.m_tmplSz, CV_32FC1);

	ushort x, y;
	for (i = 0, y = calc.m_srchSz.height / 2; i < h0; i++, y += step_y) {
		for (j = 0, x = calc.m_srchSz.width / 2; j < w0; j++, x += step_x) {

			Rect rc(x - calc.m_srchSz.width / 2, y - calc.m_srchSz.height / 2, calc.m_srchSz.width, calc.m_srchSz.height);
			if (rc.x < 0 || rc.x + rc.width >= w || rc.y < 0 || rc.y + rc.height >= h)
				continue;

			Point d;
			float a = 0, s = 0;
			if (calc.m_rot == 0)
				d = tplMatch(schi, wini, prev_img, cur_img, rc, calc, &ret32);

			m_u->at<char>(i, j) = d.x;
			m_v->at<char>(i, j) = d.y;

			if (calc.m_rot) {
				m_rot->at<float>(i, j) = a;
			}
			if (calc.m_func && other) {
				Rect rc(x - ret32.cols / 2, y - ret32.rows / 2, ret32.cols, ret32.rows);
				(*other)(rc).copyTo(*rez);
			}
		}
	}	
	return true;
}
