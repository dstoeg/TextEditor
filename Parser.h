#ifndef PARSER_H
#define PARSER_H
#pragma once

#include <string>
#include "Piece.h"

class Parser
{
public:

    static Piece * parseFile(std::string const& file, int & length);
	static bool writeFile(std::string const& file, Piece * first);
    static std::string getFontAsString(QFont const& font);

private:
	static int parseNextInt(std::ifstream & file);
	static std::string parseNextString(std::ifstream & file);
    static std::string qfontToFontString(QFont font);
    static std::string qfontToStyleString(QFont font);
    static QFont parseFont(std::string const& font, std::string const& style);

};

#endif
