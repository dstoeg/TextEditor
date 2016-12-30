
#include "Logger.h"

#include <iostream>
#include <sstream>

void Logger::dumpText(PieceListText & text)
{
	Piece * piece = text.getFirst();

	std::cout << "|";
	while (piece != nullptr)
	{
		std::cout << piece->getText() << "|";
		piece = piece->getNext();
	}
	std::cout << std::endl;
}

void Logger::dumpTextList(PieceListText & text)
{
	Piece * piece = text.getFirst();
	
	size_t cnt = 0;
	while (piece != nullptr)
	{
		std::cout << "Piece " << cnt << std::endl;
		std::cout << "Text: " << piece->getText() << std::endl;
		std::cout << "Size: " << piece->getLength() << std::endl;
		std::cout << "File: " << piece->getFile() << std::endl;
		std::cout << "Pos:  " << piece->getFilePos() << std::endl;
		std::cout << " ---------------------------------------------------------" << std::endl;
		piece = piece->getNext();
		cnt++;
	}
	
	std::cout << "Total Size: " << text.getLength() << std::endl;

}

std::string Logger::getText(PieceListText & text)
{
    Piece * piece = text.getFirst();
    std::stringstream s;

    while (piece != nullptr)
    {
        s << piece->getText();
        piece = piece->getNext();
    }
    return s.str();
}
