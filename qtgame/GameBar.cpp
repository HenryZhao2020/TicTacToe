#include "GameBar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "HelpDialog.h"
#include "QtGame.h"

namespace {
    constexpr int GAMEBAR_ICON_SIDE{30};
}

GameBar::GameBar(QtGame *game)
    : QFrame{game}
    , infoLabel{new QLabel{this}}
    , resetButton{createButton(QIcon{":/icons/Reset.svg"}, tr("Reset"))}
    , helpButton{createButton(QIcon{":/icons/Help.svg"}, tr("Help"))} {

    const auto barLayout = new QHBoxLayout{this};  // NOLINT
    barLayout->setSpacing(5);
    barLayout->addWidget(infoLabel);
    barLayout->addStretch();
    barLayout->addWidget(resetButton);
    barLayout->addWidget(helpButton);

    for (auto *button : buttons) {
        button->setCursor(Qt::PointingHandCursor);
    }

    connect(resetButton, &QPushButton::clicked, game, &QtGame::resetRound);
    connect(helpButton, &QPushButton::clicked, this, [this] {
        const auto dialog = new HelpDialog{this};
        dialog->show();
    });
}

void GameBar::setInfoMessage(const QString &text) const {
    infoLabel->setText(text);
}

void GameBar::setResetEnabled(const bool state) const {
    resetButton->setVisible(state);
}

void GameBar::onScale(const double scale) {
    const int scaledIconSize{static_cast<int>(scale * GAMEBAR_ICON_SIDE)};
    for (auto *button : buttons) {
        button->setIconSize(QSize{scaledIconSize, scaledIconSize});
    }
}

QPushButton *GameBar::createButton(const QIcon &icon, const QString &toolTip) {
    const auto button = new QPushButton{this};  // NOLINT
    button->setIcon(icon);
    button->setToolTip(toolTip);
    buttons.append(button);
    return button;
}
