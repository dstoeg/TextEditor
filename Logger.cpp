
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <QDebug>

void Logger::dumpText(PieceListText & text)
{
	Piece * piece = text.getFirst();

    qDebug() << "|";
	while (piece != nullptr)
	{
        qDebug() << QString::fromStdString(piece->getText()) << "|";
		piece = piece->getNext();
	}
    qDebug() << "\n";
}

void Logger::dumpTextList(PieceListText & text)
{
	Piece * piece = text.getFirst();
	
	size_t cnt = 0;
	while (piece != nullptr)
	{
        qDebug() << "Piece " << cnt << "\n";
        qDebug() << "Text: " << QString::fromStdString(piece->getText()) << "\n";
        qDebug() << "Size: " << piece->getLength() << "\n";
        qDebug() << "File: " << QString::fromStdString(piece->getFile()) << "\n";
        qDebug() << "Pos:  " << piece->getFilePos() << "\n";
        qDebug() << " ---------------------------------------------------------" << "\n";
		piece = piece->getNext();
		cnt++;
	}
	
    qDebug() << "Total Size: " << text.getLength() << "\n";

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
