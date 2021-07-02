#pragma once

#include <string>
#include <vector>
using namespace std;

#include <QString>
#include <QColor>

#include <opencv2/core/core.hpp>

class shape_c
{
public:
  vector<vector<cv::Point2f>*>  *m_pline;
  QString                       m_lab;
  int                           m_shp_type;
  int                           m_popul;
  
  shape_c() : m_shp_type(0), m_popul(0) { m_pline = new vector<vector<cv::Point2f>*>(); }
  ~shape_c() {
    if (m_pline) for_each(m_pline->begin(), m_pline->end(), [](vector<cv::Point2f> *p) { delete p; });
    delete m_pline;
  }

  static vector<shape_c*>*              shapeLoad(QString name, int dbf_name, int dbf_pop, int charset);
  static vector<pair<string, int>>*     getDbfFldNames(QString fname);
  static int                            dbfFldIdx(const string& attr, const vector<pair<string, int>>& flds);
};
