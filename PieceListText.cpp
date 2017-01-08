
#include "PieceListText.h"
#include "Helpers.h"
#include "Parser.h"
#include "Logger.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include <QDebug>
#include <ctype.h>
#include <cstdio>

std::string const cScratchFileName = "scratch.txt";



PieceListText::PieceListText()
{
    mFirstPiece = nullptr;
    mLength = 0;
    mFileName = "";
}

PieceListText::~PieceListText()
{
    Piece * piece = mFirstPiece;
    Piece * tmp = piece;

    while (piece != nullptr)
    {
        tmp = piece->getNext();
        delete piece;
        piece = tmp;
    }
}

void PieceListText::insert(int pos, char c, QFont font)
{
    Piece * p = split(pos);

    int last_index = p->getFilePos() + p->getLength();
    int scratchFileSize = Helpers::GetFileSize(mScratchFileName);
    if (!(p->getFile() == cScratchFileName && last_index == scratchFileSize && p->getFont() == font))
    {
        Piece * q = new Piece(mScratchFileName, 0, scratchFileSize, p->getNext(), font);
        p->setNext(q);
        p = q;
    }

    mScratchFileStream << c;
    mScratchFileStream.flush();

    p->setLength(p->getLength() + 1);
    mLength++;
    std::string letter(1,c);
    notify(UpdateEvent(pos, pos, letter));
}

void PieceListText::insert(int pos, std::string const& str, QFont font)
{
    for (int i=0; i<str.size(); i++)
        insert(pos++, str[i], font);
}

Piece * PieceListText::split(int pos)
{
    if (pos == 0) return mFirstPiece;

    //--- set p to piece containing pos
    Piece * p = mFirstPiece;

    int len = p->getLength();
    while (pos > len) {
        p = p->getNext();
        len = len + p->getLength();
    }

    //--- split piece p
    if (pos != len) {
        int len2 = len - pos;
        int len1 = p->getLength() - len2;
        p->setLength(len1);
        Piece * q = new Piece(p->getFile(), len2, p->getFilePos() + len1, p->getNext());
        p->setNext(q);
    }
    return p;
}

void PieceListText::delete_(int from, int to)
{
    Piece * a = split(from);
    Piece * b = split(to);
    a->setNext(b->getNext());
    delete b; b = nullptr;
    notify(UpdateEvent(from, to, ""));
}

char PieceListText::charAt(int pos)
{
    if (pos >= mLength)
        return '\0';

    Piece * piece = mFirstPiece;

    // skip dummy piece
    if (piece->getNext() == nullptr)
        return '\0';
    piece = piece->getNext();

    int count = 0;
    while (piece != nullptr)
    {
        if (pos < count + piece->getLength())
        {
            // in this piece
            std::string text = piece->getText();
            return text[pos - count];
        }
        count += piece->getLength();
        piece = piece->getNext();
    }
    //assert(false);
    return  '\0';
}

QFontMetrics PieceListText::metricsAt(int pos)
{
    if (pos >= mLength)
        return QFontMetrics(QFont());

    Piece * piece = mFirstPiece;

    // skip dummy piece
    if (piece->getNext() == nullptr)
        return QFontMetrics(QFont());
    piece = piece->getNext();

    int count = 0;
    while (piece != nullptr)
    {
        if (pos < count + piece->getLength())
        {
            // in this piece
            return QFontMetrics(piece->getFont());
        }
        count += piece->getLength();
        piece = piece->getNext();
    }
    //assert(false);
    return  QFontMetrics(QFont());
}

Piece * PieceListText::getFirst() const
{
    return mFirstPiece;
}

int PieceListText::getLength() const
{
    return mLength;
}

bool PieceListText::load(std::string const& file)
{
    mFileName = file;
    int length = 0;

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

bool PieceListText::save(std::string const& file)
{
    return Parser::writeFile(file, mFirstPiece);
}

void PieceListText::addListener(UpdateEventListener * listener)
{
    mListeners.push_back(listener);
}

void PieceListText::removeListener(UpdateEventListener * listener)
{
    TListenersIter iter = std::find(mListeners.begin(), mListeners.end(), listener);
    if (iter != mListeners.end())
        mListeners.erase(iter);
}

void PieceListText::notify(UpdateEvent e)
{
    Logger::dumpText(*this);
    for (UpdateEventListener * listener : mListeners)
        listener->update(e);
}

Word PieceListText::wordAt(int tpos)
{
    Word word;
    int len = 0;
    int it = tpos;

    // check to the left
    char c = charAt(it);
    while (!isspace(c) && it > 0)
    {
        it--;
        len++;
        c = charAt(it);
    }

    word.tpos = (it != 0) ? it+1 : 0;

    // now to the right
    it = tpos+1;
    c = charAt(it);
    while (!isspace(c) && it < mLength-1)
    {
        it++;
        len++;
        c = charAt(it);
    }
    word.len = len + 1;

    return word;
}

std::string PieceListText::getFileContent()
{
    Piece * piece = getFirst();
    std::stringstream s;

    while (piece != nullptr)
    {
        s << piece->getText();
        piece = piece->getNext();
    }
    return s.str();
}

int PieceListText::find(std::string const& word)
{
    std::string s = getFileContent();
    size_t idx = s.find(word);
    return (idx == std::string::npos) ? -1 : int(idx);
}

