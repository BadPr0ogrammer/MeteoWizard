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
#include <cmath>

#include "two_to_one.h"

#include "vx_log.h"

///////////////////////////////////////////////////////////////////////////////


   //
   //  this needs external linkage
   //


TwoOne DefaultTO (two_to_one_0_1_0, one_to_two_0_1_0);


///////////////////////////////////////////////////////////////////////////////


inline bool is_zero_one(const int i) { return ( (i == 0) || (i == 1) ); }


///////////////////////////////////////////////////////////////////////////////


   //
   //  Code for class TwoOne
   //


///////////////////////////////////////////////////////////////////////////////


TwoOne::TwoOne()

{

init_from_scratch();

}


///////////////////////////////////////////////////////////////////////////////


TwoOne::TwoOne(TwoToOneFunction to, OneToTwoFunction ot)

{

init_from_scratch();

set(to, ot);

}


///////////////////////////////////////////////////////////////////////////////


TwoOne::~TwoOne()

{

clear();

}


///////////////////////////////////////////////////////////////////////////////


TwoOne::TwoOne(const TwoOne & t)

{

init_from_scratch();

assign(t);

}


///////////////////////////////////////////////////////////////////////////////


TwoOne & TwoOne::operator=(const TwoOne & t)

{

if ( this == &t )  return ( * this );

assign(t);

return ( * this );

}


///////////////////////////////////////////////////////////////////////////////


void TwoOne::init_from_scratch()

{

clear();

return;

}


///////////////////////////////////////////////////////////////////////////////


void TwoOne::clear()

{

TO = (TwoToOneFunction) 0;

OT = (OneToTwoFunction) 0;

return;

}


///////////////////////////////////////////////////////////////////////////////


void TwoOne::assign(const TwoOne & t)

{

clear();

TO = t.TO;
OT = t.OT;

return;

}


///////////////////////////////////////////////////////////////////////////////


void TwoOne::set(TwoToOneFunction to, OneToTwoFunction ot)

{

clear();

TO = to;

OT = ot;

return;

}


///////////////////////////////////////////////////////////////////////////////


void TwoOne::set(int xdir, int ydir, int order)

{

clear();

TO = get_two_to_one(xdir, ydir, order);
OT = get_one_to_two(xdir, ydir, order);

return;

}


///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// The following 8 two_to_one_xdir_ydir_order functions are used
// to index into the GRIB file based on the values set in the scan flag
// in the GDS.  The flags are interpreted as follows:
//
//    xdir  == 1 -> In the -x direction
//    xdir  == 0 -> In the +x direction
//
//    ydir  == 1 -> In the +y direction
//    ydir  == 0 -> In the -y direction
//
//    order == 1 -> y changes fastest
//    order == 0 -> x changes fastest
//
///////////////////////////////////////////////////////////////////////////////


int two_to_one_0_0_0(const int Nx, const int Ny, const int x, const int y)  // +x, -y, x changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0xd5158e20");

  return -9999;
}

return((Ny - 1 - y)*Nx + x);

}

///////////////////////////////////////////////////////////////////////////////

int two_to_one_0_0_1(const int Nx, const int Ny, const int x, const int y)  // +x, -y, y changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x4a4f42b3");
  
  return -9999;
}

return((Nx - 1 - x)*Ny + y);

}

///////////////////////////////////////////////////////////////////////////////


int two_to_one_0_1_0(const int Nx, const int Ny, const int x, const int y)  // +x, +y, x changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x6f6f1be0");

  return -9999;
}

return ( y*Nx + x );

}


///////////////////////////////////////////////////////////////////////////////

int two_to_one_0_1_1(const int Nx, const int Ny, const int x, const int y) // +x, +y, y changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0xb502001b");
  
  return -9999;
}

return(x*Ny + y);

}

///////////////////////////////////////////////////////////////////////////////

int two_to_one_1_0_0(const int Nx, const int Ny, const int x, const int y)  // -x, -y, x changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x78b5d8de");

  return -9999;
}

return((Ny - 1 - y)*Nx + (Nx - 1 - x));

}

///////////////////////////////////////////////////////////////////////////////

int two_to_one_1_0_1(const int Nx, const int Ny, const int x, const int y)  // -x, -y, y changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x37c55a77");
  
  return -9999;
}

return((Nx - 1 - x)*Ny + (Ny - 1 - y));

}

///////////////////////////////////////////////////////////////////////////////

int two_to_one_1_1_0(const int Nx, const int Ny, const int x, const int y)  // -x, +y, x changes fastest

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x2648fe5");

   return -9999;
}

return(y*Nx + (Nx - 1 - x));

}

///////////////////////////////////////////////////////////////////////////////

int two_to_one_1_1_1(const int Nx, const int Ny, const int x, const int y)  // -x, +y, y changes fastest(y, x)

{

if( (x < 0) || (x >= Nx) || (y < 0) || (y >= Ny) ) {
  cerr << "error!\n";//\n", "0x622d3f6b");
  
  return -9999;
}

return(x*Ny + (Ny - 1 - y));

}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


void one_to_two_0_0_0(const int Nx, const int Ny, const int n, int & x, int & y)  // +x, -y, x changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0x332eba13");
  
  return;
}

//  n = (Ny - 1 - y)*Nx + x

x  = n%Nx;

y = Ny - 1 - (n/Nx);

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_0_0_1(const int Nx, const int Ny, const int n, int & x, int & y)  // +x, -y, y changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0x856ff415");
  
  return;
}

// n = (Nx - 1 - x)*Ny + y

y = n%Ny;

x = Nx - 1 - (n/Ny);

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_0_1_0(const int Nx, const int Ny, const int n, int & x, int & y)  // +x, +y, x changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0xd36ce6dc");
  
  return;
}

// n = y*Nx + x

x = n%Nx;

y = n/Nx;

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_0_1_1(const int Nx, const int Ny, const int n, int & x, int & y) // +x, +y, y changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0xc490ab0e");
  
  return;
}

// n = x*Ny + y

y = n%Ny;

x = n/Ny;

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_1_0_0(const int Nx, const int Ny, const int n, int & x, int & y)  // -x, -y, x changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0xdabde715");
  
  return;
}

// n = (Ny - 1 - y)*Nx + (Nx - 1 - x)

x = Nx - 1 - (n%Nx);

y = Ny - 1 - (n/Nx);

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_1_0_1(const int Nx, const int Ny, const int n, int & x, int & y)  // -x, -y, y changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0x94356ad6");

  return;
}

// n = (Nx - 1 - x)*Ny + (Ny - 1 - y)

y = Ny - 1 - (n%Ny);

x = Nx - 1 - (n/Ny);

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_1_1_0(const int Nx, const int Ny, const int n, int & x, int & y)  // -x, +y, x changes fastest

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n", "0xd6b0e1ee");
  
  return;
}

// n = y*Nx + (Nx - 1 - x)

x = Nx - 1 - (n%Nx);

y = n/Nx;

return;

}


///////////////////////////////////////////////////////////////////////////////


void one_to_two_1_1_1(const int Nx, const int Ny, const int n, int & x, int & y)  // -x, +y, y changes fastest(y, x)

{

if ( (n < 0) || (n >= Nx*Ny) )  {
  cerr << "error!\n";//\n","0xc4e3eedf");
  
  return;
}

// n = x*Ny + (Ny - 1 - y)

y = Ny - 1 - (n%Ny);

x = n/Ny;

return;

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


TwoToOneFunction get_two_to_one(int xdir, int ydir, int order)

{

bool check = ( is_zero_one(xdir) && is_zero_one(ydir) && is_zero_one(order) );

if ( !check )  {
  cerr << "error!\n";//\n", "0x50327865");
  
  return TwoToOneFunction();
}

const int k = 4*xdir + 2*ydir + order;
TwoToOneFunction f = (TwoToOneFunction) 0;


switch ( k )  {

   case 0:  f = two_to_one_0_0_0;  break;
   case 1:  f = two_to_one_0_0_1;  break;

   case 2:  f = two_to_one_0_1_0;  break;
   case 3:  f = two_to_one_0_1_1;  break;

   case 4:  f = two_to_one_1_0_0;  break;
   case 5:  f = two_to_one_1_0_1;  break;

   case 6:  f = two_to_one_1_1_0;  break;
   case 7:  f = two_to_one_1_1_1;  break;

   default:
     cerr << "error!\n";//\n", "0xc8c7f5a4");
     
     return TwoToOneFunction();

}   //  switch

   //
   //  done
   //

return ( f );

}


///////////////////////////////////////////////////////////////////////////////


OneToTwoFunction get_one_to_two(int xdir, int ydir, int order)

{

bool check = ( is_zero_one(xdir) && is_zero_one(ydir) && is_zero_one(order) );

if ( !check )  {
  cerr << "error!\n";//\n", "0x731e8eba");
  
  return OneToTwoFunction();
}

const int k = 4*xdir + 2*ydir + order;
OneToTwoFunction f = (OneToTwoFunction) 0;


switch ( k )  {

   case 0:  f = one_to_two_0_0_0;  break;
   case 1:  f = one_to_two_0_0_1;  break;

   case 2:  f = one_to_two_0_1_0;  break;
   case 3:  f = one_to_two_0_1_1;  break;

   case 4:  f = one_to_two_1_0_0;  break;
   case 5:  f = one_to_two_1_0_1;  break;

   case 6:  f = one_to_two_1_1_0;  break;
   case 7:  f = one_to_two_1_1_1;  break;

   default:
     cerr << "error!\n";//\n", "0xf426d2c6");
     
     return OneToTwoFunction();

}   //  switch

   //
   //  done
   //

return ( f );

}


///////////////////////////////////////////////////////////////////////////////
