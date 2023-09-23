#include "Attr.h"

void Attr::save() {
    QFile file("TicTacToe_Data");
    file.open(QFile::WriteOnly);

    QDataStream out(&file);
    out << xPlaced;
    out << oPlaced;
    out << ended;

    out << numPlayed;
    out << xScore;
    out << oScore;
    out << numTied;

    out << animated;
    out << hintVisible;

    file.close();
}

bool Attr::load() {
    QFile file("TicTacToe_Data");
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    in >> xPlaced;
    in >> oPlaced;
    in >> ended;

    in >> numPlayed;
    in >> xScore;
    in >> oScore;
    in >> numTied;

    in >> animated;
    in >> hintVisible;

    file.close();
    return true;
}
