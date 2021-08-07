#pragma once

#include <string>
#include <map>

typedef struct grib1_tbl_t {
	int   code;
	int   table_number;
	int   center;
	int   subcenter;
	const char* parm_name;
	const char* full_name;
	const char* units;
} grib1_tbl_t;

typedef struct grib2_tbl_t {
	int index_a;
	int mtab_set;
	int mtab_low;
	int mtab_high;
	int cntr;
	int ltab;
	int index_b;
	int index_c;
	const char* parm_name;
	const char* full_name;
	const char* units;
	const char* short_name;
	int my_id;
} grib2_tbl_t;

class rtlv_c
{
public:
	std::string  m_role;
	std::string  m_tag;
	std::string  m_lev;
	std::string  m_lval;
	rtlv_c() {}
	rtlv_c(const rtlv_c& param)
		: m_role(param.m_role), m_tag(param.m_tag), m_lev(param.m_lev), m_lval(param.m_lval) {}
	rtlv_c(const std::string& role, const std::string& tag, const std::string& lev, const std::string& lval)
		: m_role(role), m_tag(tag), m_lev(lev), m_lval(lval) {}
	void clear() { m_role.clear(); m_tag.clear(); m_lev.clear(); m_lval.clear(); }
	bool is_empty() const { return m_role.empty() || m_tag.empty() || m_lev.empty() || m_lval.empty(); }
	bool operator== (const rtlv_c& rhs) const {
		if (m_role == rhs.m_role && m_tag == rhs.m_tag && m_lev == rhs.m_lev && m_lval == rhs.m_lval) return true;
		return false;
	}
};

extern grib1_tbl_t grib1_ncep_2_7[1024];
#define GRIB2_ALL_NUM 1018
extern grib2_tbl_t grib2_all[GRIB2_ALL_NUM];

#include "griblatlon.h"

struct Grib2Record;
class DataPlane;
class MetGrib2DataFile;

class grib2_rec_c 
{
public:
	Grib2Record* m_rec;
	DataPlane* m_plane;

	grib2_rec_c() : m_rec(nullptr), m_plane(nullptr) {}
	grib2_rec_c(Grib2Record* rec, DataPlane* plane) : m_rec(rec), m_plane(plane) {}
};

class grib2_c
{
public:
	MetGrib2DataFile* m_grib2DataFile;
	std::map<std::string, grib2_rec_c*> m_grib2DataPlanes;
	dlatlon_c m_reg;
	int m_nx, m_ny;
	std::map<std::string, grib2_rec_c*> m_U;
	std::map<std::string, grib2_rec_c*> m_V;

	grib2_c() : m_grib2DataFile(nullptr), m_nx(0), m_ny(0) {}
	~grib2_c();

	static grib2_c* read_info_grib(string filename);
	static bool set_grib_table();	
	static std::string get_lval(double LvlVal1);

	void get_min_max(double& vmin, double& vmax);
};

#define BAD_VALUE_m9999         (-9999.)