#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include "inc.h"
#include "supl.h"

#define MFCMS_MAX_IRCHN  7

double geninfo_nuc[MFCMS_MAX_IRCHN] = {
  2555.731534, 1588.479697, 1358.460452, 1147.372612,
  //1034.479078,  
  927.068881, 836.873459,  748.168675
};

double geninfo_beta[MFCMS_MAX_IRCHN] = {
  0.993332,    0.994790,    0.998933,    0.999598,
  //0.999887,    
  0.998883,    0.999454,    0.999557
};

double geninfo_alpha[MFCMS_MAX_IRCHN] = {
  3.068828,    1.563938,    0.274709,    0.084396,
  //0.019891,    
  0.144813,    0.032091,   -0.056122
};

#define C_LIGHT                  299792458.0  // Speed of light  (m/s)   
#define K_BOLTZ                1.3806503e-23  // Boltzman constant (J/K) 
#define H_PLANCK               6.6260688e-34  // Planck constant (J s)   

double info_can_planck1[MFCMS_MAX_IRCHN];   // to compute planck function 
double info_can_planck2[MFCMS_MAX_IRCHN];   // to compute planck function 

void InitInfoCan()
{
    const double C1 = 2. * H_PLANCK * C_LIGHT * C_LIGHT * 1.e+11;
    const double C2 = 100 * H_PLANCK * C_LIGHT / K_BOLTZ;
    int k;
    for (k = 0; k < MFCMS_MAX_IRCHN; k++) {
        info_can_planck1[k] = (C1 * pow(geninfo_nuc[k], 3.));
        info_can_planck2[k] = (C2 * geninfo_nuc[k]);
    }
}

float RadToTemp1(float rad, int can)
{
    double teff = info_can_planck2[can] / log(1. + info_can_planck1[can] / rad);
    double temp = (teff - geninfo_alpha[can]) / geninfo_beta[can];
    return (float)temp;
}

void AtmradGetTb1(const cv::Mat& v, int dt, cv::Mat& watt, double* calib)
{
    int ir = dt - 4;
    int k = dt <= T_08_7 ? dt - 1 : dt;//??? -1 ???
    double scale = calib[2 * k];
    double offset = calib[2 * k + 1];
    for (int i = 0; i < v.rows; i++) {
        for (int j = 0; j < v.cols; j++) {
            watt.at<float>(i, j) = RadToTemp1(offset + scale * v.at<unsigned short>(i, j), ir);
        }
    }
}

