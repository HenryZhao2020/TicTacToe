#include "Attr.h"

#include <QFile>
#include <QDataStream>

const QMap<Lang::Name, QLocale> Lang::LOCALES = {
    {Lang::ENGLISH, QLocale(QLocale::English, QLocale::LatinScript, QLocale::World)},
    {Lang::CHINESE_SIMP, QLocale(QLocale::Chinese, QLocale::SimplifiedChineseScript)},
    {Lang::CHINESE_TRAD, QLocale(QLocale::Chinese, QLocale::TraditionalChineseScript)},
};

QStringList Lang::getLangNames() {
    QStringList names;
    for (const auto &locale : LOCALES) {
        names.append(locale.nativeLanguageName());
    }
    return names;
}

QString Lang::getLangTerrCode(Name lang) {
    QString langCode = QLocale::languageToCode(LOCALES[lang].language());
    QString terrCode = QLocale::territoryToCode(LOCALES[lang].territory());
    return langCode + "_" + terrCode;
}

int Attr::getTotalPlays() const {
    return xPoint + tiePoint + oPoint;
}

void Attr::resetProgress() {
    board.fill(SquareIcon::EMPTY, 9);
    xTurn = (getTotalPlays() % 2 == 0);
    ended = false;
}

void Attr::resetSettings() {
    lang = Lang::ENGLISH;
    animated = true;
    twoPlayer = false;
    showScores = true;
}

void Attr::resetStats() {
    xPoint = 0;
    tiePoint = 0;
    oPoint = 0;
}

void Attr::save() {
    QFile file("TTT_Data");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QDataStream out(&file);
    out << board;
    out << xTurn;
    out << ended;

    out << lang;
    out << animated;
    out << twoPlayer;
    out << showScores;

    out << xPoint;
    out << tiePoint;
    out << oPoint;

    file.close();
}

bool Attr::load() {
    QFile file("TTT_Data");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }

    QDataStream in(&file);
    in >> board;
    in >> xTurn;
    in >> ended;

    in >> lang;
    in >> animated;
    in >> twoPlayer;
    in >> showScores;

    in >> xPoint;
    in >> tiePoint;
    in >> oPoint;

    file.close();
    return true;
}

Attr &Attr::get() {
    static Attr attr;
    return attr;
}

Attr::Attr() {
    resetProgress();
    resetSettings();
    resetStats();
}

Attr::~Attr() {}
