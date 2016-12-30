#ifndef PIECE_H
#define PIECE_H

#include <QFont>
#include <string>
#include <fstream>

class Piece
{
public:
    Piece();
    Piece(std::string file, size_t length, size_t pos, Piece * next, bool dummy = false);
    Piece(std::string file, size_t length, size_t pos, Piece * next, QFont font, bool dummy = false);

    void setNext(Piece * next);
    Piece * getNext() const;

    std::string getText();

	size_t getLength() const;
	void setLength(size_t length);
	
	std::string getFile() const;
	size_t getFilePos() const;

    QFont getFont() const;
    void setFont(QFont const& font);

private:
    size_t mLength;
    std::string mFileName;
	std::fstream mFileStream;
	size_t mFilePos;
    Piece * mNext;
	bool mIsDummy;
    QFont mFont;

};

#endif // PIECE_H
