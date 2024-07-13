#pragma once

#include <QDialog>
#include <QBoxLayout>
#include <QHash>
#include <QKeyEvent>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>

class Game;

class Dialog : public QDialog {
    Q_OBJECT

public:
    Dialog(Game *game, const QIcon &icon, const QString &title);
    ~Dialog();

protected:
    Game *game;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *okButton;

    void keyPressEvent(QKeyEvent *event);
};

class SettingsDialog : public Dialog {
    Q_OBJECT

public:
    SettingsDialog(Game *game);
    ~SettingsDialog();

private:
    QHash<QCheckBox *, bool *> boxes;
    QComboBox *langBox;
    QComboBox *resetBox;

    QVBoxLayout *newGroup(const QString &title);
    void addCheckBox(QLayout *layout, const QString &text, bool &state);
    void applySettings();
};

class HelpDialog : public Dialog {
    Q_OBJECT

public:
    HelpDialog(Game *game);
    ~HelpDialog();

private:
    QTextBrowser *newBrowser(const QString &path);
};
