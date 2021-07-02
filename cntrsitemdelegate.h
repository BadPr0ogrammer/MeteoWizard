#ifndef DLG_STARTUP_C_H
#define DLG_STARTUP_C_H

#include <list>

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QDialog>
#include <QStyledItemDelegate>

class shp_c;

enum {
    CNTRS_FILE_NAME, CNTRS_DBF_PLS_PARAM, CNTRS_TEXT_COLOR, CNTRS_LINE_COLOR, CNTRS_LINE_WIDTH, CNTRS_DASHED, CNTRS_FONT, CNTRS_FONT_SIZE, CNTRS_NUM
};

class cntrs_item_delegate_c : public QStyledItemDelegate
{
    Q_OBJECT
public:
    const std::vector<shp_c*>* m_shp_files;

    cntrs_item_delegate_c(const std::vector<shp_c*>* vec, QObject* parent) : QStyledItemDelegate(parent), m_shp_files(vec) {}
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget* editor, const QModelIndex& index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const Q_DECL_OVERRIDE;

private slots:
    void commit_and_close();
};

#endif // DLG_STARTUP_C_H
