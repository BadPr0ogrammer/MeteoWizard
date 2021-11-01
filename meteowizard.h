#pragma once

#include <vector>
#include <QtWidgets>
#include <QQuickWidget>
#include <opencv2/core/core.hpp>

#include "inc.h"
#include "region.h"
#include "wizparams.h"

class date_c;
class shp_c;
class SelectColorButton;
//class ModelRender;
class palettes_c;

class params_channels_c : QObject {
public:
	int channels[6];
	double params[9];

	params_channels_c() : channels{ 0,0,0,0,0,0 }, params{ 0,0,0,0,0,0,0,0,0 } {}
	params_channels_c(int(chn)[6], double(par)[9]) { memcpy(channels, chn, sizeof(channels)); memcpy(params, par, sizeof(params));}
	params_channels_c(const params_channels_c& obj) { memcpy(channels, obj.channels, sizeof(channels)); memcpy(params, obj.params, sizeof(params)); }
};
Q_DECLARE_METATYPE(params_channels_c)

#define color_num 3

class MeteoWizard : public QWizard
{
	Q_OBJECT
public:
	QLineEdit* m_msg_path;
	QLineEdit* m_jpg_path;
	QLineEdit* m_shp_path;
	QLineEdit* m_fname_pref;
	QCheckBox* m_msg_type;
	QComboBox* m_channel_tag;
	QCalendarWidget* m_calendar0;
	QCalendarWidget* m_calendar1;
	QComboBox* m_minutes0;
	QComboBox* m_minutes1;
	QDoubleSpinBox* m_arrow_scale;
	SelectColorButton* m_arrow_color;
	QDoubleSpinBox* m_arrow_width;
	QDoubleSpinBox* m_region_step;
	QCheckBox* m_rgb_flag;
	QComboBox* m_rgb_preset;
	QComboBox* m_rgb_dimin[3];
	QComboBox* m_rgb_subtr[3];
	QDoubleSpinBox* m_thres_min[3];
	QDoubleSpinBox* m_thres_max[3];
	QDoubleSpinBox* m_gamma[3];
	QListWidget* m_rgbSetList;
	QPushButton* m_rgb_add;
	QPushButton* m_rgb_del;

	QStandardItemModel* m_model_cntrs;
	QTableView* m_view_cntrs;

	QQuickWidget* m_osm;

	std::vector<date_c> m_dates;
	std::vector<shp_c*> m_shp_files;
	ll_region_c m_ll_region;
	wiz_params_c m_wiz_params;

	bool m_json;

	//ModelRender* m_modelRender;
	//palettes_c m_palettes;
	void checkColorTF(std::vector<double>& xv, std::vector<double>& yv);
	QDoubleSpinBox* m_normSp[3];
	QDoubleSpinBox* m_cutSp[3];
	QDoubleSpinBox* m_bBoxSp[6];
	QDoubleSpinBox* m_colorTfSp_X[2 * color_num], * m_colorTfSp_Y[2 * color_num];
	QMetaObject::Connection m_colorConnect_X[2 * color_num], m_colorConnect_Y[2 * color_num];

	MeteoWizard(QWidget* parent);

	QWizardPage* createIntroPage();
	QVBoxLayout* addDateTimePanel(bool from, const char* name);
	QWizardPage* createDateTimePage();
	QWizardPage* createShapePage();
	QWizardPage* createRegionPage();
	QWizardPage* createPostProcPage();

	static cv::Mat* openMsg(const wchar_t* fname, ll_region_c& ll_region);
	cv::Mat* makeRgb(date_c& date, const params_channels_c& par_chnl);
	void process();

protected slots:
	void accept() override;
#if defined(WITH_VTK)
	void colorBoxValueChanged(double val);
#endif
};

extern const wchar_t* const rgb_names_en[RGB_PRESET_NUM];
