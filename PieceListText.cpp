
#include "PieceListText.h"
#include "Helpers.h"
#include "Parser.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>

std::string const cScratchFileName = "scratch.txt";



PieceListText::PieceListText()
{
	mFirstPiece = nullptr;
	mLength = 0;
	mFileName = "";
}

void PieceListText::insert(size_t pos, char c)
{
	Piece * p = split(pos); 

	size_t last_index = p->getFilePos() + p->getLength();
	size_t scratchFileSize = Helpers::GetFileSize(mScratchFileName);
	if (!(p->getFile() == cScratchFileName && last_index == scratchFileSize))
	{
		Piece * q = new Piece(mScratchFileName, 0, scratchFileSize, p->getNext());
		p->setNext(q);
		p = q;
	}

	mScratchFileStream << c;
	mScratchFileStream.flush();

	p->setLength(p->getLength() + 1);
	mLength++;
}

Piece * PieceListText::split(size_t pos)
{
	if (pos == 0) return mFirstPiece;

	//--- set p to piece containing pos
	Piece * p = mFirstPiece;

	size_t len = p->getLength();
	while (pos > len) {
		p = p->getNext();
		len = len + p->getLength();
	}

	//--- split piece p
	if (pos != len) {
		size_t len2 = len - pos;
		size_t len1 = p->getLength() - len2;
		p->setLength(len1);
		Piece * q = new Piece(p->getFile(), len2, p->getFilePos() + len1, p->getNext());
		p->setNext(q);
	}
	return p;
}

void PieceListText::delete_(size_t from, size_t to)
{
	Piece * a = split(from);
	Piece * b = split(to);
	a->setNext(b->getNext());
}

Piece * PieceListText::getFirst() const
{
	return mFirstPiece;
}

size_t PieceListText::getLength() const
{
	return mLength;
}

bool PieceListText::load(std::string const& file)
{
	mFileName = file;
	size_t length = 0;

	Piece * piece = Parser::parseFile(file, length);
	if (piece != nullptr)
	{
		mFirstPiece = piece;
		mLength = length;
		mScratchFileName = cScratchFileName;
		mScratchFileStream.open(mScratchFileName, std::ofstream::out | std::ofstream::trunc);
		return true;
	}
	else
	{
		mFirstPiece = nullptr;
		mLength = 0;
		assert(false);
		return false;
	}
}

bool PieceListText::save()
{
	return Parser::writeFile(mFileName, mFirstPiece);
}