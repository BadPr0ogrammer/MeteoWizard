#include <vector>
#include <codecvt>

#include <QtWidgets>
#include <QQmlApplicationEngine> 
#include <QGeoCoordinate>
#include <QQuickItem>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

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

using namespace std;
using namespace cv;

const char* channel_tags[T_NUM] = { "", "VIS006", "VIS008", "IR_016", "IR_039", "WV_062", "WV_073", "IR_087", "IR_108", "IR_120", "IR_134"};//"IR_097", 

MeteoWizard::MeteoWizard(QWidget* parent) : QWizard(parent),
m_msg_path(nullptr), m_jpg_path(nullptr), m_shp_path(nullptr), m_fname_pref(nullptr), m_msg_type(nullptr), m_channel_tag(nullptr), m_calendar0(nullptr), m_calendar1(nullptr),
m_minutes0(nullptr), m_minutes1(nullptr), m_arrow_scale(nullptr), m_arrow_color(nullptr), m_arrow_width(nullptr), m_region_step(nullptr), m_model_cntrs(nullptr), m_view_cntrs(nullptr),
m_osm(nullptr), m_dates(new std::vector<date_c>()), m_shp_files(new std::vector<shp_c*>()), m_wiz_params(new wiz_params_c())
{
	m_wiz_params->working_dir = QDir::currentPath();
	m_ll_region = new ll_region_c();
	m_json = m_wiz_params->read_settings(*m_wiz_params, m_ll_region, *m_shp_files, "settings.json");
}

QWizardPage* MeteoWizard::createIntroPage()
{
	QWizardPage* page = new QWizardPage;
	page->setTitle(QString(str_output_settings));

	QVBoxLayout* layout = new QVBoxLayout;

	QLabel* label = new QLabel(str_info_page_decsr);
	label->setWordWrap(true);
	layout->addWidget(label);

	layout->addStretch();
	{
		QGridLayout* hbox = new QGridLayout;
		layout->addLayout(hbox);
		{
			hbox->addWidget(new QLabel(str_input_files_msg_path), 0, 0);
			m_msg_path = new QLineEdit(!m_json ? "debug/Data/MSG" : m_wiz_params->msg_path);

			hbox->addWidget(m_msg_path, 0, 1);
			m_msg_path->setFixedWidth(400);

			QPushButton* btn = new QPushButton(str_select);
			connect(btn, &QPushButton::clicked, [=]() {
				QString directory = QFileDialog::getExistingDirectory(NULL, str_input_files_msg_path, QDir::currentPath());
				if (!directory.isEmpty())
					m_msg_path->setText(directory);
				});
			hbox->addWidget(btn, 0, 2);
		}
		{
			hbox->addWidget(new QLabel(str_output_files_jpg_path), 1, 0);
			m_jpg_path = new QLineEdit(!m_json ? "debug/Data/Images" : m_wiz_params->jpg_path);

			hbox->addWidget(m_jpg_path, 1, 1);
			m_jpg_path->setFixedWidth(400);

			QPushButton* btn = new QPushButton(str_select);
			connect(btn, &QPushButton::clicked, [=]() {
				QString directory = QFileDialog::getExistingDirectory(NULL, str_output_files_jpg_path, QDir::currentPath());
				if (!directory.isEmpty())
					m_jpg_path->setText(directory);
				});
			hbox->addWidget(btn, 1, 2);
		}
		{
			hbox->addWidget(new QLabel(str_input_files_shp_path), 2, 0);
			m_shp_path = new QLineEdit(!m_json ? "debug/Data/Shp" : m_wiz_params->shp_path);

			hbox->addWidget(m_shp_path, 2, 1);
			m_shp_path->setFixedWidth(400);

			QPushButton* btn = new QPushButton(str_select);
			connect(btn, &QPushButton::clicked, [=]() {
				QString directory = QFileDialog::getExistingDirectory(NULL, str_input_files_shp_path, QDir::currentPath());
				if (!directory.isEmpty())
					m_shp_path->setText(directory);
				});
			hbox->addWidget(btn, 2, 2);
		}

		hbox->addWidget(new QLabel(str_output_file_name_prefix), 3, 0);
		m_fname_pref = new QLineEdit(!m_json ? "Test" : m_wiz_params->fname_pref);
		m_fname_pref->setFixedWidth(150);
		hbox->addWidget(m_fname_pref, 3, 1);

		hbox->addWidget(new QLabel(str_satellite_type), 4, 0);
		m_msg_type = new QCheckBox;
		m_msg_type->setChecked(!m_json ? true : m_wiz_params->msg == 4);
		hbox->addWidget(m_msg_type, 4, 1);

		hbox->addWidget(new QLabel(str_main_channel), 5, 0);
		m_channel_tag = new QComboBox;
		m_channel_tag->setFixedWidth(150);
		for (int i = 1; i < _countof(channel_tags); i++)
			m_channel_tag->addItem(channel_tags[i]);
		m_channel_tag->setCurrentIndex(4);
		hbox->addWidget(m_channel_tag, 5, 1);
	}
	layout->addStretch();

	page->setLayout(layout);
	return page;
}

QVBoxLayout* MeteoWizard::addDateTimePanel(bool from, const char* name)
{
	QVBoxLayout* vbox = new QVBoxLayout;

	vbox->addWidget(new QLabel(name));

	QCalendarWidget* calendar;
	if (from)
		calendar = m_calendar0 = new QCalendarWidget;
	else
		calendar = m_calendar1 = new QCalendarWidget;
	vbox->addWidget(calendar);
	
	date_c& d = from ? m_wiz_params->start : m_wiz_params->stop;
	{
		QDate date;
		date.setDate(d.m_year, d.m_mon, d.m_day);
		calendar->setSelectedDate(date);
	}
	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->setAlignment(Qt::AlignHCenter);
	hbox->addWidget(new QLabel(str_hours_sc_min));

	QComboBox* minutes;
	if (from)
		minutes = m_minutes0 = new QComboBox;
	else
		minutes = m_minutes1 = new QComboBox;

	for (int j = 0; j < 24; j++)
		for (int i = 0; i < 4; i++) {
			char buf[6];
			sprintf(buf, "%02d%02d", j, i * 15);
			minutes->addItem(buf);

			if (j == d.m_hour && i == d.m_mn / 15)
				minutes->setCurrentIndex(minutes->count() - 1);
		}
	hbox->addWidget(minutes);

	vbox->addLayout(hbox);
	return vbox;
}

QWizardPage* MeteoWizard::createDateTimePage()
{
	QWizardPage* page = new QWizardPage;

	page->setTitle(str_datetime_page_title);

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->setContentsMargins(12, 12, 12, 12);

	if (!m_json) {
		m_wiz_params->start = date_c(2019, 11, 21, 10, 0);
		m_wiz_params->stop = date_c(2019, 11, 21, 12, 0);
	}
	hbox->addLayout(addDateTimePanel(true, str_date_from));
	hbox->addLayout(addDateTimePanel(false, str_date_to));

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addLayout(hbox);

	page->setLayout(layout);
	return page;
}

void cntrs_add_row(shp_c* shp, QStandardItem* root)
{
	QList<QStandardItem*> tmp;

	QStandardItem* item = new QStandardItem(shp->m_shp_name);
	item->setEditable(false);
	tmp.append(item);

	//if (shp->m_dbf_flds.m_dbf_plparam.isEmpty())
	  //  shp->m_dbf_plparam = DEF_DBF_PLS_PARAM;
	item = new QStandardItem(DEF_DBF_PLS_PARAM);
	tmp.append(item);

	item = new QStandardItem();
	item->setBackground(QBrush(shp->m_text_color));
	tmp.append(item);

	item = new QStandardItem();
	item->setBackground(QBrush(shp->m_line_color));
	tmp.append(item);

	item = new QStandardItem(QString::number(shp->m_line_width));
	tmp.append(item);

	item = new QStandardItem(dash_line_names[shp->m_dash]);
	tmp.append(item);

	item = new QStandardItem(shp->m_font_face);
	tmp.append(item);

	item = new QStandardItem(QString::number(shp->m_font_size));
	tmp.append(item);

	root->appendRow(tmp);
}

QWizardPage* MeteoWizard::createShapePage()
{
	QWizardPage* page = new QWizardPage;

	page->setTitle(str_visual_style);

	QGridLayout* layout = new QGridLayout;
	layout->setContentsMargins(12, 12, 12, 12);
	{
		QVBoxLayout* vbox2 = new QVBoxLayout;
		vbox2->setContentsMargins(12, 12, 12, 12);

		QLabel* lab1 = new QLabel(str_vector_layers);
		vbox2->addWidget(lab1);

		m_model_cntrs = new QStandardItemModel;

		QStringList header_sl1;

		header_sl1 << str_file_name << str_dbf_params << str_text_color << str_line_color << str_line_width << str_line_style << str_font_name << str_size;//, IDSTR_POINTS
		m_model_cntrs->setColumnCount(header_sl1.size());
		m_model_cntrs->setHorizontalHeaderLabels(header_sl1);

		if (!m_json) {
			shp_c* shp = new shp_c();
			shp->m_shp_name = "ne_10m_coastline.shp";
			m_shp_files->push_back(shp);
			shp = new shp_c();
			shp->m_shp_name = "ne_10m_populated_places_simple.shp";
			m_shp_files->push_back(shp);
		}
		if (m_shp_files && m_shp_files->size()) {
			QStandardItem* root = m_model_cntrs->invisibleRootItem();
			for (shp_c* p : *m_shp_files) {
				cntrs_add_row(p, root);
			}
		}

		m_view_cntrs = new QTableView;
		m_view_cntrs->setAlternatingRowColors(true);
		m_view_cntrs->setSelectionMode(QAbstractItemView::SingleSelection);
		m_view_cntrs->setSelectionBehavior(QAbstractItemView::SelectItems);
		m_view_cntrs->setModel(m_model_cntrs);
		m_view_cntrs->setItemDelegate(new cntrs_item_delegate_c(m_shp_files, m_view_cntrs));

		vbox2->addWidget(m_view_cntrs);
		{
			QHBoxLayout* hbox = new QHBoxLayout;
			hbox->setContentsMargins(12, 12, 12, 12);
			hbox->addStretch();

			QPushButton* add = new QPushButton(QIcon(QPixmap(":/images/add3.png")), "");
			add->setToolTip(str_add_layer);
			add->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			hbox->addWidget(add);
			hbox->setAlignment(add, Qt::AlignRight);
			connect(add, &QPushButton::clicked, [=]() {
				QStringList fnames = QFileDialog::getOpenFileNames(NULL, str_load, "", "Shp (*.shp)");
				if (fnames.isEmpty() || fnames[0].isEmpty())
					return;
				QString wd = QDir::currentPath();

				int n;
				n = fnames[0].lastIndexOf('/', -1);
				QString path = fnames[0].left(n - 1);
				QDir::setCurrent(path);

				m_shp_path->setText(path);

				QStandardItem* root = m_model_cntrs->invisibleRootItem();
				for (int i = 0; i < fnames.size(); i++) {
					QFileInfo finfo(fnames[i]);
					if (!finfo.exists()) {
						wstring s = L"File not found ";
						s += (wchar_t*)fnames[i].utf16();
						OutputDebugString(s.c_str());
						continue;
					}
					shp_c* shp = shp_c::shpProc(fnames[i].right(n + 1), m_ll_region);
					//shp_c* shp = new shp_c();
					//shp->m_shp_name = QString::fromWCharArray(buf + n + 1);
					if (shp)
					{
						if (!m_shp_files)
							m_shp_files = new vector<shp_c*>();
						m_shp_files->push_back(shp);

						cntrs_add_row(shp, root);
					}
					else {
						wstring s = L"Load file ";
						s += (wchar_t*)fnames[i].utf16();
						s += L" failed";
						OutputDebugString(s.c_str());
					}
				}
				QDir::setCurrent(wd);
				});

			QPushButton* rem = new QPushButton(QIcon(QPixmap(":/images/buttonminus.png")), "");
			rem->setToolTip(str_remove_layer);
			rem->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			hbox->addWidget(rem);
			hbox->setAlignment(rem, Qt::AlignRight);
			connect(rem, &QPushButton::clicked, [=]() {
				QModelIndexList list = m_view_cntrs->selectionModel()->selectedIndexes();
				if (!list.size())
					return;
				int row = list[0].row();
				m_model_cntrs->removeRow(row);

				m_shp_files->erase(m_shp_files->begin() + row);
				});
			vbox2->addLayout(hbox);
		}
		layout->addLayout(vbox2, 0, 0, 1, 5);
	}

	layout->addWidget(new QLabel(str_wind_arrows), 1, 0, 1, 3);

	layout->addWidget(new QLabel(str_size), 2, 0);

	m_arrow_scale = new QDoubleSpinBox;

	m_arrow_scale->setValue(!m_json ? 1 : m_wiz_params->arrow_scale);
	m_arrow_scale->setSingleStep(0.1);
	layout->addWidget(m_arrow_scale, 2, 1);

	layout->addWidget(new QLabel(str_color), 3, 0);

	m_arrow_color = new SelectColorButton(this, page);
	m_arrow_color->setColor(!m_json ? QColor(0, 255, 0) : m_wiz_params->arrow_color);
	layout->addWidget(m_arrow_color, 3, 1);
	m_arrow_color->setFixedWidth(60);

	layout->addWidget(new QLabel(str_width_depth), 4, 0);

	m_arrow_width = new QDoubleSpinBox;

	m_arrow_width->setValue(!m_json ? 1 : m_wiz_params->arrow_width);
	m_arrow_width->setSingleStep(0.1);
	layout->addWidget(m_arrow_width, 4, 1);

	page->setLayout(layout);
	return page;
}

QQuickWidget* quick_map_create(QWidget* parent, double left, double right, double top, double bottom)
{
	QQuickWidget* root = new QQuickWidget(QUrl("qrc:/map.qml"), parent);
	if (root == nullptr) {
		qDebug() << str_error_blank << "map.qml (root == nullptr)\n";
		return nullptr;
	}
	QQmlEngine::setObjectOwnership(root, QQmlEngine::CppOwnership);
	root->setResizeMode(QQuickWidget::SizeRootObjectToView);
	{
		QObject* map = root->rootObject()->findChild<QObject*>("osmMap");
		if (map == nullptr) {
			qDebug() << str_error_blank << "map.qml (map == nullptr)\n";
			return nullptr;
		}
		else {
			QGeoCoordinate center(0, 0);
			center.setLongitude((right + left) / 2);
			center.setLatitude((top + bottom) / 2);
			map->setProperty("center", QVariant::fromValue(center));
		}
	}
	{
		QObject* rect = root->rootObject()->findChild<QObject*>("redRect");
		if (rect == nullptr) {
			qDebug() << str_error_blank << "map.qml (rect == nullptr)\n";
			return nullptr;
		}
		else {
			QGeoCoordinate topLeft(1, -1), bottomRight(-1, 1);
			int x0 = floor(left);
			topLeft.setLongitude(x0);
			int x1 = ceil(right);
			bottomRight.setLongitude(x1);
			int y1 = ceil(top);
			topLeft.setLatitude(y1);
			int y0 = floor(bottom);
			bottomRight.setLatitude(y0);

			rect->setProperty("topLeft", QVariant::fromValue(topLeft));
			rect->setProperty("bottomRight", QVariant::fromValue(bottomRight));
		}
	}
	return root;
}

void quick_map_done(QObject* objRect, QQuickWidget* osm, double& left, double& right, double& top, double& bottom)//QVariant rectObj
{
	//QObject* objRect = rectObj.value<QObject*>();
	if (!objRect) {
		osm->deleteLater();
		return;
	}
	QGeoCoordinate topLeft = objRect->property("topLeft").value<QGeoCoordinate>();
	QGeoCoordinate bottomRight = objRect->property("bottomRight").value<QGeoCoordinate>();
	int x0 = floor(topLeft.longitude());
	left = x0;
	int x1 = ceil(bottomRight.longitude());
	right = x1;
	int y0 = floor(bottomRight.latitude());
	bottom = y0;
	int y1 = ceil(topLeft.latitude());
	top = y1;

	osm->deleteLater();
}

QWizardPage* MeteoWizard::createRegionPage()
{
	QWizardPage* page = new QWizardPage;

	page->setTitle(str_region_page_title);

	QVBoxLayout* layout = new QVBoxLayout;

	if (!m_json) {
		m_ll_region->m_x = 0;
		m_ll_region->m_width = 40;
		m_ll_region->m_y = 30;
		m_ll_region->m_height = 20;
		m_ll_region->m_ll_step = 2.0;
	}
	m_osm = quick_map_create(NULL, m_ll_region->m_x, m_ll_region->m_x + m_ll_region->m_width, m_ll_region->m_y + m_ll_region->m_height, m_ll_region->m_y);
	layout->addWidget((QWidget*)m_osm);

	QHBoxLayout* hbox = new QHBoxLayout;
	hbox->addWidget(new QLabel(str_grid_step));

	m_region_step = new QDoubleSpinBox;

	m_region_step->setValue(m_ll_region->m_ll_step);
	m_region_step->setSingleStep(0.1);
	hbox->addWidget(m_region_step);
	hbox->addStretch();
	layout->addLayout(hbox);

	page->setLayout(layout);
	m_osm->show();
	return page;
}

cv::Mat* MeteoWizard::openMsg(const wchar_t* fname, ll_region_c* ll_region)
{
	int n0 = 0, n1 = 0;
	cv::Mat* msg = dwtOpen(fname, ll_region->m_rect, n0, n1);
	if (msg) {
		SuplDebugMat(msg);

		Rect rc1(ll_region->m_rect);
		rc1.y -= (8 - n0) * MSAT_STRIP_DIM;
		cv::Mat* clip = new cv::Mat(*msg, rc1);
		SuplDebugMat(clip);

		cv::Mat* remap = ll_region->imgRemap(clip);
		SuplDebugMat(remap);

		delete msg;
		return remap;
	}
	return nullptr;
}

void MeteoWizard::accept()
{
	QGuiApplication::setOverrideCursor(Qt::WaitCursor);
	QGuiApplication::processEvents();

	m_wiz_params->msg_path = m_msg_path->text();
	m_wiz_params->jpg_path = m_jpg_path->text();
	m_wiz_params->shp_path = m_shp_path->text();
	m_wiz_params->fname_pref = m_fname_pref->text();
	m_wiz_params->arrow_scale = m_arrow_scale->value();
	m_wiz_params->arrow_width = m_arrow_width->value();

	int year0 = m_calendar0->selectedDate().year();
	int mon0 = m_calendar0->selectedDate().month();
	int day0 = m_calendar0->selectedDate().day();

	int year1 = m_calendar1->selectedDate().year();
	int mon1 = m_calendar1->selectedDate().month();
	int day1 = m_calendar1->selectedDate().day();

	int minutes0 = m_minutes0->currentIndex();
	int minutes1 = m_minutes1->currentIndex();

	int hour0 = minutes0 / 4;
	int mn0 = 15 * (minutes0 % 4);
	int hour1 = minutes1 / 4;
	int mn1 = 15 * (minutes1 % 4);

	m_wiz_params->start = date_c(year0, mon0, day0, hour0, mn0);
	m_wiz_params->stop = date_c(year1, mon1, day1, hour1, mn1);

	bool msg_type = m_msg_type->isChecked();
	m_wiz_params->msg = msg_type ? 4 : 3;

	m_dates->clear();
	m_wiz_params->start.hour_range(m_wiz_params->stop, m_dates);

	if (m_dates->size() < 2) {
		QGuiApplication::restoreOverrideCursor();
		QMessageBox::information(nullptr, "MeteoWizard", str_time_slot_undermine_message);
		QDialog::reject();
		return;
	}

	m_wiz_params->channel_idx = m_channel_tag->currentIndex();
	QString channel = channel_tags[m_wiz_params->channel_idx + 1];

	m_wiz_params->arrow_color = m_arrow_color->getColor();

	m_ll_region->m_ll_step = m_region_step->value();

	double left, right, top, bottom;
	QObject* rect = m_osm->rootObject()->findChild<QObject*>("redRect");
	quick_map_done(rect, m_osm, left, right, top, bottom);

	m_ll_region->m_x = left;
	m_ll_region->m_width = right - left;
	m_ll_region->m_y = bottom;
	m_ll_region->m_height = top - bottom;

	m_ll_region->geo2Rect();

	if (!QDir::setCurrent(m_wiz_params->working_dir) || !QDir::setCurrent(m_wiz_params->shp_path))
		qDebug() << str_error_blank << "SetCurrentDirectory\n";

	for (int i = 0; i < m_shp_files->size(); i++) {
		shp_c* shp = (*m_shp_files)[i];
		shp_c* shp0 = shp_c::shpProc(shp->m_shp_name, m_ll_region);
		if (shp0) {
			vector<shape_c*>* tmp = shp0->m_shape;
			shp0->m_shape = nullptr;
			delete shp0;
			shp->m_shape = tmp;
		}
		else
			qDebug() << str_error_blank << "shpProc\n";
	}

	date_c& d0 = (*m_dates)[0];
	wchar_t msg_fname[100], jpg_fname[100];
	cv::Mat* img0;
	{
		if (!QDir::setCurrent(m_wiz_params->working_dir) || !QDir::setCurrent(m_wiz_params->msg_path))
			qDebug() << str_error_blank << "SetCurrentDirectory 1\n";
		swprintf(msg_fname, MSAT_NAME_FORMAT, m_wiz_params->msg, m_wiz_params->msg, channel.utf16(), 7, d0.m_year, d0.m_mon, d0.m_day, d0.m_hour, d0.m_mn);//L"WV_062"
		img0 = openMsg(msg_fname, m_ll_region);
		SuplDebugMat(img0);
	}
	for (int i = 1; i < m_dates->size(); i++) {
		date_c& d = (*m_dates)[i];
		
		if (!QDir::setCurrent(m_wiz_params->working_dir) || !QDir::setCurrent(m_wiz_params->msg_path))
			qDebug() << str_error_blank << "SetCurrentDirectory 2\n";
		swprintf(msg_fname, MSAT_NAME_FORMAT, m_wiz_params->msg, m_wiz_params->msg, channel.utf16(), 7, d.m_year, d.m_mon, d.m_day, d.m_hour, d.m_mn);
		
		cv::Mat* img1 = openMsg(msg_fname, m_ll_region);
		SuplDebugMat(img1);

		int daym = date_c::day_in_mon(d0.m_year, d0.m_mon);
		int dt_mn = 0;
		if (d.m_mn > d0.m_mn)
			dt_mn = d.m_mn - d0.m_mn;
		else if (d.m_hour == d0.m_hour + 1
			|| d.m_day == d0.m_day + 1 && d.m_hour == 0 && d0.m_hour == 23
			|| daym == d0.m_day && d.m_mon == d0.m_mon + 1 && d.m_hour == 0 && d0.m_hour == 23)
			dt_mn = 60 + d.m_mn - d0.m_mn;

		vpainter_c vpnt;
		painter_c* pnt1 = new painter_c();
		pnt1->drawImage(img0);
		vpnt.m_painter.push_back(pnt1);

		vector<cv::Mat*> vrgb;
		vector<wstring> vrgb_fname;
		if (m_rgb_flag->isChecked()) {
			for (int k = 0; k < m_rgbSetList->count(); k++) {
				auto item = m_rgbSetList->item(k);
				QVariant var = item->data(Qt::UserRole);
				const params_channels_c& p = qvariant_cast<params_channels_c>(var);
				QString str = item->text();

				cv::Mat* rgb = makeRgb(d, p);
				vrgb.push_back(rgb);

				painter_c* pnt2 = new painter_c();
				pnt2->drawImage(rgb);
				vpnt.m_painter.push_back(pnt2);
				
				wchar_t rgb_fname[100];
				wsprintf(rgb_fname, L"%s-%04d%02d%02d%02d%02d.jpg", str.toStdWString().c_str(), d.m_year, d.m_mon, d.m_day, d.m_hour, d.m_mn);
				vrgb_fname.push_back(wstring(rgb_fname));
			}
		}		
		
		vpnt.outputUV(m_ll_region, m_shp_files, m_wiz_params, dt_mn, img0, img1);

		if (!QDir::setCurrent(m_wiz_params->working_dir) || !QDir::setCurrent(m_wiz_params->jpg_path))
			qDebug() << str_error_blank << "SetCurrentDirectory 3\n";
		swprintf(jpg_fname, L"%s_%s_%d_%d_%d_%d_%d.jpg", m_wiz_params->fname_pref.utf16(), channel.utf16(), d.m_year, d.m_mon, d.m_day, d.m_hour, d.m_mn);

		imwrite(SuplName16to8(jpg_fname), *vpnt.m_painter[0]->m_rgb);

		for (int m = 0; m < vrgb.size(); m++) {
			imwrite(SuplName16to8(vrgb_fname[m].c_str()), *vpnt.m_painter[m + 1]->m_rgb);
			delete vrgb[m];
		}

		delete img0;
		img0 = img1;
	}
	delete img0;
		
	QGuiApplication::restoreOverrideCursor();
	QGuiApplication::processEvents();
	QMessageBox::information(nullptr, "MeteoWizard", str_generation_succeeded);

	QDir::setCurrent(m_wiz_params->working_dir);
	if (!m_wiz_params->write_settings(*m_wiz_params, m_ll_region, *m_shp_files, "settings.json"))
		qDebug() << str_error_blank << str_saving_nocap << " JSON\n";

	QDialog::accept();
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	MeteoWizard* dw = new MeteoWizard(nullptr);
	dw->setWizardStyle(QWizard::WizardStyle::ModernStyle);
	
	dw->addPage(dw->createIntroPage());
	dw->addPage(dw->createDateTimePage());
	dw->addPage(dw->createShapePage());
	dw->addPage(dw->createRegionPage());
	dw->addPage(dw->createPostProcPage());

	dw->setWindowTitle(str_data_processing_wizard);
	dw->resize(QSize(700, 500));
	dw->show();

	app.exec();

	delete dw;
	return 0;
}
