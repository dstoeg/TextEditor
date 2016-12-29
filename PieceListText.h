#ifndef PIECELISTTEXT_H
#define PIECELISTTEXT_H

#include "Piece.h"
#include "UpdateEvent.h"

#include <vector>

class PieceListText
{
public:
    PieceListText();
    ~PieceListText();

    // basic
    void insert(size_t pos, char c);
    Piece * split(size_t pos);
    void delete_(size_t from, size_t to);

    // load / store
    bool load(std::string const& file);
	bool save();

	Piece * getFirst() const;
	size_t getLength() const;

    // listeners
    void addListener(UpdateEventListener * listener);
    void removeListener(UpdateEventListener * listener);

private:
    size_t mLength;
    Piece * mFirstPiece;
    std::string mScratchFileName;
	std::fstream mScratchFileStream;
	std::string mFileName;

    typedef std::vector<UpdateEventListener*> TListeners;
    typedef std::vector<UpdateEventListener*>::iterator TListenersIter;

    TListeners mListeners;
    void notify(UpdateEvent e);
};

#endif // PIECELISTTEXT_H
