#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include "PieceListText.h"


class Logger
{
public:
	static void dumpText(PieceListText & text);
	static void dumpTextList(PieceListText & text);
    static std::string getText(PieceListText & text);
    static void debugPrint(std::string const& text);
};

#endif
