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
 *  FILE        :       msg_l15_PlannedCoverageVIS_IRRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 PlannedCoverageVIS_IRRecord I/O
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
 * FUNCTION:     freadPlannedCoverageVIS_IRRecord
 * DESCRIPTION:  Read a PlannedCoverageVIS_IR structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedCoverageVIS_IR structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadPlannedCoverageVIS_IRRecord(PlannedCoverageVIS_IR_Record *r, FILE *fp)
{
  freadUInt(&r->SouthernLinePlanned,1,fp);
  freadUInt(&r->NorthernLinePlanned,1,fp);
  freadUInt(&r->EasternColumnPlanned,1,fp);
  freadUInt(&r->WesternColumnPlanned,1,fp);
}


/************************************************************
 * FUNCTION:     fwritePlannedCoverageVIS_IRRecord
 * DESCRIPTION:  Write a PlannedCoverageVIS_IR structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedCoverageVIS_IR structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwritePlannedCoverageVIS_IRRecord(PlannedCoverageVIS_IR_Record *r, FILE *fp)
{
  fwriteUInt(&r->SouthernLinePlanned,1,fp);
  fwriteUInt(&r->NorthernLinePlanned,1,fp);
  fwriteUInt(&r->EasternColumnPlanned,1,fp);
  fwriteUInt(&r->WesternColumnPlanned,1,fp);
}

