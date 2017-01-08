#ifndef HELPERS_H
#define HELPERS_H

#include<string>
#include<fstream>

namespace Helpers
{
    int GetFileSize(std::string const& file);

    std::string ReplaceTabs(std::string const& text);

}



#endif // HELPERS_H
