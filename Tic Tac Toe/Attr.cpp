#include "Attr.h"

QList<int> Attr::xPlaced;
QList<int> Attr::oPlaced;
bool Attr::ended;

int Attr::numPlayed;
int Attr::xScore;
int Attr::oScore;
int Attr::numTied;

bool Attr::animated = true;
bool Attr::hintVisible = true;

void Attr::save() {
    QFile file("../Saved");
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
    QFile file("../Saved");
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
