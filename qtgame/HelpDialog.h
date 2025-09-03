#ifndef TICTACTOE_HELPDIALOG_H
#define TICTACTOE_HELPDIALOG_H

#include <QDialog>

/// Displays app name, version, and author information.
class HelpDialog final : public QDialog {
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
};

#endif //TICTACTOE_HELPDIALOG_H
