#pragma once

#include <QList>
#include <QLocale>
#include <QMap>

/**
 * @brief Types of icons in a Tic-Tac-Toe square.
 */
enum class SquareIcon {
    X,      // Square marked with X.
    O,      // Square marked with O.
    EMPTY,  // Square is empty.
};

/**
 * @brief Acquires language names and their locale information.
 */
class Lang {
public:
    enum Name {
        ENGLISH,
        CHINESE_SIMP,
        CHINESE_TRAD,
    };

    static QStringList getLangNames();
    static QString getLangTerrCode(Name lang);

private:
    static const QMap<Name, QLocale> LOCALES;
};

/**
 * @brief Contains shared attributes for saving and loading game state.
 */
class Attr {
public:
    // Progress
    QList<SquareIcon> board;
    bool xTurn;
    bool ended;

    // Settings
    Lang::Name lang;
    bool animated;
    bool twoPlayer;
    bool showScores;

    // Stats
    int xPoint;
    int tiePoint;
    int oPoint;

    int getTotalPlays() const;

    void resetProgress();
    void resetSettings();
    void resetStats();

    void save();
    bool load();

    static Attr &get();

private:
    Attr();
    ~Attr();
};
