#ifndef PIECELISTTEXT_H
#define PIECELISTTEXT_H

#include "Piece.h"
#include "UpdateEvent.h"

#include <QFontMetrics>

#include <vector>

class PieceListText
{
public:
    PieceListText();
    ~PieceListText();

    // basic
    void insert(int pos, char c, QFont font);
    void insert(int pos, std::string const& str, QFont font);
    Piece * split(int pos);
    void delete_(int from, int to);
    char charAt(int pos);
    QFontMetrics metricsAt(int pos);

    // load / store
    bool load(std::string const& file);
    bool save(std::string const& file);

	Piece * getFirst() const;
    int getLength() const;

    // listeners
    void addListener(UpdateEventListener * listener);
    void removeListener(UpdateEventListener * listener);

private:
    int mLength;
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
