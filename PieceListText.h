#ifndef PIECELISTTEXT_H
#define PIECELISTTEXT_H

#include "Piece.h"
#include "UpdateEvent.h"
#include <QFontMetrics>
#include <vector>

struct Word {
    int tpos;
    int len;
};

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
    Piece * getFirst() const;
    int getLength() const;

    // load / store
    bool load(std::string const& file);
    bool save(std::string const& file);

    // find / select
    Word wordAt(int tpos);
    int find(std::string const& word);

    // listeners
    void addListener(UpdateEventListener * listener);
    void removeListener(UpdateEventListener * listener);

private:
    // members
    int mLength;
    Piece * mFirstPiece;
    std::string mScratchFileName;
	std::fstream mScratchFileStream;
	std::string mFileName;

    // helpers
    std::string getFileContent();

    typedef std::vector<UpdateEventListener*> TListeners;
    typedef std::vector<UpdateEventListener*>::iterator TListenersIter;
    TListeners mListeners;
    void notify(UpdateEvent e);
};

#endif // PIECELISTTEXT_H
