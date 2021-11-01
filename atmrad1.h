#pragma once

#include <opencv2/core/core.hpp>

void InitInfoCan();
float RadToTemp1(float rad, int can);
void AtmradGetTb1(const cv::Mat& v, int dt, cv::Mat& watt, double* calib);
