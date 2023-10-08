#pragma once

#include "PCH.h"

namespace Attr {
    extern QList<int> xPlaced;
    extern QList<int> oPlaced;
    extern bool ended;

    extern int numPlayed;
    extern int xScore;
    extern int oScore;
    extern int numTied;

    extern bool animated;
    extern bool hintVisible;

    void save();
    bool load();
}
