#pragma once

class Mat;

cv::Mat* dwtOpen(const wchar_t* fname, const cv::Rect& rc, int& strip_n0, int& strip_n1);