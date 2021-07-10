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
 *  FILE        :       msg_hrit_HRITHeader128.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader128 I/O
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
#include <string.h>
#include "msg_hrit.h"


/************************************************************
 * FUNCTION:     freadHRITHeader128
 * DESCRIPTION:  Read HRIT Header128
 * DATA IN:      fp: file
 * DATA OUT:     h:  header128 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader128(hrit_header128 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  freadUShort(&h->GP_SC_ID,1,fp);
  fread(&h->Spectral_Channel_ID,1,1,fp);
  freadUShort(&h->Segm_Seq_No,1,fp);
  freadUShort(&h->Planned_Start_Segm_Seq_No,1,fp);
  freadUShort(&h->Planned_End_Segm_Seq_No,1,fp);
  fread(&h->Data_Field_Representation,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader128
 * DESCRIPTION:  Write HRIT Header128
 * DATA IN:      fp: file
 *               h:  header128 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader128(hrit_header128 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwriteUShort(&h->GP_SC_ID,1,fp);
  fwrite(&h->Spectral_Channel_ID,1,1,fp);
  fwriteUShort(&h->Segm_Seq_No,1,fp);
  fwriteUShort(&h->Planned_Start_Segm_Seq_No,1,fp);
  fwriteUShort(&h->Planned_End_Segm_Seq_No,1,fp);
  fwrite(&h->Data_Field_Representation,1,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader128
 * DESCRIPTION:  Displays HRIT Header128 contents
 * DATA IN:      stream: output stream
 *               h:  header128 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader128(FILE *stream, hrit_header128 *h)
{
  fprintf(stream,"---------HEADER TYPE #128------------\n");
  fprintf(stream,"Header_Type               %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length      %d\n",h->Header_Record_Length);
  fprintf(stream,"GP_SC_ID                  %d\n",h->GP_SC_ID);
  fprintf(stream,"Spectral_Channel_ID       %d\n",h->Spectral_Channel_ID);
  fprintf(stream,"Segm_Seq_No               %d\n",h->Segm_Seq_No);
  fprintf(stream,"Planned_Start_Segm_Seq_No %d\n",
                                          h->Planned_Start_Segm_Seq_No);
  fprintf(stream,"Planned_End_Segm_Seq_No   %d\n",
                                          h->Planned_End_Segm_Seq_No);
  fprintf(stream,"Data_Field_Representation %d\n",
                                          h->Data_Field_Representation);
  fprintf(stream,"\n");
}

