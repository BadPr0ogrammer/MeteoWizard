/******************************************************************************
 *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
 *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
 *                      contract of INM, within he context of the EUMETSAT
 *                      Satellite Application facility on Nowcasting
 *                      and Short Range Forecasting, under the Cooperation
 *                      Agreement dated on 05 December 1996, between EUMETSAT
 *                      and INM.
 *  PROJECT     :       SAFNWC
 *  UNIT NAME   :       SEVEXT
 *  FILE        :       sevext_basictypes.h
 *  TYPE        :       NWCLIB/SEVEXT
 *
 *  FUNCTION    :       This module defines the basic types and constants used
 *                      by the SEVEXT module
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  JUL 2005  v2.0     GMV     SAFNWC/MSG v2.0
 *                              SPR-SAF-NWC-IOP-0217 : SMR-SAF-NWC-IOP-0200
 *
 *  NOV 2007  v2008    GMV     SAFNWC/MSG v2008
 *                              SPR-SAF-NWC-CDOP-0314 : SMR-SAF-NWC-CDOP-0295
 *  OCT 2010  v2011    GMV     SAFNWC/MSG v2011
 *                              SPR-SAF-NWC-CDOP-0446 : SMR-SAF-NWC-CDOP-0xxx
 *
 ****************************************************************************/

#ifndef __SEVEXT_BASICTYPES_H__
#define __SEVEXT_BASICTYPES_H__

#include "libnwc_basictypes.h"

/* ---------------------------- SEVIRI values ------------------------------- */
#define SEVIRI_MISSING_VALUE -99999
#define INVALID_COUNT        0xFFFF  /* 65535 */

/* ---------------------- Annotation texts base names ----------------------- */
#define PROLOGUE_BASENAME "H-000-%s__-%s_%s____-_________-PRO______-"
#define EPILOGUE_BASENAME "H-000-%s__-%s_%s____-_________-EPI______-"
#define IMAGE_BASENAME    "H-000-%s__-%s_%s____-"

/* --------------------------- HRIT headers lenght -------------------------- */
#define HEADER0_LENGTH     16
#define HEADER1_LENGTH      9
#define HEADER2_LENGTH     51
#define HEADER4_LENGTH     64
#define HEADER5_LENGTH     10
#define HEADER7_LENGTH     12
#define HEADER128_LENGTH   13

/* ----------------------------- SEVIRI channels ---------------------------- */
typedef enum {
        HRVIS=0,
        VIS06,
        VIS08,
        IR16,
        IR39,
        WV62,
        WV73,
        IR87,
        IR97,
        IR108,
        IR120,
        IR134,
        NUM_BANDS
} Sev_bands;

/* ---------------------------- File information ---------------------------- */
typedef struct {
        File_name       name;
        U_short         slot;
        YYYYMMDDhhmm    date;
        Pixel_coords    centre;
        U_short         reg_lin;
        U_short         reg_col;
} File_information;

/* ---------------------------- Band information ---------------------------- */
typedef struct{
   char channel[6];
   char central_wl[12];
   char spectral_band[12];
   char radiometric_noise[7];
} Band_info;


typedef Boolean Band_mask[NUM_BANDS];


/* ************************************************************************** */
/*                             15HEADER RECORD                                */
/* ************************************************************************** */

/* ---------------------------- Satellite ID -------------------------------- */
/*
typedef enum {
  MSG=0,
  MSG2
} Sat_id;
*/
#define MSG   0
#define MSG2  1

/* ----------------------- Satellite status record -------------------------- */
typedef struct {
        Short_CDS_time  start_time;     /* Start time coefficient validity */
        Short_CDS_time  end_time;       /* End time coefficient validity   */
        Float_64  x[8], y[8], z[8];     /* Spacecraft position             */
        Float_64  vx[8], vy[8], vz[8];  /* Spacecraft velocity             */
} Orbit_coef;

typedef struct {
        Short_CDS_time  start_time;     /* Start time coverage period */
        Short_CDS_time  end_time;       /* End   time coverage period */
        Orbit_coef      orbit_pol[100];
} Orbit;

typedef struct {
        Short_CDS_time  start_time;     /* Start time coefficient validity */
        Short_CDS_time  end_time;       /* End time coefficient validity   */
        Float_64  x_spin_axis[8];       /* Spacecraft spin axis            */
        Float_64  y_spin_axis[8];
        Float_64  z_spin_axis[8];
} Orbit_coef_att;

typedef struct {
  Short_CDS_time  start_time;               /* Start time coverage period */
  Short_CDS_time  end_time;                 /* End   time coverage period */
  Float_64        princ_axis_offset_angle;  /* Between principle axis and */
                                            /* geom. axis  perp. to the   */
                                            /* baseplate in radians       */
  Orbit_coef_att  attitude_pol[100];
} Attitude;

typedef struct {
  /*Sat_id*/ int    satellite_identifier; /* Satellite identification              */
  Float_32  ref_long;      /* Subsatellite longitude in degrees            */
  Float_32  ref_alt;       /* Subsatellite altitude in km                  */
  U_short   nb_tcols;      /* Columns in the full VIS/IR resolution        */
  U_short   nb_tlines;     /* Lines in the full VIS/IR resolution          */
  U_int    acq_dur;       /* Duration of the data acquisition in seconds  */
  U_int    nb_day_slots;  /* Nb of slots disseminated by day              */
  U_int    time_slot1;    /* Start time of acquisition for slot 1 in secs */
} Processing_sat_params;

typedef struct {
        Orbit   orbit;        /* Offset relative to its nominal position */
        Attitude attitude;    /* Attitude information */
        Float_64  spin_rate;
} Sat_params;

/* ------------------------- Image acquisition record ----------------------- */
typedef struct {
 Expanded_CDS_time  repeat_cycle_start;   /* Start time of the repeated cycle */
 Expanded_CDS_time  planned_fwd_scan_end; /* Planned start time   */
 Expanded_CDS_time  planned_cycle_end;    /* Planned end time     */
} Planned_acquisition_time;

/* ------------------------- Celestial Events record ------------------------ */
typedef struct {
        Short_CDS_time start_time;  /* Start time for the coeff. set validity */
        Short_CDS_time end_time;    /* End   time for the coeff. set validity */
        Float_64 alpha_coef[8];     /* position of earth, sun or moon */
        Float_64 beta_coef[8];      /* position of earth, sun or moon */
} EMS_coeff;


typedef struct {
  Short_CDS_time    start_time;   /* Start time of the coverage for this data */
  Short_CDS_time    end_time;     /* End  time of the coverage for this data */
  Time_generalized  orbit_file_time;    /* Time of creation orbit file    */
  Time_generalized  attitude_file_time; /* Time of creation attitude file */
  EMS_coeff         sun_ephemeris[100]; /* Sun ephemeris data */
  /* Moon, earth and star ephemeris not included */
} Ephemeris;

/* ------------------------- Image description record ----------------------- */
typedef enum  {
        GEOS=1,
        MAX_PROJECTIONS
} Projection_type;

typedef enum  {
        NW=0,
        SW,
        SE,
        NE
} Grid_origin;

typedef struct {
  Projection_type type_of_projection; /* Projection used in L1.5 image generation */
  Float_32        SSP_longitude;    /* Subsatellite point long in degrees Eastwards */
} Projection_description;

/* Reference grid */
typedef struct {
  S_int   nb_lines;        /* Number of lines in reference grid. Maxi 3712   */
  S_int   nb_columns;      /* Number of columns in reference grid. Maxi 3712 */
  Float_32 line_grid_step;   /* Grid step size in km in the line direction   */
  Float_32 column_grid_step; /* Grid step size in km in the column direction */
  Grid_origin origin;        /* Reference grid origin */
} Reference_grid;


/* Coverage VIS_IR */
typedef struct {
        S_int south_line;
        S_int north_line;
        S_int east_line;
        S_int west_line;
} Coverage_VIS_IR;

/* Coverage HRV */
typedef struct {
        S_int low_south_line;
        S_int low_north_line;
        S_int low_east_line;
        S_int low_west_line;
        S_int up_south_line;
        S_int up_north_line;
        S_int up_east_line;
        S_int up_west_line;
} Coverage_HRV;

/* Level 1.5 Image production */
typedef enum  {
        N_S=0,
        S_N
} Prod_direction;

typedef enum  {
        E_W=0,
        W_E
} Pixel_direction;

typedef struct {
  Prod_direction  image_prod_dir;           /* Image production direction */
  Pixel_direction pixel_gen_dir;            /* Pixel generation direction */
  Boolean    planned_chan_proc[NUM_BANDS];  /* Planned channel to derive data */
} Level_15_production;

typedef struct {
        Projection_description  projection;
        Reference_grid          grid_VIS_IR;
        Reference_grid          grid_HRV;
        Coverage_VIS_IR         planned_cov_VIS_IR;
        Coverage_HRV            planned_cov_HRV;
        Level_15_production     image_production;
        Coverage_VIS_IR         actual_cov_VIS_IR;
        Coverage_HRV            actual_cov_HRV;
} Image_description;

/* --------------------- Radiometric Processing record ----------- */
typedef struct {
        Float_64  cal_slope;
        Float_64  cal_offset;
} Calibration_data;

/* ************************************************************* */
/*          15VIS/IRLINE and 15HRVLINE RECORD STRUCTURE          */
/* ************************************************************* */

typedef enum  {
        NOT_DERIVED=0,
        NOMINAL,
        MISSING_DATA,
        CORRUPTED_DATA,
        REPLACED_DATA
} Line_validity;

typedef enum  {
        N_DERIVED=0,
        NOMINALE,
        USABLE,
        SUSPECT,
        NOT_USE
} Geo_Radio_validity;

typedef struct {
        S_int              line_nb;
        Short_CDS_time      mean_acq_time;
        Line_validity       validity;
        Geo_Radio_validity  radio_validity;
        Geo_Radio_validity  geo_validity;
} Line_side_info;       /* This information ir read from HRIT header type 129 */


/* Data types for counts, brightness temperature and radiances  */
/* Data is stored line per line. An image is made by a NL lines */
/* of NC pixels, NL and NC parameters from region structure.    */
/* In order to save memory usage pointers are used. There isn't */
/* any difference between VIS_IR and HRV channels due to the    */
/* dynamic approach used.                                       */

typedef U_short     *Line_counts;  /* Pointer to one line of counts        */
typedef Line_counts *Image_counts; /* Pointer to the image lines with CNTs */

typedef Float_32      *Line_radiance;  /* Pointer to one line of radiances */
typedef Line_radiance *Image_rad;      /* Pointer to the image lines with RADs*/

typedef Float_32 *Line_reflectances; /* Pointer to one line of reflectances   */
typedef Line_radiance *Image_refl;   /* Pointer to the image lines with Refl */

typedef Float_32 *Line_bt;   /* Pointer to one line of brightness temp.   */
typedef Line_bt  *Image_bt;  /* Pointer to the image lines with BTs       */

/* Level 1.5 image quality */
typedef struct {
  Boolean nominal_image;
  Boolean incomplete;
  Boolean radiometric_quality;  /* Non nominal due to bad radiometric quality */
  Boolean geometric_quality;    /* Non nominal due to bad geometric quality */
  Boolean timeliness;           /* Non nominal due to late arrival data */
  Boolean incomplete_L15;       /* Not all level 1.5 data was produced */
} L15_channel_validity;

/* ************************************************************* */
/*                     15TRAILER RECORD STRUCTURE                */
/* ************************************************************* */

/* geometric accuracy */
typedef enum  {    /* Whole channel records validity */
        NO_DERIVED=0,     /* it must be checked before using */
        VALID,            /* other values of the record     */
        INVALID,
        ESTIMATED
} Quality_info_validity;

typedef struct {
   Quality_info_validity info;        /* Whole channel record validity        */
   Float_32  east_west_accuracy;      /* E-W image accuracy in RMS terms      */
   Float_32  north_south_accuracy;    /* N-S image accuracy in RMS terms      */
   Float_32  magnitude;               /* Magnitude of accumulated RMS         */
   Float_32  east_west_uncertan;      /* E-W uncertainty in the acc. RMS      */
   Float_32  north_south_uncertan;    /* N-S uncertainty in the acc. RMS      */
   Float_32  magnitud_uncertan;       /* Magnitude uncertainty in acc. RMS    */
   Float_32  east_west_deviation;     /* Maximun E-W deviation in image acc   */
   Float_32  north_south_deviation;   /* Maximun N-S deviation in image acc   */
   Float_32  magnitude_deviation;     /* Magnitude of the max. deviation      */
   Float_32  east_west_uncertan_max;  /* Maximun E-W uncertainty factor       */
   Float_32  north_south_uncertan_max;/* Maximun N-S uncertainty factor       */
   Float_32  magnitud_uncertan_max;   /* Maximun magnitude uncertainty factor */
} Geometric_accuracy;


/* ************************************************************* */
/*                     SEVIRI1.5 STRUCTURE                       */
/* ************************************************************* */

/* This structure contains all the information related to SEVIRI1.5 file      */
/* incluiding all data derived from it. It must be allocated using the        */
/* SevInit provided in this module and at the end of each PGE                 */
/* Processing SevFree shall be called to liberate memory                      */
/* Data is stored in separately counts, radiance, reflectance and bt.         */
/* Three arrays contain the pointers to the 12 different images of each       */
/* band for each each type of data. Syntaxis for access is:                   */
/*      seviri_struct_var.rad_by_channel[channel][line][column]               */
/* Every element of NUM_BANDS items arrays refers to one channel              */

typedef struct {
        File_information         *file;
        Planned_acquisition_time *planned_acq_time;
        Ephemeris                *sun_position;
        Image_description        *image_descriptor;
        Calibration_data         calibration[NUM_BANDS];
        Processing_sat_params    *sat_params;
        Sat_params               *other_sat_params;
        Line_side_info           *line_info_array[NUM_BANDS];
        U_byte                   nb;
        U_short                  nc;
        U_short                  nl;
        Boolean                  cflg;
        U_int                   cfac;
        U_int                   lfac;
        S_int                   coff;
        S_int                   loff;
        Image_counts             counts[NUM_BANDS];
        Image_rad                radiances[NUM_BANDS];
        Image_refl               reflectances[NUM_BANDS];
        Image_bt                 bt[NUM_BANDS];
        L15_channel_validity     channel_validity[NUM_BANDS];
        Geometric_accuracy       abs_geo_accuracy[NUM_BANDS];
        Geometric_accuracy       rel_geo_accuracy[NUM_BANDS];
} Seviri_struct;

#endif
