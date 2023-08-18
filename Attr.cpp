#include "Attr.h"

QList<int> Attr::xPlaced = {};
QList<int> Attr::oPlaced = {};
bool Attr::ended = false;

int Attr::numPlayed = 0;
int Attr::xScore = 0;
int Attr::oScore = 0;
int Attr::numTied = 0;

bool Attr::animated = true;
bool Attr::hintVisible = true;

void Attr::save() {
    QFile file("TicTacToe_Data");
    file.open(QFile::WriteOnly);

    QDataStream stream(&file);
    stream << xPlaced;
    stream << oPlaced;
    stream << ended;

    stream << numPlayed;
    stream << xScore;
    stream << oScore;
    stream << numTied;

    stream << animated;
    stream << hintVisible;

    file.close();
}

bool Attr::load() {
    QFile file("TicTacToe_Data");
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream stream(&file);
    stream >> xPlaced;
    stream >> oPlaced;
    stream >> ended;

    stream >> numPlayed;
    stream >> xScore;
    stream >> oScore;
    stream >> numTied;

    stream >> animated;
    stream >> hintVisible;

    file.close();
    return true;
}
