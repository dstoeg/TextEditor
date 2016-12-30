
#include "Parser.h"
#include "Helpers.h"

#include <QDebug>

#include <fstream>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <iostream>

char const EXISTS_HEADER = char(127);

#define cOFFSET_LEN	10


Piece * Parser::parseFile(std::string const& file, size_t & length)
{
	Piece * first = nullptr;
	std::ifstream f(file);
	if (f.is_open())
	{
		// read first character
		char in = f.get();

		if (in == EXISTS_HEADER)
		{
			// read offset
			int offset = parseNextInt(f);
			
			// read pieces
			first = new Piece("", 0, 0, nullptr, true);
			Piece * previous = first;
			size_t pos = offset;
			while ((int)f.tellg() < offset)
			{
				int len = parseNextInt(f);
				std::string font = parseNextString(f);
				std::string style = parseNextString(f);
                QFont qfont = parseFont(font, style);
				
				// append new piece
                Piece * piece = new Piece(file, len, pos, nullptr, qfont);
				pos += len;
				previous->setNext(piece);
				previous = piece;
			}

			// write length
			length = Helpers::GetFileSize(file) - offset;
		}
		else
		{
			// file doesn't have a header

			// actual first piece
			length = Helpers::GetFileSize(file);
			Piece * second = new Piece(file, length, 0, nullptr);

			// dummy piece
			first = new Piece("", 0, 0, second, true);
		}
	}
	else
	{
		first = nullptr;
		length = 0;
	}
	return first;
}

bool Parser::writeFile(std::string const& file, Piece * first)
{
	std::stringstream text;
	std::stringstream info;
	std::stringstream header;
	std::string output;
	Piece * piece = first;
	
	if (first != nullptr)
		piece = first->getNext();

	info << ";";
	while (piece != nullptr)
	{
		// add text
		text << piece->getText();

		// add meta info
        info << piece->getLength()                      << ";";
        info << qfontToFontString(piece->getFont())     << ";";
        info << qfontToStyleString(piece->getFont())    << ";";

		piece = piece->getNext();
	}

	// set header flag
	header << EXISTS_HEADER;

	// write offset
	size_t offset = header.str().size() + info.str().size() + cOFFSET_LEN;
	header << std::setw(cOFFSET_LEN) << offset;

	// put it all together
	output = header.str() + info.str() + text.str();

	std::ofstream out;
	out.open(file, std::ofstream::out | std::ofstream::trunc);
	out << output;
	out.close();

	return true;
}

int Parser::parseNextInt(std::ifstream & file)
{
	return std::stoi(parseNextString(file));
}

std::string Parser::parseNextString(std::ifstream & file)
{
	std::stringstream s;
	char c = file.get();

	while (c != ';' && c != EOF)
	{
		s << c;
		c = file.get();
	}
	return s.str();
}

std::string Parser::qfontToFontString(QFont font)
{
    std::string fontStr;
    fontStr.append(std::to_string(font.pixelSize()));
    fontStr.append("px ");
    fontStr.append(font.family().toStdString());
    return std::string(fontStr);
}

std::string Parser::qfontToStyleString(QFont font)
{
    std::string style;
    if(font.bold())
        style.push_back('b');
    if(font.italic())
        style.push_back('i');
    if(font.underline())
        style.push_back('u');
    return style;
}

QFont Parser::parseFont(std::string const& font, std::string const& style)
{
    QFont qFont;

    size_t idx = font.find("px");
    int size = std::stoi(font.substr(0, idx));
    qFont.setPixelSize(size);

    idx = font.find(' ') + 1;
    std::string family = font.substr(idx, font.size()-1);
    qFont.setFamily(QString::fromStdString(family));

    if (style.find('b') != std::string::npos)
        qFont.setBold(true);
    if (style.find('i') != std::string::npos)
        qFont.setItalic(true);
    if (style.find('u') != std::string::npos)
        qFont.setUnderline(true);

    return qFont;
}

std::string Parser::getFontAsString(QFont const& font)
{
    std::string fontStr;

    if (font.italic())
        fontStr.append("italic ");
    if (font.bold())
        fontStr.append("bold ");
    /* underline not supported */

    fontStr.append(std::to_string(font.pixelSize()) + "px ");
    fontStr.append(font.family().toStdString());

    return fontStr;
}
