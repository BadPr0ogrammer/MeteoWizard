#include <QtCore>

#include <opencv2/core/core.hpp>

#include <shapefil.h>

using namespace std;
using namespace cv;
/*
#include "defs.h"
#include "staticstr.h"
#include "places.h"
*/
#include "shaperead.h"
/*
#define CHAR_SET_NUM 25
const char* char_set_names[CHAR_SET_NUM] = {
  "WINDOWS-1250", "WINDOWS-1251", "WINDOWS-1252", "WINDOWS-1253", "WINDOWS-1254", "WINDOWS-1255", "WINDOWS-1256", "WINDOWS-1257", "WINDOWS-1258",
  "UTF-8", "UTF-16", "UTF-32"
};
*/
vector<shape_c*>* shape_c::shapeLoad(QString fname, int dbf_name, int dbf_pop, int charset)
{
  QTextCodec* codec = QTextCodec::codecForName("WINDOWS-1251");//char_set_names[charset]
  vector<shape_c*>* ret = nullptr;  
/*
#ifdef _WINDOWS
  wchar_t name[MAX_PATH];
  fname.toWCharArray(name);
  name[fname.length()] = 0;

  SHPHandle shp = SHPOpen(name, "rb");
#else
*/
  SHPHandle shp = SHPOpen(fname.toUtf8(), "rb");
//#endif
  if (!shp || !shp->nRecords) {

    qDebug() << "Ошибка чтения shp файла 1" << endl;

    if (shp)
      SHPClose(shp);
    return ret;
  }

  DBFHandle dbf = nullptr;
  int field_num = 0;
  if (dbf_name >= 0) {
/*
#ifdef _WINDOWS
    dbf = DBFOpen(name, "rb");
#else
*/
    dbf = DBFOpen(fname.toUtf8(), "rb");
//#endif
    if (dbf)
        field_num = DBFGetFieldCount(dbf);
  }

  for (int i = 0; i < shp->nRecords; i++) {
    shape_c *shape = new shape_c();

    SHPObject *obj = SHPReadObject(shp, i);
    if (!obj) {
        qDebug() << "Ошибка чтения shp файла 2" << endl;
      continue;
    }
    shape->m_shp_type = obj->nSHPType;

    int j;
    for (j = 0; j < MAX(1, obj->nParts); j++) {
      int k0 = obj->nParts > 1 ? obj->panPartStart[j] : 0;
      int k1 = obj->nParts > 1 && j < obj->nParts - 1 ? obj->panPartStart[j + 1] : obj->nVertices;
      vector<Point2f> *tmp = new vector<Point2f>();

      int k;
      for (k = k0; k < k1; k++) {
        Point2f pt(obj->padfX[k], obj->padfY[k]);
        tmp->push_back(pt);
      }
      if (tmp->size()) {
        if (!shape->m_pline)
          shape->m_pline = new vector<vector<Point2f>*>();
        shape->m_pline->push_back(tmp);
      }
      else {
          qDebug() << "Ошибка чтения shp файла 3" << endl;
        delete tmp;
      }
    }
    if (shape->m_pline && dbf && field_num > dbf_name) {
      const char *str = DBFReadStringAttribute(dbf, i, dbf_name);
      shape->m_lab = codec->toUnicode(str);
      int n = DBFReadIntegerAttribute(dbf, i, dbf_pop);
      shape->m_popul = n;
    }

    SHPDestroyObject(obj);
    if (shape->m_pline) {
        if (!ret)
            ret = new vector<shape_c*>();
        ret->push_back(shape);
    }
    else {
        qDebug() << "Ошибка чтения shp файла 4" << endl;
      delete shape;
    }
  }
  if (dbf)
    DBFClose(dbf);

  if (shp)
    SHPClose(shp);
  return ret;
}

vector<pair<string, int>>* shape_c::getDbfFldNames(QString fname)
{
/*
 #ifdef _WINDOWS
  wchar_t name[LARGEBUF];
  fname.toWCharArray(name);
  name[fname.length()] = 0;

  DBFHandle dbf = DBFOpen(name, "rb");
#else
*/
  DBFHandle dbf = DBFOpen(fname.toUtf8(), "rb");
//#endif
  vector<pair<string, int>> *ret = nullptr;
  if (dbf) {
    char buf[100];
    int i, num = DBFGetFieldCount(dbf);

    for (i = 0; i < num; i++) {
      memset(buf, 0, 100);
      if (DBFGetFieldInfo(dbf, i, buf, nullptr, nullptr) != FTInvalid && buf[0]) {
        pair<string, int> b;
        //        buf[31] = 0;
        b.first = buf;
        b.second = i;
        if (!ret)
            ret = new vector<pair<string, int>>();
        ret->push_back(b);
      }
    }
    DBFClose(dbf);
  }
  return ret;
}

int shape_c::dbfFldIdx(const string& attr, const vector<pair<string, int>>& flds)
{
  int ret = -1;
  if (!flds.empty() && !attr.empty()) {
    for (int i = 0; i < flds.size(); i++) {
      const pair<string, int> &b = flds[i];
      if (!b.first.compare(attr)) {
        ret = b.second;
        break;
      }
    }
  }
  return ret;
}
