#ifndef PARSER_H
#define PARSER_H
#pragma once

#include <string>
#include "Piece.h"

class Parser
{
public:

	static Piece * parseFile(std::string const& file, size_t & length);
	static bool writeFile(std::string const& file, Piece * first);

private:
	static int parseNextInt(std::ifstream & file);
	static std::string parseNextString(std::ifstream & file);

};

#endif