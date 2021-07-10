/******************************************************************************
 *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
 *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
 *                      contract of INM, within he context of the EUMETSAT
 *                      Satellite Application facility on Nowcasting
 *                      and Short Range Forecasting, under the Cooperation
 *                      Agreement dated on 05 December 1996, between EUMETSAT
 *                      and INM.
 *  PROJECT     :       SAFNWC
 *  UNIT NAME   :       LIBNWC
 *  FILE        :       libnwc_basictypes.h
 *  TYPE        :       NWCLIB/LIBNWC
 *
 *  FUNCTION    :       This module defines the basic types and constants used
 *                      by the SAFNWC/MSG application
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  SEP 2006  v2.0     GMV     SAFNWC/MSG v2.0
 *                              SPR-SAF-NWC-IOP-0217 : SMR-SAF-NWC-IOP-0200
 *                              SPR-SAF-NWC-IOP-0230 : SMR-SAF-NWC-IOP-0209
 *                              SPR-SAF-NWC-IOP-0220 : SMR-SAF-NWC-IOP-0219
 *                              SPR-SAF-NWC-IOP-0233 : SMR-SAF-NWC-IOP-0213
 *                              SPR-SAF-NWC-IOP-0236 : SMR-SAF-NWC-IOP-0217
 *                              SPR-SAF-NWC-IOP-0246 : SMR-SAF-NWC-IOP-0229
 *
 *  FEB 2008  v2008    GMV     SAFNWC/MSG v2008
 *                              SPR-SAF-NWC-CDOP-0302 : SMR-SAF-NWC-CDOP-0288
 *                              SPR-SAF-NWC-CDOP-0314 : SMR-SAF-NWC-CDOP-0295
 *                              SPR-SAF-NWC-CDOP-0341 : SMR-SAF-NWC-CDOP-0318
 *
 *  NOV 2008  v2009    GMV     SAFNWC/MSG v2009
 *                              SPR-SAF-NWC-CDOP-0362 : SMR-SAF-NWC-CDOP-0339
 *
 *  JUN 2009  v2010    GMV     SAFNWC/MSG v2010
 *                              SPR-SAF-NWC-CDOP-0367 : SMR-SAF-NWC-CDOP-0345
 *                              PGE13 Creation
 *  JUL 2010  v2011    GMV     SAFNWC/MSG v2011
 *                              SPR-SAF-NWC-CDOP-0435 : SMR-SAF-NWC-CDOP-0417
 *  OCT 2010  v2011    GMV     SAFNWC/MSG v2011
 *                              SPR-SAF-NWC-CDOP-0446 : SMR-SAF-NWC-CDOP-0422
 *  OCT 2011  v2012    GMV     SAFNWC/MSG v2012
 *                              SPR-SAF-NWC-CDOP-0477 : SMR-SAF-NWC-CDOP-0453
 *                              SPR-SAF-NWC-CDOP-0478 : SMR-SAF-NWC-CDOP-0458
 * MAY 2013  v2013     GMV     SAFNWC/MSG v2013
 *                              SPR-SAF-NWC-CDOP-0535 : SMR-SAF-NWC-CDOP-XXXX
 *                              SPR-SAF-NWC-CDOP2-0536 : SMR-SAF-NWC-CDOP2-xxxx
 *
 ****************************************************************************/

#ifndef __LIBNWC_BASICTYPES_H__
#define __LIBNWC_BASICTYPES_H__

#include <math.h>


/* ---------------------------- Maximum values ------------------------------ */
#define MAX_ERROR_MESSAGES  1000
#define MAX_SIZE_PARAM       240
#define MAX_KEYWORD_STRING    25
#define MAX_VALUE_STRING     160
#define MAX_REGION_NAME       13
#define MAX_DATABUF_NAME     255
#define MAX_LOG_ENTRY        400
#define MAX_LINE_STRING (MAX_VALUE_STRING + MAX_KEYWORD_STRING + 20)

/* ----------------------------- Boolean values ----------------------------- */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* --------------------------- Number of total PGEs ------------------------- */
#define NUM_PGES   14

/* ---------------------------- Environment values -------------------------- */
#define SAFNWC_HOME_ENV_VAR  "SAFNWC"
#define DATABUF_DIR          "/tmp/"
#define CONFIG_DIR           "/config/"
#define OUTPUT_DIR           "/export/"
#define SEV_IMPORT           "/import/SEVIRI_data/"
#define NWP_IMPORT           "/import/NWP_data/"
#define NWP_CONF_FILE        "nwp_conf_file"
#define SAT_CONF_FILE        "sat_conf_file"
#define STRING_NULL          "\0"

/* ------------------------------ Logging values ---------------------------- */
#define MESSAGE_SAFNWC_ID_LOG            2
#define LOG_CODE                         0
#define MESSAGE_QUEUE_ID               's'

/* ---------------------------- MSG name convention ------------------------- */
#define MSG1_ID        321
#define MSG2_ID        322
#define MSG3_ID        323

/* ------------------------------- Time macros ------------------------------ */
#define UTC_JULIAN_REFERENCE   "19580101000000"
#define DAYS_JULIAN_REFERENCE           2436205
#define JDFROM1970                  4382.500000
#define SECONDS_IN_DAY                    86400
#define AVERAGE_DAYS_PER_YEAR            365.25

/* ---------------------------- Trigonometric macros ------------------------ */
#define PI M_PI
#define DEG2RAD      PI/180
#define RAD2DEG      180/PI
#define MILLIDEG2DEG  0.001

/* ---------------------------- Idealized Earth radius ---------------------- */
#define EQUATOR_EARTH_RADIUS  6378.1690  /* Earth Equator radius (Km)   */
#define POLE_EARTH_RADIUS     6356.5838  /* Earth Pole radius    (Km)   */
#define SATELLITE_HEIGHT     42164       /* Distance to the Earth centre (Km) */

/* ---------------------------- Physics constants --------------------------- */
#define ZERO_KELVIN                   273.15
#define C_LIGHT                  299792458.0  /* Speed of light  (m/s)   */
#define K_BOLTZ                1.3806503e-23  /* Boltzman constant (J/K) */
#define H_PLANCK               6.6260688e-34  /* Planck constant (J s)   */
#define DRY_AIR_GAS_CONSTANT         287.048  /* Gas constant for Dry Air*/
#define WATER_V_GAS_CONSTANT         461.500  /* Gas constant for water  */
#define DA_WV_RATIO            (DRY_AIR_GAS_CONSTANT/WATER_V_GAS_CONSTANT)
#define WV_DA_RATIO            (WATER_V_GAS_CONSTANT/DRY_AIR_GAS_CONSTANT)
#define AVOGADRO_NUMBER           6.0221e+23
#define DRY_AIR_MOLAR_MASS         28.964e-3
#define WATER_MOLAR_MASS          18.0159e-3
#define EARTH_ROTATION_SPEED     7.292116e-5  /* Rad/s */
#define MEAN_GRAVITY                 9.80665  /* m/s2  */
#define PLANCK_C1             1.19104273e-16 /* 2hc2 */
#define PLANCK_C2               0.0143877523 /* hc/k */

/* ----------------------------- NWP constants ------------------------------ */
/* MAX_FORECAST_TERM removed and configured in the nwp_conf_file */
#define MAX_FORECAST_VALIDITY   6

/* -------------------- Satellite reference threshold  ---------------------- */
#define SAT_REF_THRESHOLD    15    /* TBC  */

/* ------------------------ Basic types definitions ------------------------- */

/* This definitions could be changed, by adding code and compiler directives*/
/* if different data representations are identified among the workstations  */
/* where SAFNWC will operate                                                */

typedef unsigned char           U_byte;
typedef unsigned short int      U_short;
typedef unsigned int            U_int;
typedef signed char             S_byte;
typedef signed short int        S_short;
typedef signed int              S_int;
typedef float                   Float_32;
typedef double                  Float_64;
#ifdef __x86_64
   typedef signed long      S_long;
   typedef unsigned long    U_long;
#else
   typedef signed int       S_long;
   typedef unsigned int     U_long;
#endif


typedef char *File_name;

typedef char Boolean;

typedef struct {
        U_short day;
        U_int  milliseconds;
} Short_CDS_time;

typedef struct {
        U_short day;
        U_int  milliseconds;
        U_short microseconds;
} CDS_time;

typedef struct {
        U_short day;
        U_int  milliseconds;
        U_short microseconds;
        U_short nanoseconds;
} Expanded_CDS_time;

typedef struct {
        U_int  seconds;
        U_short milliseconds;
} CUC_time;

typedef char YYYYMMDDhhmm[13];
typedef char YYYYMMDDhhmm_hh[16];
typedef char Time_generalized[16];
typedef char Time_generalized_exp[26];

typedef char UTC[15];

typedef double  JD;

typedef enum  {
        OK=0,         // No error                                           
        WARNING,      // Error wich does not disable processing             
        FAILURE,      // High level error wich disables processing          
        ERROR         // Low level error to be managed by the higher element
} Status;

/* ----------------------------- Entities list ------------------------------ */
typedef enum  {
        TM=0,
        PGE01_INST,
        PGE01_PREP,
        PGE01_EXEC,
        PGE02_INST,
        PGE02_PREP,
        PGE02_EXEC,
        PGE03_INST,
        PGE03_PREP,
        PGE03_EXEC,
        PGE04,
        PGE05,
        PGE06,
        PGE07,
        PGE08,
        PGE09,
        PGE10,
        PGE11,
        PGE12,
        PGE13,
        PGE14,
        MPEF,
        SEV,
        NWCLIB
} Sender_id;

/* ------------------------------ Channel types ----------------------------- */
typedef enum  {
        HRV,            /* High resolution SEVIRI channel (HRV) */
        VIS_IR          /* Other SEVIRI channels (VIS and IR)   */
} Channel_type;

/* ----------------------------- Error codes -------------------------------- */
/* barh
typedef enum  {
#include "CMa_error_codes"
#include "CT_error_codes"
#include "CTTH_error_codes"
#include "PC_error_codes"
#include "CRR_error_codes"
#include "HRW_error_codes"
#include "ASII_error_codes"
#include "RDT_error_codes"
#include "SPhR_error_codes"
#include "PPh_error_codes"
#include "TM_error_codes"
#include "NWCLIB_error_codes"
} Error_code;
*/
/* ----------------------------- Error messages ----------------------------- */
typedef struct MessageError {
  long  id;                       /* message id: Destination */
  char parameter[MAX_SIZE_PARAM]; /* parameters              */
} MessageError;

/* -------------------------- Pixel data types ------------------------------ */
typedef enum  {
        CNT=0,
        RAD,
        BT,
        REFL
} Data_type;


/* -------------------------- Pixel coordinates ----------------------------- */
/* all indices are started at 1 for line and columns    */
/* increasing indices directions: S-N and E-W           */
typedef struct {
        Float_64 latitude;              /* Latitude of pixel centre           */
        Float_64 longitude;             /* Longitude of pixel centre          */
        U_int  abs_line_index;         /* line index of point with respect   */
                                        /* respect to full SEVIRI image       */
        U_int  abs_column_index;       /* column index of point with respect */
                                        /* respect to full SEVIRI image       */
        U_int  rel_line_index;         /* line index of point with respect   */
                                        /* respect to processed region        */
        U_int  rel_column_index;       /* column index of point with respect */
                                        /* respect to processed region        */
} Pixel_coords;

/* --------------------------- Region definition ---------------------------- */
typedef struct {
        char region_name[MAX_REGION_NAME];
        Pixel_coords centre;
        Pixel_coords upper_left;
        Pixel_coords upper_right;
        Pixel_coords lower_left;
        Pixel_coords lower_right;
        U_short nb_lines;
        U_short nb_cols;
        Channel_type channel_flag;
        S_short lines_incr; /* Region line increment. 1 for HRV, 3 for VIS   */
        S_short cols_incr;  /* Region column increment. 1 for HRV, 3 for VIS */
} Psing_region, *Psing_region_ptr;


/* ----------------------- Configuration file strcuture --------------------- */
typedef struct {
        char keyword[MAX_KEYWORD_STRING];
        char value[MAX_VALUE_STRING];
} Conf_param, *Conf_param_ptr;

/* ------------------------ Parameter list structure ------------------------ */
struct Param_node {
        Conf_param parameter;
        struct Param_node *next;
};

typedef struct Param_node Conf_param_node, *Conf_param_list;

/* ----------------- Satellite configuration file structure ----------------- */
typedef struct {
   char     msg [100];
   char     mode [4];
   Float_64 prj_ref_long;
   Float_64 sat_ref_long;
   S_int    segment_lines;
   Float_64 ref_alt;
   S_int    nb_cols;
   S_int    nb_lines;
   S_int    nb_cols_hrv;
   S_int    nb_lines_hrv;
   S_int    repeating_cycle;
   S_int    nb_hrv_detectors;
   S_int    nb_sev_detectors;
   S_int    vis_ir_resolution;
   S_int    hrv_resolution;
   char     prod_direction[2];
   Float_64 pixel_sampling;
   Float_64 pixel_sampling_hrv;
   S_int    spin_rate;
   Float_64 scan_delta; /* in seconds */
   Float_64 scan_rate;  /* in milliseconds */

   char     output_format[5];

   Float_64 coff;
   Float_64 loff;
   Float_64 cfac;
   Float_64 lfac;
   Float_64 coff_hrv;
   Float_64 loff_hrv;
   Float_64 cfac_hrv;
   Float_64 lfac_hrv;

   Float_64 hrvis_f;
   Float_64 vis06_f;
   Float_64 vis08_f;
   Float_64 ir16_f;

   Float_64 vc_ir39;
   Float_64 vc_wv62;
   Float_64 vc_wv73;
   Float_64 vc_ir87;
   Float_64 vc_ir97;
   Float_64 vc_ir108;
   Float_64 vc_ir120;
   Float_64 vc_ir134;

   Float_64 l0_hrvis;
   Float_64 l0_vis06;
   Float_64 l0_vis08;
   Float_64 l0_ir16;
   Float_64 l0_ir39;
   Float_64 l0_wv62;
   Float_64 l0_wv73;
   Float_64 l0_ir87;
   Float_64 l0_ir97;
   Float_64 l0_ir108;
   Float_64 l0_ir120;
   Float_64 l0_ir134;

   Float_64 bw_hrvis;
   Float_64 bw_vis06;
   Float_64 bw_vis08;
   Float_64 bw_ir16;
   Float_64 bw_ir39;
   Float_64 bw_wv62;
   Float_64 bw_wv73;
   Float_64 bw_ir87;
   Float_64 bw_ir97;
   Float_64 bw_ir108;
   Float_64 bw_ir120;
   Float_64 bw_ir134;

   Float_64 f0_hrvis;
   Float_64 f0_vis06;
   Float_64 f0_vis08;
   Float_64 f0_ir16;
   Float_64 f0_ir39;
   Float_64 f0_wv62;
   Float_64 f0_wv73;
   Float_64 f0_ir87;
   Float_64 f0_ir97;
   Float_64 f0_ir108;
   Float_64 f0_ir120;
   Float_64 f0_ir134;

   Float_64 fw_hrvis;
   Float_64 fw_vis06;
   Float_64 fw_vis08;
   Float_64 fw_ir16;
   Float_64 fw_ir39;
   Float_64 fw_wv62;
   Float_64 fw_wv73;
   Float_64 fw_ir87;
   Float_64 fw_ir97;
   Float_64 fw_ir108;
   Float_64 fw_ir120;
   Float_64 fw_ir134;

   Float_64 alpha_ir39;
   Float_64 alpha_wv62;
   Float_64 alpha_wv73;
   Float_64 alpha_ir87;
   Float_64 alpha_ir97;
   Float_64 alpha_ir108;
   Float_64 alpha_ir120;
   Float_64 alpha_ir134;

   Float_64 beta_ir39;
   Float_64 beta_wv62;
   Float_64 beta_wv73;
   Float_64 beta_ir87;
   Float_64 beta_ir97;
   Float_64 beta_ir108;
   Float_64 beta_ir120;
   Float_64 beta_ir134;

   Float_64 btfit_a_ir39;
   Float_64 btfit_a_wv62;
   Float_64 btfit_a_wv73;
   Float_64 btfit_a_ir87;
   Float_64 btfit_a_ir97;
   Float_64 btfit_a_ir108;
   Float_64 btfit_a_ir120;
   Float_64 btfit_a_ir134;

   Float_64 btfit_b_ir39;  
   Float_64 btfit_b_wv62;
   Float_64 btfit_b_wv73;
   Float_64 btfit_b_ir87;
   Float_64 btfit_b_ir97;
   Float_64 btfit_b_ir108;
   Float_64 btfit_b_ir120;
   Float_64 btfit_b_ir134;

   Float_64 btfit_c_ir39;  
   Float_64 btfit_c_wv62;
   Float_64 btfit_c_wv73;
   Float_64 btfit_c_ir87;
   Float_64 btfit_c_ir97;
   Float_64 btfit_c_ir108;
   Float_64 btfit_c_ir120;
   Float_64 btfit_c_ir134;

} Sat_conf_file_struct;

/* ----------------- Parameters stored in DATABUF ----------------- */
typedef enum {
  NAV=0,
  SUN,
  SAT
} Nav_type;


#endif
