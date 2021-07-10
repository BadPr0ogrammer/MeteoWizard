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
 *  FILE        :       msg_l15_L15HRVLineRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 L15HRVLineRecord I/O
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
#include "msg_l15.h"


/************************************************************
 * FUNCTION:     freadL15HRVLineRecord
 * DESCRIPTION:  Read a L15HRVLine structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  L15HRVLine structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadL15HRVLineRecord(L15HRVLine_Record *r, FILE *fp)
{
  fread(&r->L15HRVLineVersion,1,1,fp);
  freadLineSideInfoRecord(&r->LineSideInfo,fp);
  fread(&r->LineData,1,6960,fp);
}


/************************************************************
 * FUNCTION:     fwriteL15HRVLineRecord
 * DESCRIPTION:  Write a L15HRVLine structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  L15HRVLine structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteL15HRVLineRecord(L15HRVLine_Record *r, FILE *fp)
{
  fwrite(&r->L15HRVLineVersion,1,1,fp);
  fwriteLineSideInfoRecord(&r->LineSideInfo,fp);
  fwrite(&r->LineData,1,6960,fp);
}

