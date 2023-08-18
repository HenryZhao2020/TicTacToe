#ifndef ATTR_H
#define ATTR_H

#include "PCH.h"

class Attr {
public:
    static QList<int> xPlaced;
    static QList<int> oPlaced;
    static bool ended;

    static int numPlayed;
    static int xScore;
    static int oScore;
    static int numTied;

    static bool animated;
    static bool hintVisible;

    static void save();
    static bool load();
};

#endif
