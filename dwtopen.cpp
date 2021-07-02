#include <Windows.h>

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ErrorHandling.h"			// Util
#include "CxRITFile.h"				// DISE
#include "CxRITFileDecompressed.h"	// DISE

#include "inc.h"
#include "supl.h"
#include "dwtopen.h"

#include <QtCore>

using namespace cv;
using namespace std;

cv::Mat* dwtOpen(const wchar_t* fname, const Rect& rc, int& strip_n0, int& strip_n1)
{
	int len;
	if (!fname || (len = (int)wcslen(fname)) < MSAT_NAME_LEN) {
		qDebug() << "Ошибка чтения файла 1" << endl;
		return NULL;
	}
	strip_n0 = 9 - MIN(8, MAX(1, (int)rc.y / MSAT_STRIP_DIM + 1));
	strip_n1 = 9 - MIN(8, MAX(1, (int)(rc.y + rc.height) / MSAT_STRIP_DIM + 1));

	int num = strip_n0 - strip_n1 + 1;
	int H = MSAT_STRIP_DIM * num;
	int W = MSAT_WIDTH;

	wchar_t bn[LARGEBUF];
	bn[LARGEBUF - 1] = 0;
	wcsncpy(bn, fname, LARGEBUF - 1);
	wchar_t* p = bn + len - 20;
	*p = '0' + strip_n1;

	cv::Mat* image = new cv::Mat(H, W, CV_16UC1, Scalar(0));
	uchar* ps = image->data;
	if (!ps) {
		delete image;
		qDebug() << "Ошибка чтения файла 3" << endl;
		return NULL;
	}
	int f = FALSE;
	wchar_t cached[LARGEBUF];
	int i;

	DISE::CxRITFileDecompressed* decomp = NULL;
	DISE::CxRITFile* file = NULL;

	for (i = strip_n1; i <= strip_n0; i++) {
		cached[LARGEBUF - 1] = 0;
		wcsncpy(cached, bn, LARGEBUF - 1);
		cached[len - 2] = '_';

		int exist = SuplFileExists(cached);
		wchar_t* s = NULL;
		if (exist)
			s = cached;
		else  if (SuplFileExists(bn))
			s = bn;
		if (!s) {
			qDebug() << "Ошибка чтения файла 4" << endl;
			goto end;
		}
		file = new DISE::CxRITFile(s);
		decomp = new DISE::CxRITFileDecompressed(*file);
		if (!exist)
			decomp->Write(cached);

		int sz = (decomp->GetDataField().Size() + 7) / 8;
		uchar* pc = (uchar*)malloc(sz);
		if (pc) {
			decomp->GetDataField().Read(0, pc, sz);
			SuplUnpack10(pc, (ushort*)ps, W, MSAT_STRIP_DIM);
			free(pc);
		}
		else {
			qDebug() << "Ошибка чтения файла 7" << endl;
			goto end;
		}

		delete decomp;
		decomp = NULL;
		delete file;
		file = NULL;

		(*p)++;
		ps += 2 * MSAT_STRIP_DIM * W;
	}
	f = TRUE;
end:
	delete decomp;
	delete file;
	if (f)
		flip(*image, *image, -1);
	else {
		delete image;
		return NULL;
	}
	return image;
}
