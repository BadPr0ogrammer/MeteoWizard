#pragma once

#include <QString>
#include <QColor>
#include "datec.h"

class shp_c;

class wiz_params_c
{
public:
	QString msg_path, jpg_path, shp_path, fname_pref, working_dir;
	double arrow_scale, arrow_width;
	QColor arrow_color;
	int msg;
	int channel_idx;
	date_c start, stop;

	wiz_params_c() : arrow_scale(1), arrow_width(1), msg(4), channel_idx(0) {};

	bool write_settings(const wiz_params_c& wiz, const std::vector<shp_c*>& shp_files, const QString& fname);
	bool read_settings(wiz_params_c& wiz, std::vector<shp_c*>& shp_files, const QString& fname);
};

