#include <Windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "supl.h"
#include "tpl.h"
#include "region.h"

using namespace cv;
using namespace std;

void uv_c::rotateTpl(const cv::Mat& tplb, cv::Mat& tpla, double a, double s, cv::Mat& tpl)
{
	Point2f center(tplb.cols / 2.f, tplb.rows / 2.f);
	cv::Mat rot = getRotationMatrix2D(center, a, s);
	warpAffine(tplb, tpla, rot, tplb.size());

	cv::Mat roi(tpla(Rect((tpla.cols - tpl.cols) / 2, (tpla.rows - tpl.rows) / 2, tpl.cols, tpl.rows)));
	tpl = roi.clone();
}

Point uv_c::tplMatch(cv::Mat& schi, cv::Mat& wini, cv::Mat* prev, cv::Mat* next, const Rect& sch, const calc_c& calc)
{
	cv::Mat ret32(Size(calc.m_srchSz.width - calc.m_tmplSz.width + 1,
		calc.m_srchSz.height - calc.m_tmplSz.height + 1), CV_32FC1);

	Point pt0, pt1, ret = { 0, 0 };
	int method = calc.m_method == 0 ? TM_SQDIFF_NORMED : calc.m_method == 1 ? TM_CCORR_NORMED : TM_CCOEFF_NORMED;
	double thr = 0, mthr = 0;

	(*next)(sch).copyTo(schi);

	Rect rc(sch.x + sch.width / 2 - calc.m_tmplSz.width / 2,
		sch.y + sch.height / 2 - calc.m_tmplSz.height / 2,
		calc.m_tmplSz.width, calc.m_tmplSz.height);

	(*prev)(rc).copyTo(wini);

	matchTemplate(schi, wini, ret32, method);

	blur(ret32, ret32, Size(3, 3));
	minMaxLoc(ret32, &thr, &mthr, &pt0, &pt1);

	if (method == TM_SQDIFF_NORMED) {
		ret.x = pt0.x - ret32.cols / 2;
		ret.y = pt0.y - ret32.rows / 2;
	}
	else {
		ret.x = pt1.x - ret32.cols / 2;
		ret.y = pt1.y - ret32.rows / 2;
	}
	return ret;
}

void uv_c::tplMatchTpl(cv::Mat* prev_img, cv::Mat* cur_img, int step_x, int step_y, 
	const calc_c& calc)
{
	int w0 = (int)(cur_img->cols / step_x) - 1;
	int h0 = (int)(cur_img->rows / step_y) - 1;

	m_u = cv::Mat(h0, w0, CV_8UC1);
	m_v = cv::Mat(h0, w0, CV_8UC1);

	if (calc.m_rot) {
		m_rot = new cv::Mat_<float>(h0, w0);
		m_rot->setTo(0);
		m_kdif = new cv::Mat_<float>(h0, w0);
		m_kdif->setTo(0);
	}

	int i, j;
	int w = cur_img->cols;
	int h = cur_img->rows;
	cv::Mat schi(calc.m_srchSz, CV_32FC1);
	cv::Mat wini(calc.m_tmplSz, CV_32FC1);
	
	ushort x, y;
	for (i = 0, y = calc.m_srchSz.height / 2; i < h0; i++, y += step_y) 
	//i = 10; y = calc.m_srchSz.height / 2 + 10 * step_y;
	{
		for (j = 0, x = calc.m_srchSz.width / 2; j < w0; j++, x += step_x) 
		//j = 10; x = calc.m_srchSz.width / 2 + 10 * step_x;
		{

			Rect rc(x - calc.m_srchSz.width / 2, y - calc.m_srchSz.height / 2, calc.m_srchSz.width, calc.m_srchSz.height);
			if (rc.x >= 0 && rc.x + rc.width < w && rc.y >= 0 && rc.y + rc.height < h) {

				Point d;
				double a = 0, s = 0;
				if (!calc.m_rot)
					d = tplMatch(schi, wini, prev_img, cur_img, rc, calc);
				else
					d = tplMatchRot(prev_img, cur_img, rc, calc, a, s);

				m_u.at<char>(i, j) = d.x;
				m_v.at<char>(i, j) = d.y;

				if (calc.m_rot) {
					m_rot->at<float>(i, j) = a;
					m_kdif->at<float>(i, j) = s;
				}
			}
		}
	}
	if (calc.m_rot) {
		cv::Mat_<float> tmp = m_rot->clone();
		delete m_rot;
		m_rot = new cv::Mat_<float>(cur_img->size());
		resize(tmp, *m_rot, m_rot->size());

		cv::Mat_<float> tmp1 = m_kdif->clone();
		delete m_kdif;
		m_kdif = new cv::Mat_<float>(cur_img->size());
		resize(tmp1, *m_kdif, m_kdif->size());
	}
}

cv::Point uv_c::tplMatchRot(cv::Mat* prev, cv::Mat* next, Rect sch, const calc_c& calc, double& ang, double& scale)
{
	Point ret = { 0, 0 };
	Point pt0, pt1;
	double thr = FLT_MAX, mthr = 0;
	double thr0, mthr0;
	float a = 0;
	Rect rc0, rc1, rc;
	int d = (int)hypot((double)calc.m_tmplSz.width, (double)calc.m_tmplSz.height);
	int method = calc.m_method == 0 ? TM_SQDIFF_NORMED : calc.m_method == 1 ? TM_CCORR_NORMED : TM_CCOEFF_NORMED;

	cv::Mat ret32(Size(calc.m_srchSz.width - calc.m_tmplSz.width + 1,
		calc.m_srchSz.height - calc.m_tmplSz.height + 1), CV_32FC1);
	cv::Mat bit(ret32.size(), CV_8UC1);
	cv::Mat schi(Size(sch.width, sch.height), CV_32FC1);
	cv::Mat tmpl(calc.m_tmplSz, CV_32FC1);
	cv::Mat tplb(Size(d, d), CV_32FC1);
	cv::Mat tpla(Size(d, d), CV_32FC1);

	(*next)(sch).copyTo(schi);

	rc0 = Rect(sch.x + sch.width / 2 - d / 2, sch.y + sch.height / 2 - d / 2, d, d);
	(*prev)(rc0).copyTo(tplb);

	rc1 = Rect(sch.x + sch.width / 2 - calc.m_tmplSz.width / 2, sch.y + sch.height / 2 - calc.m_tmplSz.height / 2, calc.m_tmplSz.width, calc.m_tmplSz.height);
	(*prev)(rc1).copyTo(tmpl);

	matchTemplate(schi, tmpl, ret32, method);
	blur(ret32, ret32, Size(3, 3));
	minMaxLoc(ret32, &thr, &mthr);
	if (method == TM_SQDIFF_NORMED)
		cv::compare(ret32, 1.2*thr, bit, CMP_LE);
	else
		cv::compare(ret32, 0.8*mthr, bit, CMP_GE);
	scale = cv::countNonZero(bit);
	
	rotateTpl(tplb, tpla, 0.1, 1, tmpl);
	
	matchTemplate(schi, tmpl, ret32, method);
	blur(ret32, ret32, Size(3, 3));
	minMaxLoc(ret32, &thr, &mthr);
	
	for (float a0 = -calc.m_phi; a0 <= calc.m_phi; a0 += calc.m_da) {
		rotateTpl(tplb, tpla, a0, 1, tmpl);

		matchTemplate(schi, tmpl, ret32, method);
		blur(ret32, ret32, Size(3, 3));
		minMaxLoc(ret32, &thr0, &mthr0);

		if (method == TM_SQDIFF_NORMED && thr0 < thr || method != TM_SQDIFF_NORMED && mthr0 > mthr) {
			a = a0;
			thr = thr0;
			mthr = mthr0;
		}
	}
	if (fabs(a) <= FLT_EPSILON)
		a = 0;
	ang = a;

	if (a != 0)
		rotateTpl(tplb, tpla, a, 1, tmpl);
	else {
		rc = Rect(sch.x + sch.width / 2 - calc.m_tmplSz.width / 2,
			sch.y + sch.height / 2 - calc.m_tmplSz.height / 2, calc.m_tmplSz.width, calc.m_tmplSz.height);
		(*prev)(rc).copyTo(tmpl);
	}

	matchTemplate(schi, tmpl, ret32, method);
	blur(ret32, ret32, Size(3, 3));	
	minMaxLoc(ret32, &thr, &mthr, &pt0, &pt1);

	if (method == TM_SQDIFF_NORMED) {
		ret.x = pt0.x - ret32.cols / 2;
		ret.y = pt0.y - ret32.rows / 2;
	}
	else {
		ret.x = pt1.x - ret32.cols / 2;
		ret.y = pt1.y - ret32.rows / 2;
	}
		
	return ret;
}
