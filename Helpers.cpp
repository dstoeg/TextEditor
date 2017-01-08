#include "Helpers.h"
#include <fstream>


int Helpers::GetFileSize(std::string const& file)
{
    std::ifstream t(file);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    int size = int(str.size());
    t.close();
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
