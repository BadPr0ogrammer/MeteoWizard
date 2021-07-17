#pragma once

class Mat;

std::wstring SuplName8to16(const char* filename);
std::string SuplName16to8(const wchar_t* filename);
bool SuplFileExists(const wchar_t* name);
void SuplUnpack10(unsigned char* pc, unsigned short* ps, int w, int h);
void SuplDebugMat(const cv::Mat* img);
void SuplShowImage(cv::Mat* image);
