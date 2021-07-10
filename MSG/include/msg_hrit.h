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
 *  FILE        :       msg_hrit.h
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRIT definitions 
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

#include <stdlib.h>
#include <stdio.h>
#include "msg_basictypes.h"

/* ------------------------------ */
/* Declaration of Data Structures */
/* ------------------------------ */

typedef struct Line_Quality_Record {            /*   13 bytes */
  unsigned int      Line_Number_in_Grid;              /*    4 */
  TimeCDSShort      Line_Mean_Acquisition;            /*    6 */
  unsigned char     Line_Validity;                    /*    1 */
  unsigned char     Line_Radiometric_Quality;         /*    1 */
  unsigned char     Line_Geometric_Quality;           /*    1 */
} Line_Quality_Record;



typedef struct hrit_header0 {                 /*    16 bytes */
  unsigned char    Header_Type;                     /*     1 */
  unsigned short   Header_Record_Length;            /*     2 */
  signed   char    File_Type_Code;                  /*     1 */
  unsigned int     Total_Header_Length;             /*     4 */
  unsigned int     Data_Field_Length_msb;           /*     4 */
  unsigned int     Data_Field_Length_lsb;           /*     4 */
} hrit_header0;

typedef struct hrit_header1 {                 /*     9 bytes */
  unsigned char    Header_Type;                     /*     1 */
  unsigned short   Header_Record_Length;            /*     2 */
  unsigned char    NB;                              /*     1 */
  unsigned short   NC;                              /*     2 */
  unsigned short   NL;                              /*     2 */
  signed char      Compression_Flag;                /*     1 */
} hrit_header1;

typedef struct hrit_header2 {                 /*    51 bytes */
  unsigned char    Header_Type;                     /*     1 */
  unsigned short   Header_Record_Length;            /*     2 */
  char             Projection_Name[32];             /*    32 */
  signed int       CFAC;                            /*     4 */
  signed int       LFAC;                            /*     4 */
  signed int       COFF;                            /*     4 */
  signed int       LOFF;                            /*     4 */
} hrit_header2;

typedef struct hrit_header4 {                /*     64 bytes */
  unsigned char    Header_Type;                     /*     1 */
  unsigned short   Header_Record_Length;            /*     2 */
  char             Annotation_Text[61];             /*    61 */
}  hrit_header4;

typedef struct hrit_header5 {                /*     10 bytes */
  unsigned char    Header_Type;                     /*     1 */
  unsigned short   Header_Record_Length;            /*     2 */
  unsigned char    CDS_P_Field;                     /*     1 */
  TimeCDSShort     CDS_T_Field;                     /*     6 */
} hrit_header5;

typedef struct hrit_header7 {                /*     12 bytes */
  unsigned char     Header_Type;                    /*     1 */
  unsigned short    Header_Record_Length;           /*     2 */
  unsigned char     Key_Number;                     /*     1 */
  unsigned int      Seed_msb;                       /*     4 */
  unsigned int      Seed_lsb;                       /*     4 */
} hrit_header7;

typedef struct hrit_header128 {             /*      13 bytes */
  unsigned char     Header_Type;                    /*     1 */
  unsigned short    Header_Record_Length;           /*     2 */
  unsigned short    GP_SC_ID;                       /*     2 */
  unsigned char     Spectral_Channel_ID;            /*     1 */
  unsigned short    Segm_Seq_No;                    /*     2 */
  unsigned short    Planned_Start_Segm_Seq_No;      /*     2 */
  unsigned short    Planned_End_Segm_Seq_No;        /*     2 */
  unsigned char     Data_Field_Representation;      /*     1 */
} hrit_header128;

typedef struct hrit_header129 {           /* 3 + NL*13 bytes */
  unsigned char         Header_Type;             /*        1 */
  unsigned short        Header_Record_Length;    /*        2 */
  Line_Quality_Record  *Line_Quality_Entries;    /*  NL * 13 */
} hrit_header129;


/* ---------------- */
/* Public Functions */
/* ---------------- */

void freadHRITHeader0(hrit_header0 *h, FILE *fp);
void freadHRITHeader1(hrit_header1 *h, FILE *fp);
void freadHRITHeader2(hrit_header2 *h, FILE *fp);
void freadHRITHeader4(hrit_header4 *h, FILE *fp);
void freadHRITHeader5(hrit_header5 *h, FILE *fp);
void freadHRITHeader128(hrit_header128 *h, FILE *fp);
void freadHRITHeader129(hrit_header129 *h, FILE *fp, int nl);

void fwriteHRITHeader0(hrit_header0 *h, FILE *fp);
void fwriteHRITHeader1(hrit_header1 *h, FILE *fp);
void fwriteHRITHeader2(hrit_header2 *h, FILE *fp);
void fwriteHRITHeader4(hrit_header4 *h, FILE *fp);
void fwriteHRITHeader5(hrit_header5 *h, FILE *fp);
void fwriteHRITHeader128(hrit_header128 *h, FILE *fp);
void fwriteHRITHeader129(hrit_header129 *h, FILE *fp, int nl);

void fprintfHRITHeader0(FILE *stream, hrit_header0 *h);
void fprintfHRITHeader1(FILE *stream, hrit_header1 *h);
void fprintfHRITHeader2(FILE *stream, hrit_header2 *h);
void fprintfHRITHeader4(FILE *stream, hrit_header4 *h);
void fprintfHRITHeader5(FILE *stream, hrit_header5 *h);
void fprintfHRITHeader128(FILE *stream, hrit_header128 *h);
void fprintfHRITHeader129(FILE *stream, hrit_header129 *h, int nl);


/* ----------------- */
/* Private Functions */
/* ----------------- */

void freadLineQualityRecord(Line_Quality_Record *l, FILE *fp);
void fwriteLineQualityRecord(Line_Quality_Record *l, FILE *fp);
void fprintfLineQualityRecord(FILE *stream, Line_Quality_Record *l,
                              char *label);

