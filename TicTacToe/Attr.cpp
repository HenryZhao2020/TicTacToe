#include "Attr.h"

Attr::Attr() {
    // Reset all attributes to their default values
    resetProgress();
    resetSettings();
    resetStats();
}

Attr::~Attr() {

}

int Attr::getTotalPlays() {
    return xWins + oWins + ties;
}

void Attr::resetProgress() {
    xPlaced = {};
    oPlaced = {};
    xTurn = (getTotalPlays() % 2 == 0);
    ended = false;
}

void Attr::resetSettings() {
    playAI = true;
    animated = true;
    hinted = true;
    lang = Lang::ENGLISH;
}

void Attr::resetStats() {
    xWins = 0;
    oWins = 0;
    ties = 0;
}

void Attr::save() {
    QFile file("../Saved");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QDataStream out(&file);
    out << xPlaced;
    out << oPlaced;
    out << xTurn;
    out << ended;

    out << playAI;
    out << animated;
    out << hinted;

    out << xWins;
    out << oWins;
    out << ties;
    out << lang;

    file.close();
}

bool Attr::load() {
    QFile file("../Saved");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }

    QDataStream in(&file);
    in >> xPlaced;
    in >> oPlaced;
    in >> xTurn;
    in >> ended;

    in >> playAI;
    in >> animated;
    in >> hinted;

    in >> xWins;
    in >> oWins;
    in >> ties;
    in >> lang;

    file.close();
    return true;
}

Attr &Attr::get() {
    static Attr attr;
    return attr;
}
