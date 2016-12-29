#ifndef PIECELISTTEXT_H
#define PIECELISTTEXT_H

#include "Piece.h"


class PieceListText
{
public:
    PieceListText();

    // basic
    void insert(size_t pos, char c);
    Piece * split(size_t pos);
    void delete_(size_t from, size_t to);

    // load / store
    bool load(std::string const& file);
	bool save();

	Piece * getFirst() const;
	size_t getLength() const;


private:
    size_t mLength;
    Piece * mFirstPiece;
    std::string mScratchFileName;
	std::fstream mScratchFileStream;
	std::string mFileName;
};

#endif // PIECELISTTEXT_H
