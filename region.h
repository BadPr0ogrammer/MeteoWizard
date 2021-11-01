#pragma once

class ll_region_c
{
public:
	double m_x;
	double m_y;
	double m_width;
	double m_height;
	cv::Rect m_rect;
	cv::Mat* m_map_x;
	cv::Mat* m_map_y;
	float m_ll_step;

	ll_region_c() : m_x(0), m_y(0), m_width(0), m_height(0), m_rect(0, 0, 0, 0), m_ll_step(0), m_map_x(nullptr), m_map_y(nullptr) {}
	~ll_region_c() { delete m_map_x; delete m_map_y; }
	void geo2Rect();
	cv::Mat* imgRemap(cv::Mat& ori);
};
