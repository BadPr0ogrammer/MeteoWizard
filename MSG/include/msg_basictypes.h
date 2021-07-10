/******************************************************************************
 *  COPYRIGHT   :       Copyright 2000, EUMETSAT, All Rights Reserved
 *  PRODUCED BY :       This SW (document) was developed by GMV S.A. ,under
 *                      contract of INM, within he context of the EUMETSAT
 *                      Satellite Application facility on Nowcasting
 *                      and Short Range Forecasting, under the Cooperation
 *                      Agreement dated on 05 December 1996, between EUMETSAT
 *                      and INM.
 *  PROJECT     :       SAFNWC
 *  UNIT NAME   :       MSG
 *  FILE        :       msg_basictypes.h
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Basic Types I/O
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  11/02/03  v0.1     GMV     SAFNWC/MSG v0.1
 *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
 *
 ****************************************************************************/

#ifndef __MSG_BASICTYPES_H__
#define __MSG_BASICTYPES_H__

/* ----------------------------------- */
/* Definition of basic data structures */
/* ----------------------------------- */

typedef struct TimeCDSShort {
  unsigned short    days;
  unsigned int      millisecs;
} TimeCDSShort;

typedef struct TimeCDS {
  unsigned short    days;
  unsigned int      millisecs;
  unsigned short    microsecs;
} TimeCDS;

typedef struct TimeCDSExpanded {
  unsigned short    days;
  unsigned int      millisecs;
  unsigned short    microsecs;
  unsigned short    nanosecs;
} TimeCDSExpanded;

typedef unsigned short GP_SC_ID;

/* --------------------------------------------------------*/


/* ---------------- */
/* Public Functions */
/* ---------------- */

void freadUShort(unsigned short *i, int nitems, FILE *fp);
void freadSShort(signed short *i, int nitems, FILE *fp);
void freadUInt(unsigned int *i, int nitems, FILE *fp);
void freadSInt(signed int *i, int nitems, FILE *fp);
void freadFloat(float *a, int nitems, FILE *fp);
void freadDouble(double *a, int nitems, FILE *fp);

void freadTimeCDSShort(TimeCDSShort *t, FILE *fp);
void freadTimeCDS(TimeCDS *t, FILE *fp);
void freadTimeCDSExpanded(TimeCDSExpanded *t, FILE *fp);

void freadGPSCID(GP_SC_ID *r, FILE *fp);

/* --------------------------------------------------------*/

void fwriteUShort(unsigned short *i, int nitems, FILE *fp);
void fwriteSShort(signed short *i, int nitems, FILE *fp);
void fwriteUInt(unsigned int *i, int nitems, FILE *fp);
void fwriteSInt(signed int *i, int nitems, FILE *fp);
void fwriteFloat(float *a, int nitems, FILE *fp);
void fwriteDouble(double *a, int nitems, FILE *fp);

void fwriteTimeCDSShort(TimeCDSShort *t, FILE *fp);
void fwriteTimeCDS(TimeCDS *t, FILE *fp);
void fwriteTimeCDSExpanded(TimeCDSExpanded *t, FILE *fp);

void fwriteGPSCID(GP_SC_ID *r, FILE *fp);

/* --------------------------------------------------------*/

void fprintfTimeCDSShort(FILE *stream, TimeCDSShort *t, char *label);
void fprintfTimeCDS(FILE *stream, TimeCDS *t, char *label);
void fprintfTimeCDSExpanded(FILE *stream, TimeCDSExpanded *t, char *label);

#endif
