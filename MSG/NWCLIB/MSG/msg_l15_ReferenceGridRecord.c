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
 *  FILE        :       msg_l15_ReferenceGridRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 ReferenceGridRecord I/O
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
 * FUNCTION:     freadReferenceGridRecord
 * DESCRIPTION:  Read a ReferenceGrid structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ReferenceGrid structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadReferenceGridRecord(ReferenceGrid_Record *r, FILE *fp)
{
  freadUInt(&r->NumberOfLines,1,fp);
  freadUInt(&r->NumberOfColumns,1,fp);
  freadFloat(&r->LineDirGridStep,1,fp);
  freadFloat(&r->ColumnDirGridStep,1,fp);
  fread(&r->GridOrigin,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteReferenceGridRecord
 * DESCRIPTION:  Write a ReferenceGrid structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  ReferenceGrid structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteReferenceGridRecord(ReferenceGrid_Record *r, FILE *fp)
{
  fwriteUInt(&r->NumberOfLines,1,fp);
  fwriteUInt(&r->NumberOfColumns,1,fp);
  fwriteFloat(&r->LineDirGridStep,1,fp);
  fwriteFloat(&r->ColumnDirGridStep,1,fp);
  fwrite(&r->GridOrigin,1,1,fp);
}

