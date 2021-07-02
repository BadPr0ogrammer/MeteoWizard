#pragma once

class Mat;

class calc_c
{
public:
	cv::Size m_tmplSz;
	cv::Size m_srchSz;
	int m_phi, m_func, m_method, m_rot;
	float m_da;

	calc_c() : m_tmplSz(0, 0), m_srchSz(0, 0), m_phi(0), m_func(0), m_method(0), m_rot(0), m_da(0) { }
};

class uv_c
{
public:
	cv::Mat* m_u;
	cv::Mat* m_v;
	cv::Mat* m_rot;

	uv_c() : m_u(nullptr), m_v(nullptr), m_rot(nullptr) {}

	static void rotateRpl(cv::Mat* tplb, cv::Mat* tpla, double a, double s, cv::Mat* tpl);
	static cv::Point tplMatch(cv::Mat& schi, cv::Mat& wini, const cv::Mat* prev, const cv::Mat* next, const cv::Rect& sch, const calc_c& calc, cv::Mat* ret32);
	bool tplMatchTpl(const cv::Mat* const prev_img, const cv::Mat* const cur_img, int step_x, int step_y, const calc_c& calc, cv::Mat** p_other);
};
