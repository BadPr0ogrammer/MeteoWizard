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
 *  FILE        :       msg_l15_Level1_5ImageCalibrationRecord.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Level1.5 Level1_5ImageCalibrationRecord I/O
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
 * FUNCTION:     freadLevel1_5ImageCalibrationRecord
 * DESCRIPTION:  Read a Level1_5ImageCalibration structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  Level1_5ImageCalibration structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadLevel1_5ImageCalibrationRecord(Level1_5ImageCalibration_Record *r,
                                    FILE *fp)
{
  freadDouble(&r->Cal_Slope,1,fp);
  freadDouble(&r->Cal_Offset,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteLevel1_5ImageCalibrationRecord
 * DESCRIPTION:  Write a Level1_5ImageCalibration structure
 * DATA IN:      fp: file
 * DATA OUT:     r:  Level1_5ImageCalibration structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteLevel1_5ImageCalibrationRecord(Level1_5ImageCalibration_Record *r,
                                    FILE *fp)
{
  fwriteDouble(&r->Cal_Slope,1,fp);
  fwriteDouble(&r->Cal_Offset,1,fp);
}
