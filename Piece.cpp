#include "Piece.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

Piece::Piece()
{

}

Piece::Piece(std::string file, size_t length, size_t pos, Piece * next, bool dummy)
{
    mFileName = file;
    mLength = length;
    mFilePos = pos;
	mNext = next;
	mFileStream.open(mFileName);
	mIsDummy = dummy;
}

void Piece::setNext(Piece * next)
{
    mNext = next;
}

Piece * Piece::getNext() const
{
    return mNext;
}

std::string Piece::getText()
{
    std::string text;

	if (mIsDummy)
		return "";

    // open file
    if(!mFileStream.is_open())
    {
        assert(false);
        return "";
    }

    // check file size
    if (Helpers::GetFileSize(mFileName) < mFilePos + mLength)
    {
        assert(false);
        return "";
    }

    // read pos -> length
    mFileStream.seekg(mFilePos);
    text.resize(mLength);
    mFileStream.read(&text[0], mLength);

    return text;
}

size_t Piece::getLength() const
{
	return mLength;
}

void Piece::setLength(size_t length)
{
	mLength = length;
}

std::string Piece::getFile() const
{
	return mFileName;
}

size_t Piece::getFilePos() const
{
	return mFilePos;
}

std::string Piece::getFont() const
{
	return "font1";
}

std::string Piece::getStyle() const
{
	return "sty";
}
