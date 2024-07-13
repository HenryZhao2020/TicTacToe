#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class Game;

class GameBar : public QFrame {
    Q_OBJECT

public:
    GameBar(Game *game);
    ~GameBar();

    void setInfoIcon(const QIcon &icon);
    void setInfoText(const QString &text);
    void setInfoVisible(bool visible);
    void setRestartEnabled(bool enabled);

private:
    QHBoxLayout *barLayout;
    QPushButton *iconButton;
    QLabel *infoLabel;
    QPushButton *restartButton;

    QTimer *infoTimer = nullptr;
    int infoLength;
    void typewriteInfo(const QString &text);

    QPushButton *newMenuButton(const QIcon &icon, const QString &tip);
};
