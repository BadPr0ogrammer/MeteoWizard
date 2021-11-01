#include <Windows.h>

#include <iostream>
#include <string>

#include <QtCore>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MSG_navigation_v1.02.h"

#include "inc.h"
#include "region.h"
#include "supl.h"

using namespace std;
using namespace cv;

void ll_region_c::geo2Rect()
{
	double x_0 = MSAT_WIDTH, x_1 = 0, y_0 = MSAT_WIDTH, y_1 = 0;
	double lon, lat, x, y;
	for (lon = m_x; lon <= m_x + m_width; lon += 1 / LON_SCALE) {
		if (!geocoord2pixcoord(m_y, lon, &x, &y, 0)) {
			x = MSAT_WIDTH - x;
			y = MSAT_WIDTH - y;
			BOX_MIN_MAX(x, y, x_0, x_1, y_0, y_1);
		}
		if (!geocoord2pixcoord(m_y + m_height, lon, &x, &y, 0)) {
			x = MSAT_WIDTH - x;
			y = MSAT_WIDTH - y;
			BOX_MIN_MAX(x, y, x_0, x_1, y_0, y_1);
		}
	}
	for (lat = m_y; lat <= m_y + m_height; lat += 1 / LAT_SCALE) {
		if (!geocoord2pixcoord(lat, m_x, &x, &y, 0)) {
			x = MSAT_WIDTH - x;
			y = MSAT_WIDTH - y;
			BOX_MIN_MAX(x, y, x_0, x_1, y_0, y_1);
		}
		if (!geocoord2pixcoord(lat, m_x + m_width, &x, &y, 0)) {
			x = MSAT_WIDTH - x;
			y = MSAT_WIDTH - y;
			BOX_MIN_MAX(x, y, x_0, x_1, y_0, y_1);
		}
	}

	int w = (int)MAX(4, x_1 - x_0);
	int h = (int)MAX(4, y_1 - y_0);
	w = 4 * ((w + 3) / 4);

	//??return cvRect(x_1, y_1, w, h);
	m_rect = Rect((int)x_0, (int)y_0, w, h);
}

cv::Mat* ll_region_c::imgRemap(cv::Mat& ori)
{
	bool init = false;
	cv::Mat* ret = new cv::Mat((int)(LAT_SCALE * m_height), (int)(LON_SCALE * m_width), ori.type());
	if (!m_map_x || m_map_x->cols == 0 || m_map_x->rows == 0
		|| m_map_x->cols != ret->cols || m_map_x->rows != ret->rows) {
		m_map_x = new cv::Mat(ret->rows, ret->cols, CV_32FC1);
		m_map_x->setTo(0);
		m_map_y = new cv::Mat(ret->rows, ret->cols, CV_32FC1);
		m_map_y->setTo(0);
		init = true;
	}
	if (init) {
		for (int i = 0; i < ret->rows; i++) {
			for (int j = 0; j < ret->cols; j++) {
				double x, y;
				double lon = m_x + j / LON_SCALE;
				double lat = m_y + m_height - i / LAT_SCALE;
				if (!geocoord2pixcoord(lat, lon, &x, &y, 0)) {
					float x0 = (float)(MSAT_WIDTH - (x + m_rect.x));
					float y0 = (float)(MSAT_WIDTH - (y + m_rect.y));
					x0 = MAX(0, MIN(ret->cols - 1, x0));
					y0 = MAX(0, MIN(ret->rows - 1, y0));
					*((float*)m_map_x->data + j + i * ret->cols) = x0;
					*((float*)m_map_y->data + j + i * ret->cols) = y0;
				}
			}
		}
	}
	remap(ori, *ret, *m_map_x, *m_map_y, INTER_AREA);
	return ret;
}
