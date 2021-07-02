#pragma once

#include <vector>

class QImage;
class QPixmap;
class QGraphicsScene;
class QPainter;

class shp_c;
class ll_region_c;
class Mat;
class wiz_params_c;

class painter_c
{
public:
	QGraphicsScene* m_scene;
	QPixmap* m_pixmap;
	QImage* m_img;
	QPainter* m_qp;
	cv::Mat* m_rgb;

	painter_c() : m_scene(nullptr), m_pixmap(nullptr), m_img(nullptr), m_qp(nullptr), m_rgb(nullptr) {}
	bool drawImage(const cv::Mat* mat);
	bool drawShp(const std::vector<shp_c*>* const shp_files, const ll_region_c* const rect, double sx, double sy, const cv::Mat* const mat);
	bool drawUV(cv::Mat* f0, cv::Mat* f1, int step_x, int step_y, int dt_mn, int width, int height, const wiz_params_c& wizsum);
};
