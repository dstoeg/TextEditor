#include "Piece.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

Piece::Piece()
{

}

Piece::Piece(std::string file, int length, int pos, Piece * next, bool dummy)
{
    mFileName = file;
    mLength = length;
    mFilePos = pos;
    mNext = next;
	mIsDummy = dummy;

    // default font Calibri 20px
    mFont.setFamily("Calibri");
    mFont.setPixelSize(30);
    mFont.setBold(false);
    mFont.setItalic(false);
    mFont.setUnderline(false);
}

Piece::Piece(std::string file, int length, int pos, Piece * next, QFont font, bool dummy)
    : Piece(file, length, pos, next, dummy)
{
    mFont = font;
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

    mFileStream.open(mFileName);

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
    /*
    mFileStream.seekg(mFilePos);
    text.resize(mLength);
    mFileStream.read(&text[0], mLength);
    */

    // code above temporatily replaced by following HACK
    std::ifstream t(mFileName);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    t.close();

    size_t strSize = str.size();
    if (strSize < mFilePos + mLength)
        assert(false);

    return str.substr(mFilePos, mLength);
}

int Piece::getLength() const
{
	return mLength;
}

void Piece::setLength(int length)
{
	mLength = length;
}

std::string Piece::getFile() const
{
	return mFileName;
}

int Piece::getFilePos() const
{
	return mFilePos;
}

QFont Piece::getFont() const
{
    return mFont;
}

void Piece::setFont(QFont const& font)
{
    mFont = font;
}

Piece * Piece::getDeepCopy()
{
    return new Piece(mFileName, mLength, mFilePos, mNext, mFont, mIsDummy);
}

