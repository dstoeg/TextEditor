#include "Helpers.h"

#include <fstream>
#include <iostream>


int Helpers::GetFileSize(std::string const& file)
{
    std::ifstream t(file);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    int size = str.size();
    t.close();
    return size;
    /*
    std::ifstream in(file, std::ifstream::ate | std::ifstream::binary);
    int size = (in.is_open()) ? int(in.tellg()) : 0;
    in.close();
    return int(fsize);*/
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
