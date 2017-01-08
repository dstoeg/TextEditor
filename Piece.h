#ifndef PIECE_H
#define PIECE_H

#include <QFont>
#include <string>
#include <fstream>

class Piece
{
public:
    Piece();
    Piece(std::string file, int length, int pos, Piece * next, bool dummy = false);
    Piece(std::string file, int length, int pos, Piece * next, QFont font, bool dummy = false);

    void setNext(Piece * next);
    Piece * getNext() const;
    std::string getText();
    int getLength() const;
    void setLength(int length);
	std::string getFile() const;
    int getFilePos() const;
    QFont getFont() const;
    void setFont(QFont const& font);
    Piece * getDeepCopy();

private:
    int mLength;
    std::string mFileName;
	std::fstream mFileStream;
    int mFilePos;
    Piece * mNext;
	bool mIsDummy;
    QFont mFont;

};

#endif // PIECE_H
