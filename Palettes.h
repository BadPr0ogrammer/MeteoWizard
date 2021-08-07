#pragma once

#include <vector>
#include <string>

typedef double(*pal_ptr_t)[3];

class palettes_c
{
public:
	std::vector<pal_ptr_t> m_pal_ptrs;
	std::vector<int> m_size;
	std::vector <std::string> m_name;
	
	palettes_c();
};


