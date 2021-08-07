#include <set>

using namespace std;

#ifndef array_countof
#define array_countof(_a) sizeof(_a)/sizeof(_a[0])
#endif

#define LARGEBUF 300

#include "readgrib.h"

#include "data_class.h"
#include "data2d_grib.h"
#include "data2d_grib2.h"
#include "data2d_factory.h"
#include "grib_strings.h"
#include "vx_data2d.h"
#include "table_lookup.h"
#include "grib1_ncep_2_7.h"
#include "grib2_all.h"
#include "data2d_grib_utils.h"
#include "data_plane.h"

#include <opencv2/core/core.hpp>
#include "supl.h"

//#include "datefcst.h"
//#include "griblatlon.h"

//USE_JPEG2000;USE_PNG;
//..\..\..\opencv-3.4.10\3rdparty\libjasper;..\..\..\opencv-3.4.10\3rdparty\libpng;..\..\..\opencv-3.4.10\3rdparty\libjpeg;src\win32;
//C:\Users\oldman\work\opencv-3.4.10\build\3rdparty\lib\Debug;
//zlibd.lib;libjasperd.lib;libpngd.lib;libjpeg-turbod.lib;
//src;src\g2clib-1.6.0;src\met-5.2_bugfix\src\basic\vx_cal;src\met-5.2_bugfix\src\basic\vx_config;src\met-5.2_bugfix\src\basic\vx_log;src\met-5.2_bugfix\src\basic\vx_math;src\met-5.2_bugfix\src\basic\vx_util;src\met-5.2_bugfix\src\libcode\vx_data2d;src\met-5.2_bugfix\src\libcode\vx_data2d_factory;src\met-5.2_bugfix\src\libcode\vx_data2d_grib2;src\met-5.2_bugfix\src\libcode\vx_data2d_grib;src\met-5.2_bugfix\src\libcode\vx_grid;src\win32;

grib2_c::~grib2_c()
{
	delete m_grib2DataFile;
}

bool grib2_c::set_grib_table()
{
	GribTable = new TableFlatFile();
	if (!GribTable) {
		cerr << "!GribTable error" << "\n";
		return false;
	}
	GribTable->N_grib1_elements = array_countof(grib1_ncep_2_7);
	GribTable->N_grib2_elements = array_countof(grib2_all);
	GribTable->g1e = new Grib1TableEntry * [GribTable->N_grib1_elements];
	if (!GribTable->g1e) {
		cerr << "!GribTable->g1e error" << "\n";
		return false;
	}
	for (int i = 0; i < GribTable->N_grib1_elements; i++) {
		GribTable->g1e[i] = new Grib1TableEntry;
		if (!GribTable->g1e[i]) {
			cerr << "!GribTable->g1e[i] error" << "\n";
			return false;
		}
		GribTable->g1e[i]->code = grib1_ncep_2_7[i].code;
		GribTable->g1e[i]->table_number = grib1_ncep_2_7[i].table_number;
		GribTable->g1e[i]->center = grib1_ncep_2_7[i].center;
		GribTable->g1e[i]->parm_name = grib1_ncep_2_7[i].parm_name;
		GribTable->g1e[i]->full_name = grib1_ncep_2_7[i].full_name;
		GribTable->g1e[i]->units = grib1_ncep_2_7[i].units;
	}
	GribTable->g2e = new Grib2TableEntry * [GribTable->N_grib2_elements];
	if (!GribTable->g2e) {
		cerr << "!GribTable->g2e error" << "\n";
		return false;
	}
	/*
	for (int i = 0; i < 1018; i++) {
	  grib2_all[i].my_id = i;

	  for (int j = 0; j < NGAC_2D_TAG_NUM; j++) {
	  if (QString(tags_ngac2d[j].tag) == QString(grib2_all[i].parm_name)) {
	  tags_ngac2d[j].id = i;
	  break;
	  }
	  }
	}
	*/
	for (int i = 0; i < GribTable->N_grib2_elements; i++) {
		GribTable->g2e[i] = new Grib2TableEntry;
		if (!GribTable->g2e[i]) {
			cerr << "!GribTable->g2e[i] error" << "\n";
			return false;
		}
		GribTable->g2e[i]->index_a = grib2_all[i].index_a;
		GribTable->g2e[i]->mtab_set = grib2_all[i].mtab_set;
		GribTable->g2e[i]->mtab_low = grib2_all[i].mtab_low;
		GribTable->g2e[i]->mtab_high = grib2_all[i].mtab_high;
		GribTable->g2e[i]->cntr = grib2_all[i].cntr;
		GribTable->g2e[i]->ltab = grib2_all[i].ltab;
		GribTable->g2e[i]->index_b = grib2_all[i].index_b;
		GribTable->g2e[i]->index_c = grib2_all[i].index_c;
		GribTable->g2e[i]->parm_name = grib2_all[i].parm_name;
		GribTable->g2e[i]->full_name = grib2_all[i].full_name;
		GribTable->g2e[i]->units = grib2_all[i].units;
	}
	return true;
}

grib2_c* grib2_c::read_info_grib(string filename)
{
	grib2_c* grib = new grib2_c();
	Met2dDataFileFactory* factory = new Met2dDataFileFactory();
#ifdef DEBUG
	if (!factory) {
		cerr << L"error!\n";//, "0x378a803e");
		return false;
	}
#endif

#ifdef _WINDOWS
	wstring buf = SuplName8to16(filename.c_str());
	Met2dDataFile* p = factory->new_met_2d_data_file(buf.c_str());
	grib->m_grib2DataFile = (MetGrib2DataFile*)p;
#else
	datafile = (MetGrib2DataFile*)factory->new_met_2d_data_file(filename.toUtf8().data());
#endif
	delete factory;
	factory = NULL;

	if (!grib->m_grib2DataFile) {
		cerr << "!grib2DataFile error" << "\n";
		delete grib;
		return nullptr;
	}

	const Grid& grid = grib->m_grib2DataFile->grid();
	const GridInfo& gi = grid.info();

	if (!gi.ll) {
		cerr << L"!gi.ll error!\n";
		delete grib;
		return nullptr;
	}
	grib->m_reg.m_delta = gi.ll->delta_lon;
	grib->m_reg.m_lat_ll = gi.ll->lat_ll;
	grib->m_reg.m_lon_ll = -gi.ll->lon_ll;//WEST!!!
	//reg.m_delta_lat = gi.ll->delta_lat;
	grib->m_ny = gi.ll->Nlat;
	grib->m_nx = gi.ll->Nlon;

	if (grib->m_reg.m_lon_ll == 0 && grib->m_reg.m_lon_ll + gi.ll->Nlon * grib->m_reg.m_delta == 360)
		grib->m_reg.m_lon_ll = -180;

	if (grib->m_reg.m_delta <= 0) {
		cerr << L"reg.m_delta <= 0 error!\n";
		delete grib;
		return nullptr;
	}

	for (auto it = grib->m_grib2DataFile->RecList.begin(); it != grib->m_grib2DataFile->RecList.end(); it++) {
		Grib2Record* rec = *it;
		if (!rec || rec->ParmName.empty()) {
			cerr << L"!rec || rec->ParmName.empty() error!\n";
			continue;
		}
		DataPlane* plane = new DataPlane();
		if (grib->m_grib2DataFile->read_grib2_record_data_plane(rec, *plane) && plane->data()) {
			grib2_rec_c *grib2_rec = new grib2_rec_c(rec, plane);
			
			string level = grib2_c::get_lval(rec->LvlVal1);
			string ltype = to_string(rec->LvlTyp);
			string tag = rec->ParmName;
			tag += ":";
			tag += level;
			tag += ":";
			tag += ltype;
			grib->m_grib2DataPlanes[tag] = grib2_rec;
			if (rec->ParmName == "UGRD")
				grib->m_U[level] = grib2_rec;
			else if (rec->ParmName == "VGRD")
				grib->m_V[level] = grib2_rec;
		}
		else {
			cerr << L"!plane->data() error!\n";
			delete plane;
		}
	}
	return grib;
}

string grib2_c::get_lval(double LvlVal1)
{
	string lval;
	if (fabs(LvlVal1) > FLT_EPSILON && fabs(LvlVal1) < 100)
		lval = to_string(abs((int)LvlVal1));
	else
		lval = to_string((int)(LvlVal1 / 100.0));
	return lval;
}

void grib2_c::get_min_max(double &vmin, double &vmax)
{
	vmin =  1.e9;
	vmax = -1.e9;
	//for (auto it = m_grib2DataPlanes.begin(); it != m_grib2DataPlanes.end(); it++) {
	//	pair<std::string, grib2_rec_c* > pair_rec = *it;
	//	double* dbl = pair_rec.second->m_plane->data_ptr();
	for (auto itu = m_U.begin(), itv = m_V.begin(); itu != m_U.end() && itv != m_V.end(); itu++, itv++) {
		pair<std::string, grib2_rec_c* > u = *itu;
		pair<std::string, grib2_rec_c* > v = *itv;
		
		double* up = u.second->m_plane->data_ptr();
		double* vp = v.second->m_plane->data_ptr();
		for (int j = 0; j < m_ny; j++) {
			for (int i = 0; i < m_nx; i++) {
				//double val = dbl[i + j * m_nx];
				//if (val == BAD_VALUE_m9999)
				//	continue;
				if (up[i + j * m_nx] == BAD_VALUE_m9999 || vp[i + j * m_nx] == BAD_VALUE_m9999)
					continue;
				double val = _hypot(up[i + j * m_nx], vp[i + j * m_nx]);
				if (val > vmax)
					vmax = val;
				if (val < vmin)
					vmin = val;
			}
		}
	}
}
