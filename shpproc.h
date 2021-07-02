#pragma once

#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>

#include "inc.h"

class shape_c;
class ll_region_c;
class Mat;

class QGraphicsItemGroup;

class shp_c
{
public:
	QString						m_dbf_field;//vector<pair<string, int>>   
	QString                     m_shp_name;
	QColor						m_line_color;
	QColor						m_text_color;
	float						m_line_width;
	int							m_dash;
	QString						m_font_face;
	int							m_font_size;

	vector<shape_c*>* m_shape;

	shp_c() : m_shape(nullptr),m_dbf_field(DEF_DBF_PLS_PARAM), m_line_width(1), m_dash(0), m_font_size(10), m_font_face("Arial") {}
	
	~shp_c();

	QGraphicsItemGroup* renderShp(const ll_region_c* const rect, double sx, double sy, const cv::Mat* const mat);
	static shp_c* shpProc(QString name, const ll_region_c* const rc);
};
Q_DECLARE_METATYPE(shp_c);
