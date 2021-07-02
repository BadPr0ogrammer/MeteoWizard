#ifndef MSG_NAVIGATION_V1_02_H
#define MSG_NAVIGATION_V1_02_H

#define PI 3.14159265359
/* distance from Earth centre to satellite     */
#define SAT_HEIGHT 42164.0
/* radius from Earth centre to equator         */
#define R_EQ 6378.169
/* radius from Earth centre to pol             */
#define R_POL 6356.5838

#define RAD2DEG      (180./M_PI)
#define DEG2RAD      (M_PI/180.)

#define CFAC_VIR            -781648333.
#define COFF_VIR            1856.

#define SUBLON 0.0

#define CFAC_HRV            -2344944941.
#define COFF_HRV            5566.

int pixcoord2geocoord(double column, double row, double *latitude, double *longitude, int hrv);
int geocoord2pixcoord(double latitude, double longitude, double *column, double *row, int hrv);

#endif // MSG_NAVIGATION_V1_02_H
