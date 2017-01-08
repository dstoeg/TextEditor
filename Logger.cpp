
#include "Logger.h"

#include <iostream>
#include <sstream>
#include <QDebug>

void Logger::dumpText(PieceListText & text)
{
	Piece * piece = text.getFirst();
    QString str;
    str += "|";
	while (piece != nullptr)
	{
        str += QString::fromStdString(piece->getText()) + "|";
		piece = piece->getNext();
	}
    qDebug() << str;
}

void Logger::dumpTextList(PieceListText & text)
{
	Piece * piece = text.getFirst();
	
    int cnt = 0;
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

void Logger::debugPrint(std::string const& text)
{
    qDebug() << QString::fromStdString(text) << "\n";
}

void Logger::dumpText(Piece * p)
{
    Piece * piece = p;
    QString str;
    str += "|";
    while (piece != nullptr)
    {
        str += QString::fromStdString(piece->getText()) + "|";
        piece = piece->getNext();
    }
    qDebug() << str;
}
