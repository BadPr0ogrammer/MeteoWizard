#pragma once

#include <vector>

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>

#include <opencv2/core/core.hpp>

#include "shaperead.h"
#include "region.h"
#include "wizparams.h";
#include "tpl.h"

class painter_c
{
public:
	QGraphicsScene *m_scene;
	QPainter* m_qp;
	QPixmap* m_pixmap;
	QImage* m_img;
	cv::Mat* m_rgb;
	wstring m_fname;

	painter_c() : m_scene(nullptr), m_qp(nullptr), m_pixmap(nullptr), m_img(nullptr), m_rgb(nullptr) {}
	~painter_c() {
		delete m_scene; delete m_qp; delete m_pixmap; delete m_img; delete m_rgb;
	}
	bool drawImage(const cv::Mat& mat);
};

class vpainter_c
{
public:
	vector<painter_c*> m_painter;
	~vpainter_c() {
		for (auto p : m_painter) delete p; 
	}
	bool drawShp(const std::vector<shp_c*>& shp_files, const ll_region_c& rect, double sx, double sy, cv::Size sz);
	bool drawUV(const calc_c& calc, const uv_c& uv, int step_x, int step_y, int dt_mn, cv::Size sz, const wiz_params_c& wizsum);
	void outputUV(const calc_c& calc, const uv_c& uv, const ll_region_c& ll_region, const std::vector<shp_c*>& shp_files, const wiz_params_c& wiz_params, int dt_mn, cv::Size sz);
};
