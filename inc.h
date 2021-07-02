#pragma once

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define LARGEBUF            256

#define MSAT_WIDTH          3712
#define MSAT_STRIP_DIM      464
#define MSAT_NAME_LEN       61

#define LON_SCALE           60.0f
#define LAT_SCALE           60.0f

#define BOX_MIN_MAX(_x, _y, _x_min, _x_max, _y_min, _y_max) \
if (_x > _x_max) _x_max = _x; \
if (_x < _x_min) _x_min = _x; \
if (_y > _y_max) _y_max = _y; \
if (_y < _y_min) _y_min = _y

#define CANVAS_MAG			120.0

#define MSAT_NAME_FORMAT L"H-000-MSG%d__-MSG%d________-%s___-00000%d___-%04d%02d%02d%02d%02d-C_"

#define DATE_FORMAT "%04d%02d%02d"

#define DEF_DBF_PLS_PARAM "name;pop_max"

#define DASH_LINE_NAME_NUM 3
extern const char* dash_line_names[DASH_LINE_NAME_NUM];

extern const char* channel_tags[];
