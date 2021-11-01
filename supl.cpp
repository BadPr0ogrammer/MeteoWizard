#include <stdio.h>

#include <string>
#include <list>
#include <codecvt>
#include <iomanip>
#include <mutex>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include "inc.h"
#include "supl.h"

wstring SuplName8to16(const char* filename)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
	return convert.from_bytes(filename);
}

string SuplName16to8(const wchar_t* filename)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring ws = filename;
    return converter.to_bytes(ws);
}

bool SuplFileExists(const wchar_t* name)
{
	FILE* file = _wfopen(name, L"rb"); 
	//FOPEN(file, name, "rb");
	if (file) {
		fclose(file);
		return true;
	}
	return false;
}

void SuplUnpack10(unsigned char* pc, unsigned short* ps, int w, int h)
{
    int ipos = 0;
    while (ipos < w * h * 10 / 8) {
        ps[0] = (((unsigned short)pc[0]) << 2) | (((unsigned short)pc[1]) >> 6);
        ps[1] = (((unsigned short)pc[1] & 63) << 4) | (((unsigned short)pc[2]) >> 4);
        ps[2] = (((unsigned short)pc[2] & 15) << 6) | (((unsigned short)pc[3]) >> 2);
        ps[3] = (((unsigned short)pc[3] & 3) << 8) | (((unsigned short)pc[4]));
        pc += 5;
        ipos += 5;
        ps += 4;
    }
}

mutex mtx;
void SuplShowImage(cv::Mat* image)
{
    if (!image)
        return;
    else {
        lock_guard<mutex> guard(mtx);
        char name[100];
        sprintf(name, "%s %d", __FILE__, __LINE__);
        namedWindow(name, WINDOW_NORMAL);

        cv::Mat b(image->clone());
        while (true) {
            imshow("DecompWT", b);
            if (waitKey())
                break;
        }
    }
}
