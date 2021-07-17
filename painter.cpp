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
#include "region.h"

using namespace cv;

bool painter_c::drawImage(const cv::Mat* mat)
{
    m_rgb = new cv::Mat(mat->rows, mat->cols, CV_8UC3);
    if (mat->type() == CV_16UC1) {
        cv::Mat* buf = new cv::Mat(mat->rows, mat->cols, CV_8UC1);
        convertScaleAbs(*mat, *buf, 0.25);
        cvtColor(*buf, *m_rgb, cv::COLOR_GRAY2BGR);

        delete buf;
    }
    else if (mat->type() == CV_8UC3)
        mat->copyTo(*m_rgb);
    else {
        delete m_rgb;
        m_rgb = nullptr;
        return false;
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

bool vpainter_c::drawShp(const vector<shp_c*>* const shp_files, const ll_region_c* const rect, double sx, double sy, cv::Size sz)
{
    for (int i = 0; i < shp_files->size(); i++)
    {
        shp_c *shp = (*shp_files)[i];
        vector<QGraphicsItemGroup*> vgr = shp->renderShp(m_painter.size(), rect, sx, sy, sz);
        vector<QGraphicsItemGroup*>::iterator gr = vgr.begin();
        for (auto pnt : m_painter) {
            QGraphicsItem* pgr = (QGraphicsItem*)*gr;
            pnt->m_scene->addItem(pgr);
            gr++;
        }
    }
    for (auto pnt : m_painter) 
        pnt->m_scene->render(pnt->m_qp);

    return true;
}

bool vpainter_c::drawUV(cv::Mat* f0, cv::Mat* f1, int step_x, int step_y, int dt_mn, int width, int height, const wiz_params_c& wizsum)
{
    uv_c* uv = new uv_c();
    calc_c calc;
    calc.m_tmplSz = Size(32, 32);
    calc.m_srchSz = Size(64, 64);

    uv->tplMatchTpl(f0, f1, step_x, step_y, calc, nullptr);

    QPen pen(wizsum.arrow_color);
    pen.setWidth(wizsum.arrow_width);
    for (auto pnt : m_painter)
        pnt->m_qp->setPen(pen);

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
            for (auto pnt : m_painter)
                pnt->m_qp->drawLines(vec);
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
        for (auto pnt : m_painter) {            
            pnt->m_qp->setPen(pen1);
            pnt->m_qp->drawLine(p0, p1);
            pnt->m_qp->setPen(Qt::red);
            p1.setX(width - 200);
            pnt->m_qp->setFont(QFont("Arial", 20));
            pnt->m_qp->drawText(p1, QString("15 m/c"));
        }
    }
    delete uv;

    return true;
}

void vpainter_c::outputUV(ll_region_c* ll_region, const std::vector<shp_c*>* shp_files, wiz_params_c* wiz_params, int dt_mn, cv::Mat* img0, cv::Mat* img1)
{
    SuplDebugMat(img0);

    drawShp(shp_files, ll_region, LON_SCALE, LAT_SCALE, cv::Size(img0->cols, img0->rows));

    Mat_<float>* f0 = new Mat_<float>(img0->rows, img0->cols);
    Mat_<float>* f1 = new Mat_<float>(img1->rows, img1->cols);
    *f0 = *img0 * (1. / 1024);
    *f1 = *img1 * (1. / 1024);

    drawUV(f0, f1, LON_SCALE * ll_region->m_ll_step, LAT_SCALE * ll_region->m_ll_step, dt_mn, img0->cols, img0->rows, *wiz_params);
    delete f0;
    delete f1;
}
