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
 *  FILE        :       msg_hrit_HRITHeader0.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader0 I/O
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
 * FUNCTION:     freadHRITHeader0
 * DESCRIPTION:  Read HRIT Header0
 * DATA IN:      fp: file
 * DATA OUT:     h:  header0 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader0(hrit_header0 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  fread(&h->File_Type_Code,1,1,fp);
  freadUInt(&h->Total_Header_Length,1,fp);
  freadUInt(&h->Data_Field_Length_msb,1,fp);
  freadUInt(&h->Data_Field_Length_lsb,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader0
 * DESCRIPTION:  Write HRIT Header0
 * DATA IN:      fp: file
 *               h:  header0 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader0(hrit_header0 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwrite(&h->File_Type_Code,1,1,fp);
  fwriteUInt(&h->Total_Header_Length,1,fp);
  fwriteUInt(&h->Data_Field_Length_msb,1,fp);
  fwriteUInt(&h->Data_Field_Length_lsb,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader0
 * DESCRIPTION:  Displays HRIT Header0 contents
 * DATA IN:      stream: output stream
 *               h:  header0 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader0(FILE *stream,hrit_header0 *h)
{
  fprintf(stream,"---------HEADER TYPE #0------------\n");
  fprintf(stream,"Header_Type           %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length  %d\n",h->Header_Record_Length);
  fprintf(stream,"File_Type_Code        %d\n",h->File_Type_Code);
  fprintf(stream,"Total_Header_Length   %d\n",h->Total_Header_Length);
  fprintf(stream,"Data_Field_Length(ML) %d - %d\n",
          h->Data_Field_Length_msb,h->Data_Field_Length_lsb);
  fprintf(stream,"\n");
}

