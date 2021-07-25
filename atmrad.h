#pragma once

class slot_c { 
public:
	cv::Mat* m_img[LAYER_NUM];

	slot_c() { for (int i = 0; i < LAYER_NUM; i++) m_img[i] = nullptr; }
	~slot_c() { for (int i = 0; i < LAYER_NUM; i++) delete m_img[i]; }
};

cv::Mat*  AtmradMakeDif(slot_c *src, const int(chnls)[6], const double(thresh)[9]);
