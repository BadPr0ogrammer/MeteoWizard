#pragma once

typedef struct CvRect_
{
	int x;
	int y;
	int width;
	int height;
} CvRect_;

int ReadMSGInfo(char* fname, CvRect_* ret, double** p_calib);
