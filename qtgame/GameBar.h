#ifndef TICTACTOE_GAMEBAR_H
#define TICTACTOE_GAMEBAR_H

#include <QFrame>
#include <QList>

#include "Scalable.h"

class QLabel;
class QPushButton;

class QtGame;

/// Top bar widget: shows messages and offers reset control.
class GameBar final : public QFrame, public Scalable {
    Q_OBJECT

public:
    /// Creates a top-level toolbar bound to a QtGame.
    explicit GameBar(QtGame *game);

    /// Sets the info label text.
    void setInfoMessage(const QString &text) const;

    /// Enables or disables the reset button.
    void setResetEnabled(bool state) const;

private:
    QLabel *infoLabel{};
    QList<QPushButton *> buttons;
    QPushButton *resetButton{};
    QPushButton *helpButton{};

    /// Scales button icon sizes.
    void onScale(double scale) override;

    /// Creates a menu bar button with the given icon and tool tip.
    [[nodiscard]] QPushButton *createButton(
        const QIcon &icon,
        const QString &toolTip);
};

#endif // TICTACTOE_GAMEBAR_H
