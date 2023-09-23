#pragma once

#include "PCH.h"

namespace Attr {
    inline QList<int> xPlaced;
    inline QList<int> oPlaced;
    inline bool ended;

    inline int numPlayed;
    inline int xScore;
    inline int oScore;
    inline int numTied;

    inline bool animated = true;
    inline bool hintVisible = true;

    void save();
    bool load();
}
