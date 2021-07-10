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
 *  FILE        :       msg_hrit_HRITHeader1.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       HRITHeader1 I/O
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
 * FUNCTION:     freadHRITHeader1
 * DESCRIPTION:  Read HRIT Header1
 * DATA IN:      fp: file
 * DATA OUT:     h:  header1 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
freadHRITHeader1(hrit_header1 *h, FILE *fp)
{
  fread(&h->Header_Type,1,1,fp);
  freadUShort(&h->Header_Record_Length,1,fp);
  fread(&h->NB,1,1,fp);
  freadUShort(&h->NC,1,fp);
  freadUShort(&h->NL,1,fp);
  fread(&h->Compression_Flag,1,1,fp);
}


/************************************************************
 * FUNCTION:     fwriteHRITHeader1
 * DESCRIPTION:  Write HRIT Header1
 * DATA IN:      fp: file
 *               h:  header1 structure
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *
 *************************************************************/
void
fwriteHRITHeader1(hrit_header1 *h, FILE *fp)
{
  fwrite(&h->Header_Type,1,1,fp);
  fwriteUShort(&h->Header_Record_Length,1,fp);
  fwrite(&h->NB,1,1,fp);
  fwriteUShort(&h->NC,1,fp);
  fwriteUShort(&h->NL,1,fp);
  fwrite(&h->Compression_Flag,1,1,fp);
}


/*************************************************************
 * FUNCTION:     fprintfHRITHeader1
 * DESCRIPTION:  Displays HRIT Header1 contents
 * DATA IN:      stream: output stream
 *               h:  header1 structure
 *
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 07.2001    1.0     OOAL    Creation
 *************************************************************/
void
fprintfHRITHeader1(FILE *stream, hrit_header1 *h)
{
  fprintf(stream,"---------HEADER TYPE #1------------\n");
  fprintf(stream,"Header_Type            %d\n",h->Header_Type);
  fprintf(stream,"Header_Record_Length   %d\n",h->Header_Record_Length);
  fprintf(stream,"NB                     %d\n",h->NB);
  fprintf(stream,"NC                     %d\n",h->NC);
  fprintf(stream,"NL                     %d\n",h->NL);
  fprintf(stream,"Compression_Flag       %d\n",h->Compression_Flag);
  fprintf(stream,"\n");
}

