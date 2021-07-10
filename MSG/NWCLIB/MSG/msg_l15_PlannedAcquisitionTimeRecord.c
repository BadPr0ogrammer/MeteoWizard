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
 *  FILE        :       msg_l15_PlannedAcquisitionTimeRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 PlannedAcquisitionTimeRecord I/O
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
 * FUNCTION:     freadPlannedAcquisitionTimeRecord
 * DESCRIPTION:  Read a PlannedAcquisitionTime structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedAcquisitionTime structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadPlannedAcquisitionTimeRecord(PlannedAcquisitionTime_Record *r, FILE *fp)
{
  freadTimeCDSExpanded(&r->TrueRepeatCycleStart,fp);
  freadTimeCDSExpanded(&r->PlannedForwardScanEnd,fp);
  freadTimeCDSExpanded(&r->PlannedRepeatCycleEnd,fp);
}


/************************************************************
 * FUNCTION:     fwritePlannedAcquisitionTimeRecord
 * DESCRIPTION:  Write a PlannedAcquisitionTime structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  PlannedAcquisitionTime structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwritePlannedAcquisitionTimeRecord(PlannedAcquisitionTime_Record *r, FILE *fp)
{
  fwriteTimeCDSExpanded(&r->TrueRepeatCycleStart,fp);
  fwriteTimeCDSExpanded(&r->PlannedForwardScanEnd,fp);
  fwriteTimeCDSExpanded(&r->PlannedRepeatCycleEnd,fp);
}

