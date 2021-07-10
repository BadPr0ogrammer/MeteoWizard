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
 *  FILE        :       msg_basictypes_Double.c
 *  TYPE        :       MSG Level1.5 Image Data library
 *
 *  FUNCTION    :       MSG Basic Types Double I/O
 *                      Assumes file written in SUN byte ordering
 *
 ****************************************************************************
 * HISTORY
 *
 *  DATE      VERSION  AUTHOR  REASONS
 *
 *  11/02/03  v0.1     GMV     SAFNWC/MSG v0.1
 *  26/03/04  v1.0     GMV     SAFNWC/MSG v1.0
 *  NOV 2008  v2009    GMV     SAFNWC/MSG v2009
 *                              SPR-SAF-NWC-CDOP-0362 : SMR-SAF-NWC-CDOP-0xxx
 *
 ****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "msg_basictypes.h"


/************************************************************
 * FUNCTION:     freadDouble
 * DESCRIPTION:  Read a double data (8 bytes)
 * DATA IN:      fp:     file
 *               nitems: no. of items to read
 * DATA OUT:     i:      double data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 * 01.2003    1.1     JJGM    Revision and Portability
 * NOV 2008  v2009    GMV     SPR-SAF-NWC-CDOP-0362 : SMR-SAF-NWC-CDOP-0xxx
 *
 *************************************************************/
void
freadDouble(double *i, int nitems, FILE *fp)
{
  //#define BIGENDIAN 0 /* Sun Work Station */

  union auxiliar{
    char   a[8];
    double j;
  }aux;
  char c;
  int k;

  #ifdef __i386
    #define BIGENDIAN 1
  #endif
  #ifdef __alpha
    #define BIGENDIAN 1
  #endif
  #ifdef __i686
    #define BIGENDIAN 1
  #endif
  #ifdef __x86_64
    #define BIGENDIAN 1
  #endif


  for (k=0; k<nitems; k++) {
    fread(&aux.j,8,1,fp);
    #if (BIGENDIAN == 1)
      c=aux.a[0];
      aux.a[0]=aux.a[7];
      aux.a[7]=c;
      c=aux.a[1];
      aux.a[1]=aux.a[6];
      aux.a[6]=c;
      c=aux.a[2];
      aux.a[2]=aux.a[5];
      aux.a[5]=c;
      c=aux.a[3];
      aux.a[3]=aux.a[4];
      aux.a[4]=c;
    #endif
    i[k]=aux.j;
  }
}


/************************************************************
 * FUNCTION:     fwriteDouble
 * DESCRIPTION:  Write a double data (8 bytes)
 * DATA IN:      fp:     file
 *               nitems: no. of items to write
 *               i:      double data
 *************************************************************
 * HISTORY
 *
 *  DATE    VERSION  AUTHOR   REASONS
 * 09.2001    1.0     OOAL    Creation
 * 01.2003    1.1     JJGM    Revision and Portability
 * NOV 2008  v2009    GMV     SPR-SAF-NWC-CDOP-0362 : SMR-SAF-NWC-CDOP-0xxx
 *
 *************************************************************/
void
fwriteDouble(double *i, int nitems, FILE *fp)
{
  //#define BIGENDIAN 0 /* Sun Work Station */

  union auxiliar{
    char    a[8];
    double  j;
  }aux;
  char c;
  int k;

  #ifdef __i386
    #define BIGENDIAN 1
  #endif
  #ifdef __alpha
    #define BIGENDIAN 1
  #endif
  #ifdef __i686
    #define BIGENDIAN 1
  #endif
  #ifdef __x86_64
    #define BIGENDIAN 1
  #endif

  for (k=0; k<nitems; k++) {
    aux.j=i[k];
    #if (BIGENDIAN == 1)
      c=aux.a[0];
      aux.a[0]=aux.a[7];
      aux.a[7]=c;
      c=aux.a[1];
      aux.a[1]=aux.a[6];
      aux.a[6]=c;
      c=aux.a[2];
      aux.a[2]=aux.a[5];
      aux.a[5]=c;
      c=aux.a[3];
      aux.a[3]=aux.a[4];
      aux.a[4]=c;
    #endif
    fwrite(&aux.j,8,1,fp);
  }
}

