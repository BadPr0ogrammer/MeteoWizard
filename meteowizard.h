#pragma once

#include <vector>
#include <QtWidgets>
#include <QQuickWidget>
#include <opencv2/core/core.hpp>

extern const char* channel_tags[];

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

	void render(const wchar_t* fname, const cv::Mat* const p0, const cv::Mat* const p1, int dt_mn);

protected slots:
	void accept() override;
};
