#pragma once

#include <vector>
#include <QtWidgets>
#include <QQuickWidget>
#include <opencv2/core/core.hpp>

#include "inc.h"

class date_c;
class shp_c;
class ll_region_c;
class wiz_params_c;
class SelectColorButton;

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

	QStandardItemModel* m_model_cntrs;
	QTableView* m_view_cntrs;

	QQuickWidget* m_osm;

	std::vector<date_c>* m_dates;
	std::vector<shp_c*>* m_shp_files;
	ll_region_c* m_ll_region;
	wiz_params_c* m_wiz_params;
	bool m_json;

	MeteoWizard(QWidget* parent);

	QWizardPage* createIntroPage();
	QVBoxLayout* addDateTimePanel(bool from, const char* name);
	QWizardPage* createDateTimePage();
	QWizardPage* createShapePage();
	QWizardPage* createRegionPage();
	QWizardPage* createPostProcPage();

	cv::Mat* openMsg(const wchar_t* fname, ll_region_c* ll_region);
	cv::Mat* makeRgb(date_c& date);

protected slots:
	void accept() override;
};

extern const wchar_t* const rgb_names_en[RGB_PRESET_NUM];