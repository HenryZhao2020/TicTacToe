#pragma once

#include "PCH.h"

class Game;

class Dialog : public QDialog {
    Q_OBJECT

public:
    Dialog(Game *game, const QIcon &icon, const QString &title);

    void keyPressEvent(QKeyEvent *event);

protected:
    Game *game;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *okButton;
};

class SettingsDialog : public Dialog {
    Q_OBJECT

public:
    SettingsDialog(Game *game);

private:
    QHash<QCheckBox *, bool *> boxes;

    void addBox(const QString &text, bool *var);
    void apply();
};

class StatsDialog : public Dialog {
    Q_OBJECT

public:
    StatsDialog(Game *game);

private:
    QFormLayout *formLayout;

    void addRow(const QString &labelText, int value);
    void reset();
};

class HelpDialog : public Dialog {
    Q_OBJECT

public:
    HelpDialog(Game *game);

private:
    QTabWidget *tabWidget;

    QTextEdit *newTextEdit(const QString &fileName);
};
