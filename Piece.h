#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <fstream>

class Piece
{
public:
    Piece();
    Piece(std::string file, size_t length, size_t pos, Piece * next, bool dummy = false);

    void setNext(Piece * next);
    Piece * getNext() const;

    std::string getText();

	size_t getLength() const;
	void setLength(size_t length);
	
	std::string getFile() const;
	size_t getFilePos() const;

	std::string getFont() const;

	std::string getStyle() const;


private:
    size_t mLength;
    std::string mFileName;
	std::fstream mFileStream;
	size_t mFilePos;
    Piece * mNext;
	bool mIsDummy;

    // TODO: Font
    // TODO: Style

};

#endif // PIECE_H
