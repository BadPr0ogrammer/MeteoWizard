#include <Windows.h>

#include <QColor>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "inc.h"
#include "supl.h"
#include "region.h"
#include "wizparams.h"
#include "shpproc.h"
#include "tpl.h"
#include "painter.h"

using namespace cv;

bool painter_c::drawImage(const cv::Mat& mat)
{
	m_rgb = new cv::Mat(mat.rows, mat.cols, CV_8UC3);
	if (mat.type() == CV_16UC1) {
		cv::Mat buf(mat.rows, mat.cols, CV_8UC1);
		mat.convertTo(buf, buf.type(), 0.25);
		cvtColor(buf, *m_rgb, cv::COLOR_GRAY2BGR);
	}
	else if (mat.type() == CV_8UC3)
		mat.copyTo(*m_rgb);
	else if (mat.type() == CV_32FC1) {
		cv::Mat buf(mat.rows, mat.cols, CV_8UC1);
		double d0, d1;
		minMaxLoc(mat, &d0, &d1);
		mat.convertTo(buf, buf.type(), 255 / (d1 - d0), -d0 * 255 / (d1 - d0));
		cv::Mat rgb(mat.rows, mat.cols, CV_8UC3);
		cvtColor(buf, rgb, cv::COLOR_GRAY2BGR);
		cv::Mat table(1, 256, CV_8UC3);
		for (int i = 0; i < 256; i++) {
			table.at<cv::Vec3b>(i)[0] = 255 - i; // B
			table.at<cv::Vec3b>(i)[1] = i; // G
			table.at<cv::Vec3b>(i)[2] = i; // R
		}
		cv::LUT(rgb, table, *m_rgb);
	}
	else 
		return false;
	
	m_img = new QImage(m_rgb->data, m_rgb->cols, m_rgb->rows, QImage::Format_RGB888);
	m_pixmap = new QPixmap();
	m_pixmap->convertFromImage(*m_img);

	m_qp = new QPainter(m_img);
	m_qp->setRenderHint(QPainter::Antialiasing);

	m_scene = new QGraphicsScene();
	m_scene->addPixmap(*m_pixmap);

	m_scene->render(m_qp);
	return true;
}

bool vpainter_c::drawShp(const vector<shp_c*>& shp_files, const ll_region_c& rect, double sx, double sy, cv::Size sz)
{
	for (int i = 0; i < shp_files.size(); i++)
	{
		shp_c* shp = shp_files[i];
		vector<QGraphicsItemGroup*> vgr = shp->renderShp(m_painter.size(), rect, sx, sy, sz);
		vector<QGraphicsItemGroup*>::iterator gr = vgr.begin();
		for (auto& pnt : m_painter) {
			QGraphicsItem* pgr = (QGraphicsItem*)*gr;
			pnt->m_scene->addItem(pgr);
			gr++;
		}
	}
	for (auto& pnt : m_painter)
		pnt->m_scene->render(pnt->m_qp);

	return true;
}

bool vpainter_c::drawUV(const calc_c& calc, const uv_c& uv, int step_x, int step_y, int dt_mn, cv::Size sz, const wiz_params_c& wizsum)
{
	QPen pen(wizsum.arrow_color);
	pen.setWidth(wizsum.arrow_width);
	for (auto& pnt : m_painter)
		pnt->m_qp->setPen(pen);

	for (int i = 0, y = calc.m_srchSz.height / 2; i < uv.m_u.rows; i++, y += step_y) {
		for (int j = 0, x = calc.m_srchSz.width / 2; j < uv.m_u.cols; j++, x += step_x) {
			int X = wizsum.arrow_scale * uv.m_u.at<char>(i, j);
			int Y = wizsum.arrow_scale * uv.m_v.at<char>(i, j);
			int x1 = x + X;
			int y1 = y + Y;
			double d = hypot(X, Y);
			double cs = X / d;
			double sn = Y / d;
			double x3 = x1 - 4 * (cs - sn);
			double y3 = y1 - 4 * (cs + sn);
			double x4 = x1 - 4 * (cs + sn);
			double y4 = y1 - 4 * (sn - cs);

			QVector<QPointF> vec;
			vec << QPointF(x, y) << QPointF(x1, y1);
			vec << QPointF(x3, y3) << QPointF(x1, y1);
			vec << QPointF(x4, y4) << QPointF(x1, y1);
			for (auto& pnt : m_painter)
				pnt->m_qp->drawLines(vec);
		}
	}
	{
		QPointF p0(sz.width - 100, sz.height - 30);
		QPointF p1(sz.width - 100 + 15 * 1855 / (dt_mn * 60) * wizsum.arrow_scale, sz.height - 30);
		QPen pen1(QColor(0, 255, 255));
		pen1.setWidth(6);
		for (auto& pnt : m_painter) {
			pnt->m_qp->setPen(pen1);
			pnt->m_qp->drawLine(p0, p1);
			pnt->m_qp->setPen(Qt::red);
			p1.setX(sz.width - 200);
			pnt->m_qp->setFont(QFont("Arial", 20));
			pnt->m_qp->drawText(p1, QString("15 m/c"));
		}
	}
	return true;
}

void vpainter_c::outputUV(const calc_c& calc, const uv_c& uv, const ll_region_c& ll_region, const std::vector<shp_c*>& shp_files, const wiz_params_c& wiz_params, int dt_mn, cv::Size sz)
{
	drawShp(shp_files, ll_region, LON_SCALE, LAT_SCALE, sz);
	drawUV(calc, uv, LON_SCALE * ll_region.m_ll_step, LAT_SCALE * ll_region.m_ll_step, dt_mn, sz, wiz_params);
}
