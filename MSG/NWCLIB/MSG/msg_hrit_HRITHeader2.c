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
 *  FILE        :       msg_hrit_HRITHeader2.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader2 I/O
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
 * FUNCTION:     freadHRITHeader2
 * DESCRIPTION:  Read HRIT Header2
 * DATA IN:      fp: file
 * DATA OUT:     h:  header2 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader2(hrit_header2 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  fread(&h->Projection_Name,32,1,fp);
  freadSInt(&h->CFAC,1,fp);
  freadSInt(&h->LFAC,1,fp);
  freadSInt(&h->COFF,1,fp);
  freadSInt(&h->LOFF,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader2
 * DESCRIPTION:  Write HRIT Header2
 * DATA IN:      fp: file
 *               h:  header2 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader2(hrit_header2 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwrite(&h->Projection_Name,32,1,fp);
  fwriteSInt(&h->CFAC,1,fp);
  fwriteSInt(&h->LFAC,1,fp);
  fwriteSInt(&h->COFF,1,fp);
  fwriteSInt(&h->LOFF,1,fp);
}


/************************************************************
 * FUNCTION:     fprintfHRITHeader2
 * DESCRIPTION:  Displays HRIT Header2 contents
 * DATA IN:      stream: output stream
 *               h:  header2 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader2(FILE *stream,hrit_header2 *h)
{
  char ch33[33];

  strncpy(ch33,h->Projection_Name,32);
  ch33[32]=0;

  fprintf(stream,"---------HEADER TYPE #2------------\n");
  fprintf(stream,"Header_Type             %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length    %d\n",h->Header_Record_Length);
  fprintf(stream,"Projection_Name         %s\n",ch33);
  fprintf(stream,"CFAC                    %d\n",h->CFAC);
  fprintf(stream,"LFAC                    %d\n",h->LFAC);
  fprintf(stream,"COFF                    %d\n",h->COFF);
  fprintf(stream,"LOFF                    %d\n",h->LOFF);
  fprintf(stream,"\n");
}

