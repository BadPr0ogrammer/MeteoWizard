#include <Windows.h>

#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include <QtGui>
#include <QGraphicsItemGroup>

#include "inc.h"
#include "supl.h"
#include "region.h"
#include "shaperead.h"
#include "shpproc.h"

#include "MSG_navigation_v1.02.h"

shp_c::~shp_c() 
{
	if (m_shape) {
		for (int i = 0; i < m_shape->size(); i++)
			delete (*m_shape)[i];
		delete m_shape;
	}
}

shp_c* shp_c::shpProc(QString name, const ll_region_c* const rc)
{
	shp_c* sf = new shp_c();
	sf->m_shp_name = name;

	if (sf->m_shape = shape_c::shapeLoad(name, 4, 26, 0))// && sf->clipShp(rc, false)
	{
		return sf;
	}
	delete sf;
	return nullptr;
}

vector<QGraphicsItemGroup*> shp_c::renderShp(int num, const ll_region_c* const rect, double scaleX, double scaleY, cv::Size sz)
{
	vector<QGraphicsItemGroup*> group;
	for (int i = 0; i < num; i++)
		group.push_back(new QGraphicsItemGroup());

	//if (!m_clip || !m_clip->size())
		//return nullptr;
	const shape_c* parts = m_shape->at(0);// m_clip->at(0);
	QString font_face = m_font_face.isEmpty() ? QString("Arial") : m_font_face;
	int font_size = m_font_size < 9 || m_font_size > 24 ? 10 : m_font_size;
	QFont font1(font_face, font_size);
	QFont font2(font_face, 1.25 * font_size);
	QFont font3(font_face, 1.75 * font_size);
	QFontMetrics fm1(font1);
	QFontMetrics fm2(font2);
	QFontMetrics fm3(font3);
	QFontMetrics& pfm = parts->m_popul < 1E5 ? fm1 : parts->m_popul < 1E6 ? fm2 : fm3;

	for (int i = 0; i < m_shape->size(); i++) {//m_clip->size()
		const shape_c* parts = m_shape->at(i);
		if (!parts->m_pline->size()) {
			continue;
		}

		QPointF pt1{ 987654321, 0 };
		for (int j = 0; j < parts->m_pline->size(); j++)
		{
			QVector<QPointF> *tmp = new QVector<QPointF>();
			vector<Point2f> *cnt = (*parts->m_pline)[j];
			for (int k = 0; k < cnt->size(); k++)
			{
				Point2f &pt = (*cnt)[k];
				double x = scaleX * (pt.x - rect->m_x);
				double y = scaleY * (rect->m_y + rect->m_height - pt.y);
				if (x >= 0 && x <= sz.width- 1 &&
					y >= 0 && y <= sz.height - 1) {
					pt1 = QPointF(x, y);
					tmp->append(pt1);
				}
			}
			if (tmp->size()) {
				QPolygonF* poly = new QPolygonF(*tmp);
				QPainterPath* path = new QPainterPath();
				path->addPolygon(*poly);
				
				for (int ii = 0; ii < num; ii++) {
					QGraphicsPathItem* item = new QGraphicsPathItem(*path);

					QPen pen(m_line_color);
					pen.setWidth(m_line_width);
					item->setPen(pen);
					group[ii]->addToGroup(item);
				}
			}
		}
	
		if (!parts->m_lab.isEmpty() && pt1.x() != 987654321) {
			//if (pfm.width(shp->lab()) < w - pt1.x() && pfm.height() < h - pt1.y()) {
			for (int ii = 0; ii < num; ii++) {
				QGraphicsTextItem* item = new QGraphicsTextItem(parts->m_lab);
				item->setPos(pt1.x(), pt1.y() - pfm.height());
				item->setDefaultTextColor(m_text_color);
				item->setFont(parts->m_popul < 1E5 ? font1 : parts->m_popul < 1E6 ? font2 : font3);
				group[ii]->addToGroup(item);
			}
		}
	}
	return group;
}

