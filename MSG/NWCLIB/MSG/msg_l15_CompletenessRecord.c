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
 *  FILE        :       msg_l15_CompletenessRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 CompletenessRecord I/O
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
 * FUNCTION:     freadCompletenessRecord
 * DESCRIPTION:  Read a Completeness structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  Completeness structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadCompletenessRecord(Completeness_Record *r, FILE *fp)
{
  freadUShort(&r->PlannedL15ImageLines,1,fp);
  freadUShort(&r->GeneratedL15ImageLines,1,fp);
  freadUShort(&r->ValidL15ImageLines,1,fp);
  freadUShort(&r->DummyL15ImageLines,1,fp);
  freadUShort(&r->CorruptedL15ImageLines,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteCompletenessRecord
 * DESCRIPTION:  Write a Completeness structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  Completeness structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteCompletenessRecord(Completeness_Record *r, FILE *fp)
{
  fwriteUShort(&r->PlannedL15ImageLines,1,fp);
  fwriteUShort(&r->GeneratedL15ImageLines,1,fp);
  fwriteUShort(&r->ValidL15ImageLines,1,fp);
  fwriteUShort(&r->DummyL15ImageLines,1,fp);
  fwriteUShort(&r->CorruptedL15ImageLines,1,fp);
}

