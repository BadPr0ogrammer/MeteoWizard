#include <vector>
#include <set>
#include <codecvt>

#include <QtWidgets>
#include <QQmlApplicationEngine> 
#include <QGeoCoordinate>
#include <QQuickItem>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "inc.h"
#include "meteowizard.h";
#include "datec.h"
#include "shaperead.h"
#include "shpproc.h"
#include "region.h"
#include "SelectColorButton.h"
#include "cntrsitemdelegate.h"
#include "dwtopen.h"
#include "painter.h"
#include "supl.h"
#include "wizparams.h"
#include "local_str.h"
#include "atmrad.h"

using namespace std;
using namespace cv;

const char* const rgb_names[RGB_PRESET_NUM] = {
  str_mphys_night,
  str_dust,
  str_mphys_airmass,
  str_mphys_day,
  str_natural,
  //IDSTR_CLOUD_TOP_HRV,
  //IDSTR_HRV_CLOUD_MPHYSICS,
  //IDSTR_TRUE_COLOR_HRV
};

const char* const rgb_names_en[RGB_PRESET_NUM] = {
  str_mphys_night_en,
  str_dust_en,
  str_mphys_airmass_en,
  str_mphys_day_en,
  str_natural_en,
};

double rgb_params_0[RGB_PRESET_NUM][9] = {
  { -4,2,1, -4,5,1, 243,303,1 },
  { -25,0,1, -40,5,1, 243,208,1 },
  { -4,2,1, 0,15,2.5, 261,289,1 },
  { 0,10000,1, 0,6000,1.5, 243,303,1 },
  { 0,10000,1, 0,10000,1, 0,10000,1 },
  //{0,10000,1, 0,10000,1, 0,10000,1},
  //{7000,10000,1, 7000,10000,1, -70,-40,2},
  //{0,10000,1, 0,10000,1, 0,10000,1},
};

int rgb_channels_0[RGB_PRESET_NUM][6] = {
  { T_12_0, T_10_8, T_10_8, T_08_7, T_10_8, T_NONE },
  { T_06_2, T_07_3, T_08_7, T_10_8, T_06_2, T_NONE },//T_09_7
  { T_12_0, T_10_8, T_10_8, T_08_7, T_10_8, T_NONE },
  { T_00_8, T_NONE, T_03_9, T_NONE, T_10_8, T_NONE },
  { T_01_6, T_NONE, T_00_8, T_NONE, T_00_6, T_NONE },
#ifdef ab_
  { T_HRV,  T_NONE, T_HRV,  T_NONE, T_10_8, T_NONE },
  { T_HRV,  T_NONE, T_HRV,  T_NONE, T_10_8, T_03_9 },
  { T_01_6, T_NONE, T_00_8, T_NONE, T_HRV, T_NONE },
#endif
};

QWizardPage* MeteoWizard::createPostProcPage()
{
	if (m_wiz_params->rgb_channels[0][0] == T_NONE) {
		memcpy(m_wiz_params->rgb_params, rgb_params_0, sizeof(rgb_params_0));
		memcpy(m_wiz_params->rgb_channels, rgb_channels_0, sizeof(rgb_channels_0));
	}
	QWizardPage* page = new QWizardPage;

	page->setTitle(str_post_proc_page_title);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addStretch();
	layout->setContentsMargins(6, 12, 6, 12);

	QHBoxLayout* hbox = new QHBoxLayout;
	layout->addLayout(hbox);

	hbox->addWidget(new QLabel(str_generate_rgb));

	m_rgb_flag = new QCheckBox;
	m_rgb_flag->setChecked(m_wiz_params->rgb);

	hbox->setAlignment(m_rgb_flag, Qt::AlignCenter);
	hbox->addWidget(m_rgb_flag);
	hbox->addStretch();

	QGridLayout* grid = new QGridLayout;
	layout->addLayout(grid);
	grid->setContentsMargins(6, 12, 6, 12);

	grid->addWidget(new QLabel(str_rgb_presets), 0, 0);

	m_rgb_preset = new QComboBox;
	m_rgb_preset->setFixedWidth(120);
	for (int i = 0; i < _countof(rgb_names); i++)
		m_rgb_preset->addItem(rgb_names[i]);
	m_rgb_preset->setCurrentIndex(4);
	grid->addWidget(m_rgb_preset, 0, 1);

	grid->addWidget(new QLabel(str_red_difference), 1, 0);
	grid->addWidget(new QLabel(str_green_difference), 2, 0);
	grid->addWidget(new QLabel(str_blue_difference), 3, 0);
	QLabel* l1 = new QLabel("-");
	l1->setFixedWidth(8);
	grid->addWidget(l1, 1, 2);
	QLabel* l2 = new QLabel("-");
	l2->setFixedWidth(8);
	grid->addWidget(l2, 2, 2);
	QLabel* l3 = new QLabel("-");
	l3->setFixedWidth(8);
	grid->addWidget(l3, 3, 2);

	for (int i = 0; i < 3; i++) {
		m_rgb_dimin[i] = new QComboBox;
		grid->addWidget(m_rgb_dimin[i], i + 1, 1);

		m_rgb_subtr[i] = new QComboBox;
		grid->addWidget(m_rgb_subtr[i], i + 1, 3);

		for (int j = 0; j < T_NUM; j++) {
			m_rgb_dimin[i]->addItem(channel_tags[j]);
			m_rgb_subtr[i]->addItem(channel_tags[j]);
		}
		m_rgb_dimin[i]->setCurrentIndex(m_wiz_params->rgb_channels[4][2 * i]);
		m_rgb_subtr[i]->setCurrentIndex(m_wiz_params->rgb_channels[4][2 * i + 1]);

		QLabel* m0 = new QLabel("Min:");
		m0->setFixedWidth(26);
		grid->addWidget(m0, i + 1, 4);
		m_thres_min[i] = new QDoubleSpinBox;
		m_thres_min[i]->setSingleStep(1);
		m_thres_min[i]->setMinimum(-100);
		m_thres_min[i]->setMaximum(100000);

		grid->addWidget(m_thres_min[i], i + 1, 5);
		m_thres_min[i]->setValue(m_wiz_params->rgb_params[4][3 * i]);

		QLabel* m1 = new QLabel("Max:");
		m1->setFixedWidth(26);
		grid->addWidget(m1, i + 1, 6);
		m_thres_max[i] = new QDoubleSpinBox;
		m_thres_max[i]->setSingleStep(1);
		m_thres_max[i]->setMinimum(-100);
		m_thres_max[i]->setMaximum(100000);

		grid->addWidget(m_thres_max[i], i + 1, 7);
		m_thres_max[i]->setValue(m_wiz_params->rgb_params[4][3 * i + 1]);

		QLabel* g = new QLabel("Gamma:");
		g->setFixedWidth(26);
		grid->addWidget(g, i + 1, 8);
		m_gamma[i] = new QDoubleSpinBox;
		m_gamma[i]->setSingleStep(0.1);
		m_gamma[i]->setMinimum(0);
		m_gamma[i]->setMaximum(5);

		grid->addWidget(m_gamma[i], i + 1, 9);
		m_gamma[i]->setValue(m_wiz_params->rgb_params[4][3 * i + 2]);
	}

	connect(m_rgb_preset, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&](int idx) {
		for (int i = 0; i < 3; i++) {
			m_rgb_dimin[i]->setCurrentIndex(m_wiz_params->rgb_channels[idx][2 * i]);
			m_rgb_subtr[i]->setCurrentIndex(m_wiz_params->rgb_channels[idx][2 * i + 1]);

			m_thres_min[i]->setValue(m_wiz_params->rgb_params[idx][3 * i]);
			m_thres_max[i]->setValue(m_wiz_params->rgb_params[idx][3 * i + 1]);
			m_gamma[i]->setValue(m_wiz_params->rgb_params[idx][3 * i + 2]);
		}
		});

	for (int i = 0; i < 3; i++) {
		connect(m_rgb_dimin[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&](int k) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params->rgb_channels[idx][2 * i] = k;
			});
		connect(m_rgb_subtr[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&](int k) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params->rgb_channels[idx][2 * i + 1] = k;
			});
		connect(m_thres_min[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params->rgb_params[idx][3 * i] = d;
			});
		connect(m_thres_max[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params->rgb_params[idx][3 * i + 1] = d;
			});
		connect(m_gamma[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params->rgb_params[idx][3 * i + 2] = d;
			});
	}
	connect(m_rgb_flag, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
		m_wiz_params->rgb = state == Qt::Checked;
		});

	layout->addStretch();
	page->setLayout(layout);
	return page;
}

void MeteoWizard::makeRgb()
{
	int channels[6]{ 0,0,0,0,0,0 };
	for (int i = 0; i < 3; i++) {
		int i1 = m_rgb_dimin[i]->currentIndex();
		if (i1 > 0)
			channels[2 * i] = i1;
		int i2 = m_rgb_subtr[i]->currentIndex();
		if (i2 > 0)
			channels[2 * i + 1] = i2;
	}
	double thresh[9];
	for (int i = 0; i < 3; i++) {
		thresh[3 * i] = m_thres_min[i]->value();
		thresh[3 * i + 1] = m_thres_max[i]->value();
		thresh[3 * i + 2] = m_gamma[i]->value();
	}
	const char* fprefix = rgb_names_en[m_rgb_preset->currentIndex()];
	for (auto& date : *m_dates) {
		slot_c src;
		for (auto chnl : channels) {
			if (chnl > 0) {
				wchar_t buf[100];
				QString sch = channel_tags[chnl];
				swprintf(buf, MSAT_NAME_FORMAT, m_wiz_params->msg, m_wiz_params->msg, sch.utf16(), 7, date.m_year, date.m_mon, date.m_day, date.m_hour, date.m_mn);

				cv::Mat* img0 = openMsg(buf, m_ll_region);
				SuplDebugMat(img0);

				src.m_img[chnl] = img0;
			}
		}
		cv::Mat* rgb = AtmradMakeDif(&src, thresh, channels);
		{
			char buf[100];
			sprintf(buf, "%s-%04d%02d%02d%02d%02d.jpg", fprefix, date.m_year, date.m_mon, date.m_day, date.m_hour, date.m_mn);
			imwrite(buf, *rgb);
		}
	}
}
