#pragma once

#include <QString>
#include <QColor>
#include "datec.h"
#include "inc.h"

class shp_c;
class ll_region_c;

class wiz_params_c
{
public:
	QString msg_path, jpg_path, shp_path, fname_pref, working_dir;
	double arrow_scale, arrow_width;
	QColor arrow_color;
	int msg;
	int channel_idx;
	date_c start, stop;
	bool rgb;
	double rgb_params[RGB_PRESET_NUM][9];
	int rgb_channels[RGB_PRESET_NUM][6];

	wiz_params_c() : arrow_scale(1), arrow_width(1), msg(4), channel_idx(0), rgb(false) {
		memset(rgb_params, 0, sizeof(rgb_params));
		memset(rgb_channels, 0, sizeof(rgb_channels));
	};

	bool write_settings(const wiz_params_c& wiz, ll_region_c* rg, const std::vector<shp_c*>& shp_files, const QString& fname);
	bool read_settings(wiz_params_c& wiz, ll_region_c* rg, std::vector<shp_c*>& shp_files, const QString& fname);
};

