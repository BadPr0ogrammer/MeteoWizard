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

#include <atlbase.h>
#include <atlsafe.h>
#include <comutil.h>

#include "inc.h"
#include "meteowizard.h"
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
#include "atmrad1.h"
#include "EMSNWCLib_i.h"

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

const wchar_t* const rgb_names_en[RGB_PRESET_NUM] = {
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

QString rgbSetLabel(params_channels_c& p)
{
	QString ret;
	for (int i = 0; i < 6; i++) {
		const char* s = channel_tags[p.channels[i]];
		ret += s[0] == 0 ? QString("Non") : QString(s);
		if (i != 5)
			ret += "-";
	}
	for (int i = 0; i < 9; i++) {
		ret += QString::number(p.params[i]);
		if (i != 8)
			ret += "-";
	}
	return ret;
}

QWizardPage* MeteoWizard::createPostProcPage()
{
	if (m_wiz_params.rgb_channels[0][0] == T_NONE) {
		memcpy(m_wiz_params.rgb_params, rgb_params_0, sizeof(rgb_params_0));
		memcpy(m_wiz_params.rgb_channels, rgb_channels_0, sizeof(rgb_channels_0));
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
	m_rgb_flag->setChecked(m_wiz_params.rgb);

	hbox->setAlignment(m_rgb_flag, Qt::AlignCenter);
	hbox->addWidget(m_rgb_flag);
	hbox->addStretch();

	QGridLayout* grid = new QGridLayout;
	layout->addLayout(grid);
	grid->setContentsMargins(6, 12, 6, 12);

	const int curSel = 4;

	grid->addWidget(new QLabel(str_rgb_selected), 0, 0);
	m_rgbSetList = new QListWidget;
	grid->addWidget(m_rgbSetList, 0, 1, 2, 7);
	m_rgbSetList->setFixedHeight(60);

	params_channels_c params_chnls(m_wiz_params.rgb_channels[curSel], m_wiz_params.rgb_params[curSel]);
	QListWidgetItem* item = new QListWidgetItem(rgbSetLabel(params_chnls));
	item->setData(Qt::UserRole, QVariant::fromValue(params_chnls));
	m_rgbSetList->addItem(item);

	m_rgb_add = new QPushButton(str_add_preset);
	grid->addWidget(m_rgb_add, 0, 8, 1, 2);

	m_rgb_del = new QPushButton(str_remove_preset);
	grid->addWidget(m_rgb_del, 1, 8, 1, 2);

	grid->addWidget(new QLabel(str_rgb_presets), 2, 0);

	m_rgb_preset = new QComboBox;
	m_rgb_preset->setFixedWidth(120);
	for (int i = 0; i < _countof(rgb_names); i++)
		m_rgb_preset->addItem(rgb_names[i]);
	m_rgb_preset->setCurrentIndex(curSel);
	grid->addWidget(m_rgb_preset, 2, 1);

	grid->addWidget(new QLabel(str_red_difference), 3, 0);
	grid->addWidget(new QLabel(str_green_difference), 4, 0);
	grid->addWidget(new QLabel(str_blue_difference), 5, 0);
	QLabel* l1 = new QLabel("-");
	l1->setFixedWidth(8);
	grid->addWidget(l1, 3, 2);
	QLabel* l2 = new QLabel("-");
	l2->setFixedWidth(8);
	grid->addWidget(l2, 4, 2);
	QLabel* l3 = new QLabel("-");
	l3->setFixedWidth(8);
	grid->addWidget(l3, 5, 2);

	for (int i = 0; i < 3; i++) {
		m_rgb_dimin[i] = new QComboBox;
		grid->addWidget(m_rgb_dimin[i], i + 3, 1);

		m_rgb_subtr[i] = new QComboBox;
		grid->addWidget(m_rgb_subtr[i], i + 3, 3);

		for (int j = 0; j < T_NUM; j++) {
			m_rgb_dimin[i]->addItem(channel_tags[j]);
			m_rgb_subtr[i]->addItem(channel_tags[j]);
		}
		m_rgb_dimin[i]->setCurrentIndex(m_wiz_params.rgb_channels[curSel][2 * i]);
		m_rgb_subtr[i]->setCurrentIndex(m_wiz_params.rgb_channels[curSel][2 * i + 1]);

		QLabel* m0 = new QLabel("Min:");
		m0->setFixedWidth(26);
		grid->addWidget(m0, i + 3, 4);
		m_thres_min[i] = new QDoubleSpinBox;
		m_thres_min[i]->setSingleStep(1);
		m_thres_min[i]->setMinimum(-100);
		m_thres_min[i]->setMaximum(100000);

		grid->addWidget(m_thres_min[i], i + 3, 5);
		m_thres_min[i]->setValue(m_wiz_params.rgb_params[curSel][3 * i]);

		QLabel* m1 = new QLabel("Max:");
		m1->setFixedWidth(26);
		grid->addWidget(m1, i + 3, 6);
		m_thres_max[i] = new QDoubleSpinBox;
		m_thres_max[i]->setSingleStep(1);
		m_thres_max[i]->setMinimum(-100);
		m_thres_max[i]->setMaximum(100000);

		grid->addWidget(m_thres_max[i], i + 3, 7);
		m_thres_max[i]->setValue(m_wiz_params.rgb_params[curSel][3 * i + 1]);

		QLabel* g = new QLabel("Gamma:");
		g->setFixedWidth(26);
		grid->addWidget(g, i + 3, 8);
		m_gamma[i] = new QDoubleSpinBox;
		m_gamma[i]->setSingleStep(0.1);
		m_gamma[i]->setMinimum(0);
		m_gamma[i]->setMaximum(5);

		grid->addWidget(m_gamma[i], i + 3, 9);
		m_gamma[i]->setValue(m_wiz_params.rgb_params[curSel][3 * i + 2]);
	}

	connect(m_rgb_preset, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int idx) {
		for (int i = 0; i < 3; i++) {
			m_rgb_dimin[i]->setCurrentIndex(m_wiz_params.rgb_channels[idx][2 * i]);
			m_rgb_subtr[i]->setCurrentIndex(m_wiz_params.rgb_channels[idx][2 * i + 1]);

			m_thres_min[i]->setValue(m_wiz_params.rgb_params[idx][3 * i]);
			m_thres_max[i]->setValue(m_wiz_params.rgb_params[idx][3 * i + 1]);
			m_gamma[i]->setValue(m_wiz_params.rgb_params[idx][3 * i + 2]);
		}
		});

	for (int i = 0; i < 3; i++) {
		connect(m_rgb_dimin[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int k) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params.rgb_channels[idx][2 * i] = k;
			});
		connect(m_rgb_subtr[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int k) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params.rgb_channels[idx][2 * i + 1] = k;
			});
		connect(m_thres_min[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params.rgb_params[idx][3 * i] = d;
			});
		connect(m_thres_max[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params.rgb_params[idx][3 * i + 1] = d;
			});
		connect(m_gamma[i], static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [=](double d) {
			int idx = m_rgb_preset->currentIndex();
			m_wiz_params.rgb_params[idx][3 * i + 2] = d;
			});
	}
	connect(m_rgb_flag, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), [=](int state) {
		bool f = state == Qt::Checked;
		m_wiz_params.rgb = f;
		m_rgb_preset->setEnabled(f);
		for (int i = 0; i < 3; i++) {
			m_rgb_dimin[i]->setEnabled(f);
			m_rgb_subtr[i]->setEnabled(f);
			m_thres_min[i]->setEnabled(f);
			m_thres_max[i]->setEnabled(f);
			m_gamma[i]->setEnabled(f);
		}
		});

	connect(m_rgb_add, &QPushButton::clicked, [=]() {
		double params[9]{ 0,0,0,0,0,0,0,0,0 };
		int channels[6]{ 0,0,0,0,0,0 };
		for (int i = 0; i < 3; i++) {
			channels[2 * i] = m_rgb_dimin[i]->currentIndex();
			channels[2 * i + 1] = m_rgb_subtr[i]->currentIndex();
			params[3 * i] = m_thres_min[i]->value();
			params[3 * i + 1] = m_thres_max[i]->value();
			params[3 * i + 2] = m_gamma[i]->value();
		}
		params_channels_c params_chnls(channels, params);

		QListWidgetItem* item = new QListWidgetItem(rgbSetLabel(params_chnls));
		item->setData(Qt::UserRole, QVariant::fromValue(params_chnls));
		m_rgbSetList->addItem(item);
		});
	connect(m_rgb_del, &QPushButton::clicked, [=]() {
		QListWidgetItem* item = m_rgbSetList->selectedItems()[0];
		if (item) {
			m_rgbSetList->removeItemWidget(item);
			delete item;
		}
		});

	layout->addStretch();
	page->setLayout(layout);
	return page;
}

cv::Mat* MeteoWizard::makeRgb(date_c& date, const params_channels_c& par_chnl)
{
	cv::Mat* ret;
	slot_c src;
	wchar_t buf[100];
	for (auto chnl : par_chnl.channels) {
		if (chnl > 0) {
			QString sch = channel_tags[chnl];
			swprintf(buf, MSAT_NAME_FORMAT, m_wiz_params.msg, m_wiz_params.msg, sch.utf16(), 7, date.m_year, date.m_mon, date.m_day, date.m_hour, date.m_mn);

			if (!(src.m_img[chnl] = openMsg(buf, m_ll_region)))
				return nullptr;
		}
	}
	
	CComPtr<IHritObject> obj;
	double calibration[24], *pc = nullptr;
	if (SUCCEEDED(obj.CoCreateInstance(CLSID_HritObject))) {
		_bstr_t bstr(buf);
		if (SUCCEEDED(obj->ReadMSGInfo(bstr))) {
			SAFEARRAYBOUND Bound;
			Bound.lLbound = 0;
			Bound.cElements = 24;
			SAFEARRAY* psa = SafeArrayCreate(VT_R8, 1, &Bound); //??? pptr ?
			if (SUCCEEDED(obj->get_CalibrationTbl(&psa))) {
				CComSafeArray<double> comarr(psa);
				for (int i = 0; i < 24; i++)
					calibration[i] = comarr.GetAt(i);
				pc = calibration;
				InitInfoCan();
			}
		}
	}
	return AtmradMakeDif(src, par_chnl.channels, par_chnl.params, pc);
}
