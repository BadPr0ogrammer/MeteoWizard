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
	QPainter* m_qp;
	QPixmap* m_pixmap;
	QImage* m_img;
	cv::Mat* m_rgb;

	painter_c() :  m_scene(nullptr), m_qp(nullptr), m_pixmap(nullptr), m_img(nullptr), m_rgb(nullptr) {}
	~painter_c() { 
		delete m_scene;  
		delete m_qp;
		delete m_pixmap;    
		delete m_img;   
		delete m_rgb; 
	}
	bool drawImage(const cv::Mat* mat);
};

class vpainter_c
{
public:
	vector<painter_c*> m_painter;
	~vpainter_c() { for (auto p : m_painter) delete p; }

	bool drawShp(const std::vector<shp_c*>* const shp_files, const ll_region_c* const rect, double sx, double sy, cv::Size sz);
	bool drawUV(cv::Mat* f0, cv::Mat* f1, int step_x, int step_y, int dt_mn, int width, int height, const wiz_params_c& wizsum);
	void outputUV(ll_region_c* ll_region, const std::vector<shp_c*>* shp_files, wiz_params_c* wiz_params, int dt_mn, cv::Mat* img0, cv::Mat* img1);
};
