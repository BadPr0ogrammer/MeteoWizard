#pragma once

class Mat;

class calc_c
{
public:
	cv::Size m_tmplSz;
	cv::Size m_srchSz;
	int m_phi, m_method;
	bool m_rot;
	double m_da;

	calc_c() : m_tmplSz(0, 0), m_srchSz(0, 0), m_phi(0), m_method(0), m_rot(false), m_da(0) { }
};

class uv_c
{
public:
	cv::Mat m_u;
	cv::Mat m_v;
	cv::Mat_<float> *m_rot;
	cv::Mat_<float> *m_kdif;
	uv_c() : m_rot(nullptr), m_kdif(nullptr) {}
	~uv_c() { delete m_rot; delete m_kdif; }

	static void rotateTpl(const cv::Mat& tplb, cv::Mat& tpla, double a, double s, cv::Mat& tpl);
	static cv::Point tplMatch(cv::Mat& schi, cv::Mat& wini, cv::Mat* prev, cv::Mat* next, const cv::Rect& sch, const calc_c& calc);

	void tplMatchTpl(cv::Mat* prev_img, cv::Mat* cur_img, int step_x, int step_y, const calc_c& calc);
	cv::Point tplMatchRot(cv::Mat* prev, cv::Mat* next, cv::Rect sch, const calc_c& calc, double& ang, double& scale);
};
