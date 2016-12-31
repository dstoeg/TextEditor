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

std::string Helpers::ReplaceTabs(std::string const& text)
{
    std::string s1 = text;
    size_t pos = s1.find('\t');
    while (pos != std::string::npos)
    {
        s1.erase(pos, 1);
        s1.insert(pos, "    ");
        pos = s1.find('\t');
    }
    return s1;
}
