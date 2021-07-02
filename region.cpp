#include <Windows.h>

#include <iostream>
#include <string>

#include <QtCore>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MSG_navigation_v1.02.h"

#include "inc.h"
#include "region.h"

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

cv::Mat* ll_region_c::imgRemap(cv::Mat* ori)
{
	cv::Mat* img = new cv::Mat((int)(LAT_SCALE * m_height), (int)(LON_SCALE * m_width), CV_32FC1);
	bool init = false;
	if (!m_map_x)
	{
		m_map_x = new Mat_<float>(img->size());
		*m_map_x = 0;
		m_map_y = new Mat_<float>(img->size());
		*m_map_y = 0;

		init = true;
	}
	for (int i = 0; i < img->rows; i++) {
		for (int j = 0; j < img->cols; j++) {
			double x, y;
			double lon = m_x + j / LON_SCALE;
			double lat = m_y + m_height - i / LAT_SCALE;

			if (init)
			{
				if (!geocoord2pixcoord(lat, lon, &x, &y, 0)) {
					*((float*)m_map_x->data + j + i * img->cols) = (float)(MSAT_WIDTH - (x + m_rect.x));
					*((float*)m_map_y->data + j + i * img->cols) = (float)(MSAT_WIDTH - (y + m_rect.y));
				}
			}
		}
	}
	remap(*ori, *img, *m_map_x, *m_map_y, INTER_LINEAR);

	return img;
}
