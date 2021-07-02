#include <Windows.h>

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "inc.h"
#include "supl.h"
#include "region.h"
#include "shpproc.h"
#include "tpl.h"
#include "painter.h"
#include "wizparams.h"

using namespace cv;

bool painter_c::drawImage(const cv::Mat* mat)
{
    m_rgb = new cv::Mat(mat->rows, mat->cols, CV_8UC3);
    {
        cv::Mat* buf = new cv::Mat(mat->rows, mat->cols, CV_8UC1);
        convertScaleAbs(*mat, *buf, 0.25);
        cvtColor(*buf, *m_rgb, cv::COLOR_GRAY2BGR);

        delete buf;
    }

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

bool painter_c::drawShp(const vector<shp_c*>* const shp_files, const ll_region_c* const rect, double sx, double sy, const cv::Mat* const mat)
{
    for (int i = 0; i < shp_files->size(); i++)
    {
        shp_c *shp = (*shp_files)[i];
        QGraphicsItemGroup* gr = shp->renderShp(rect, sx, sy, mat);
        m_scene->addItem((QGraphicsItem *)gr);
    }
    m_scene->render(m_qp);

    return true;
}

bool painter_c::drawUV(cv::Mat* f0, cv::Mat* f1, int step_x, int step_y, int dt_mn, int width, int height, const wiz_params_c& wizsum)
{
    uv_c* uv = new uv_c();
    calc_c calc;
    calc.m_tmplSz = Size(32, 32);
    calc.m_srchSz = Size(64, 64);

    uv->tplMatchTpl(f0, f1, step_x, step_y, calc, nullptr);

    QPen pen(wizsum.arrow_color);
    pen.setWidth(wizsum.arrow_width);
    m_qp->setPen(pen);

    for (int i = 0, y = calc.m_srchSz.height / 2; i < uv->m_u->rows; i++, y += step_y) {
        for (int j = 0, x = calc.m_srchSz.width / 2; j < uv->m_u->cols; j++, x += step_x) {
            int X = wizsum.arrow_scale * uv->m_u->at<char>(i, j);
            int Y = wizsum.arrow_scale * uv->m_v->at<char>(i, j);
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
            m_qp->drawLines(vec);
        }
    }
    {
        // карта строится в масштабе 1/LON_SCALE = 1/60
        // 1 пиксель = 1 минуте
        // 1 минута = CV_PI / 180 / 60
        // 1 минута в метрах = CV_PI / 180 / 60 * 6378169 = 1855 м
        // скорость = метр / сек = 1855 / (dt_mn * 60)
        // рисуем отрезок 15 метров / секунду        
        QPointF p0(width - 100, height - 30);
        QPointF p1(width - 100 + 15 * 1855 / (dt_mn * 60) * wizsum.arrow_scale, height - 30);
        QPen pen1(QColor(0, 255, 255));
        pen1.setWidth(6);
        m_qp->setPen(pen1);
        m_qp->drawLine(p0, p1);
        m_qp->setPen(Qt::red);
        p1.setX(width - 200);
        m_qp->setFont(QFont("Arial", 20));
        m_qp->drawText(p1, QString("15 m/c"));
    }
    delete uv;

    return true;
}