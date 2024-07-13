#pragma once

#include <QList>
#include <QLocale>

enum class Role {
    X, O, EMPTY,
};

class Progress {
public:
    QList<Role> board;
    bool xTurn;
    bool ended;

    Progress();
    ~Progress();
};

class Settings {
public:
    static const QList<QLocale> LANGS;

    int lang;
    bool animated;
    bool twoPlayer;
    bool showScores;

    Settings();
    ~Settings();

    static QString getLangTerrCode(int i);
};

class Stats {
public:
    int xPoint;
    int tiePoint;
    int oPoint;

    Stats();
    ~Stats();

    int getTotalPlays() const;
};

class Attr {
public:
    static Progress &getProgress();
    static Settings &getSettings();
    static Stats &getStats();

    static void resetProgress();
    static void resetSettings();
    static void resetStats();

    static void save();
    static bool load();

private:
    static Progress progress;
    static Settings settings;
    static Stats stats;
};
