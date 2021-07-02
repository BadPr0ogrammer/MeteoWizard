#include <iostream>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFontComboBox>
#include <QFileDialog>
#include <QMessageBox>

#include <opencv2/core/core.hpp>

#include "inc.h"

#include "dwtopen.h"
#include "datec.h"
#include "shpproc.h"
#include "cntrsitemdelegate.h"

using namespace std;
using namespace cv;

const char* dash_line_names[DASH_LINE_NAME_NUM] = { "сплошная","пунктирная","штрих-пунктир" };

QWidget* cntrs_item_delegate_c::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QWidget* editor = nullptr;

	int col = index.column();
	int row = index.row();
	if (m_shp_files == nullptr || m_shp_files->size() <= row)
		return nullptr;
	shp_c* shp = (*m_shp_files)[row];

	switch (col) {
	case CNTRS_FILE_NAME:
		editor = (QWidget*) new QLineEdit(parent);
		break;
	case CNTRS_TEXT_COLOR: {
		editor = (QWidget*) new QPushButton(parent);
		QPushButton* btn = (QPushButton*)editor;
		QColor color = QColorDialog::getColor(shp->m_text_color);
		if (color.isValid()) {
			QPalette palette = btn->palette();
			palette.setColor(QPalette::Button, color);
			btn->setPalette(palette);

			shp->m_text_color = color;
		}
		else {
			QPalette palette = btn->palette();
			palette.setColor(QPalette::Button, shp->m_text_color);
			btn->setPalette(palette);
		}
		connect(btn, SIGNAL(clicked()), this, SLOT(commit_and_close()));
		break;
	}
	case CNTRS_LINE_COLOR: {
		editor = (QWidget*) new QPushButton(parent);
		QPushButton* btn = (QPushButton*)editor;
		QColor color = QColorDialog::getColor(shp->m_line_color);
		if (color.isValid()) {
			QPalette palette = btn->palette();
			palette.setColor(QPalette::Button, color);
			btn->setPalette(palette);

			shp->m_line_color = color;
		}
		else {
			QPalette palette = btn->palette();
			palette.setColor(QPalette::Button, shp->m_line_color);
			btn->setPalette(palette);
		}
		connect(btn, SIGNAL(clicked()), this, SLOT(commit_and_close()));
		break;
	}
	case CNTRS_LINE_WIDTH: {
		editor = (QWidget*) new QDoubleSpinBox(parent);
		QDoubleSpinBox* dsb = (QDoubleSpinBox*)editor;
		dsb->setSingleStep(0.1);
		dsb->setMinimum(0.1);
		dsb->setMaximum(10);
		break;
	}
	case CNTRS_DASHED: {
		editor = (QWidget*) new QComboBox(parent);
		QComboBox* cb = (QComboBox*)editor;
		QStringList sl;
		for (int i = 0; i < DASH_LINE_NAME_NUM; i++)
			sl.append(dash_line_names[i]);
		cb->addItems(sl);
		break;
	}
	case CNTRS_FONT:
		editor = (QWidget*) new QFontComboBox(parent);
		break;
	case CNTRS_FONT_SIZE: {
		editor = (QWidget*) new QSpinBox(parent);
		QSpinBox* sb = (QSpinBox*)editor;
		sb->setSingleStep(1);
		sb->setMinimum(1);
		sb->setMaximum(100);
		break;
	}
	default:
		editor = QStyledItemDelegate::createEditor(parent, option, index);
	}

	return editor;
}

void cntrs_item_delegate_c::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	int col = index.column();
	int row = index.row();
	if (m_shp_files == nullptr || m_shp_files->size() <= row)
		return;
	shp_c* shp = (*m_shp_files)[row];

	switch (col) {
	case CNTRS_FILE_NAME: {
		QLineEdit* le = qobject_cast<QLineEdit*>(editor);
		if (le)
			le->setText(shp->m_shp_name);
		break;
	}
	case CNTRS_LINE_WIDTH: {
		QDoubleSpinBox* dsb = qobject_cast<QDoubleSpinBox*>(editor);
		if (dsb)
			dsb->setValue(shp->m_line_width);
		break;
	}
	case CNTRS_DASHED: {
		QComboBox* cb = qobject_cast<QComboBox*>(editor);
		if (cb)
			cb->setCurrentIndex(shp->m_dash);
		break;
	}
	case CNTRS_FONT: {
		QFontComboBox* fcb = qobject_cast<QFontComboBox*>(editor);
		if (fcb) {
			QFont font(shp->m_font_face, shp->m_font_size);
			fcb->setCurrentFont(font);
		}
		break;
	}
	case CNTRS_FONT_SIZE: {
		QSpinBox* sb = qobject_cast<QSpinBox*>(editor);
		if (sb)
			sb->setValue(shp->m_font_size);
		break;
	}
	default:
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void cntrs_item_delegate_c::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	int col = index.column();
	int row = index.row();
	if (m_shp_files == nullptr || m_shp_files->size() <= row)
		return;
	shp_c* shp = (*m_shp_files)[row];

	switch (col) {
	case CNTRS_DBF_PLS_PARAM: {
		QLineEdit* le = qobject_cast<QLineEdit*>(editor);
		if (le) {
			shp->m_dbf_field = le->text();
			model->setData(index, shp->m_dbf_field);
		}
		break;
	}
	case CNTRS_TEXT_COLOR: {
		QPushButton* btn = qobject_cast<QPushButton*>(editor);
		shp->m_text_color = btn->palette().color(QPalette::Button);
		model->setData(index, shp->m_text_color);

		QStandardItem* item = qobject_cast<QStandardItemModel*>(model)->itemFromIndex(index);
		if (item) {
			item->setBackground(QBrush(shp->m_text_color));
			//info->cntrs_ptr()->set_text_color(info->text_c());
		}
		break;
	}
	case CNTRS_LINE_COLOR: {
		QPushButton* btn = (QPushButton*)editor;
		shp->m_line_color = btn->palette().color(QPalette::Button);
		model->setData(index, shp->m_line_color);

		QStandardItem* item = qobject_cast<QStandardItemModel*>(model)->itemFromIndex(index);
		if (item) {
			item->setBackground(QBrush(shp->m_line_color));
			//info->cntrs_ptr()->set_line(info->line_c(), info->line_w(), info->dash());
		}
		break;
	}
	case CNTRS_LINE_WIDTH: {
		QDoubleSpinBox* dsb = qobject_cast<QDoubleSpinBox*>(editor);
		if (dsb) {
			shp->m_line_width = (float)dsb->value();
			model->setData(index, QString::number(shp->m_line_width));
			//info->cntrs_ptr()->set_line(info->line_c(), info->line_w(), info->dash());
		}
		break;
	}
	case CNTRS_DASHED: {
		QComboBox* cb = qobject_cast<QComboBox*>(editor);
		if (cb) {
			shp->m_dash = cb->currentIndex();
			model->setData(index, dash_line_names[shp->m_dash]);
			//info->cntrs_ptr()->set_line(info->line_c(), info->line_w(), info->dash());
		}
		break;
	}
	case CNTRS_FONT: {
		QFontComboBox* fcb = qobject_cast<QFontComboBox*>(editor);
		if (fcb) {
			shp->m_font_face = fcb->currentFont().family();
			model->setData(index, shp->m_font_face);
			//info->cntrs_ptr()->set_font(info->font_face(), info->font_size());
		}
		break;
	}
	case CNTRS_FONT_SIZE: {
		QSpinBox* sb = qobject_cast<QSpinBox*>(editor);
		if (sb) {
			shp->m_font_size = sb->value();
			model->setData(index, QString::number(shp->m_font_size));
			//info->cntrs_ptr()->set_font(info->font_face(), info->font_size());
		}
		break;
	}
	}
}

void cntrs_item_delegate_c::commit_and_close()
{
	if (QWidget* pb = qobject_cast<QWidget*>(sender())) {
		emit commitData(pb);
		emit closeEditor(pb);
	}
}
