#include "Attr.h"

#include <QFile>
#include <QDataStream>

const QList<QLocale> Settings::LANGS = {
    QLocale(QLocale::English, QLocale::LatinScript, QLocale::World),
    QLocale(QLocale::Chinese, QLocale::SimplifiedChineseScript),
    QLocale(QLocale::Chinese, QLocale::TraditionalChineseScript),
};

Progress Attr::progress;
Settings Attr::settings;
Stats Attr::stats;

Progress::Progress() {
    board.fill(Role::EMPTY, 9);
    xTurn = (Attr::getStats().getTotalPlays() % 2 == 0);
    ended = false;
}

Progress::~Progress() {}

Settings::Settings() {
    lang = 0;
    animated = true;
    twoPlayer = false;
    showScores = true;
}

Settings::~Settings() {}

QString Settings::getLangTerrCode(int i) {
    QString langCode = QLocale::languageToCode(LANGS[i].language());
    QString terrCode = QLocale::territoryToCode(LANGS[i].territory());
    return langCode + "_" + terrCode;
}

Stats::Stats() {
    xPoint = 0;
    tiePoint = 0;
    oPoint = 0;
}

Stats::~Stats() {}

int Stats::getTotalPlays() const {
    return xPoint + tiePoint + oPoint;
}

Progress &Attr::getProgress() {
    return progress;
}

Settings &Attr::getSettings() {
    return settings;
}

Stats &Attr::getStats() {
    return stats;
}

void Attr::resetProgress() {
    progress = Progress();
}

void Attr::resetSettings() {
    settings = Settings();
}

void Attr::resetStats() {
    stats = Stats();
}

void Attr::save() {
    QFile file("TTT_Data");
    if (!file.open(QFile::WriteOnly)) {
        return;
    }

    QDataStream out(&file);
    out << progress.board;
    out << progress.xTurn;
    out << progress.ended;

    out << settings.lang;
    out << settings.animated;
    out << settings.twoPlayer;
    out << settings.showScores;

    out << stats.xPoint;
    out << stats.tiePoint;
    out << stats.oPoint;

    file.close();
}

bool Attr::load() {
    QFile file("TTT_Data");
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    in >> progress.board;
    in >> progress.xTurn;
    in >> progress.ended;

    in >> settings.lang;
    in >> settings.animated;
    in >> settings.twoPlayer;
    in >> settings.showScores;

    in >> stats.xPoint;
    in >> stats.tiePoint;
    in >> stats.oPoint;

    file.close();
    return true;
}
