// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2016
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*




////////////////////////////////////////////////////////////////////////

using namespace std;

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cmath>

#include "vx_log.h"

#include "file_size.h"


////////////////////////////////////////////////////////////////////////


#ifdef _WINDOWS
long long file_size(const wchar_t *fname)
{
int status;
struct _stat sbuf;
status = _wstat(fname, &sbuf);
#else
long long file_size(const char *fname)
{
int status;
struct stat sbuf;
status = stat(fname, &sbuf);
#endif

if ( status < 0 )  {
  cerr << "error!\n";//\n", "0x7e87cfc");

   return 0;
}

   //
   //  return the file size in bytes
   //

return( (long long) sbuf.st_size );

}


////////////////////////////////////////////////////////////////////////
