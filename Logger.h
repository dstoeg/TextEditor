#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include "PieceListText.h"


class Logger
{
public:
	static void dumpText(PieceListText & text);
	static void dumpTextList(PieceListText & text);
};

#endif