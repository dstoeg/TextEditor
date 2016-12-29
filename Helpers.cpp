#include "Helpers.h"

#include <fstream>
#include <iostream>


size_t Helpers::GetFileSize(std::string const& file)
{
	std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
	size_t size = (in.is_open()) ? size_t(in.tellg()) : 0;
	in.close();
	return size;
}
