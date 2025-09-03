#include "StatsView.h"

#include "QtGame.h"

#include <QHBoxLayout>
#include <QLabel>

StatsView::StatsView(QtGame *game)
    : QFrame{game}
    , xLabel{new QLabel{this}}
    , tieLabel{new QLabel{this}}
    , oLabel{new QLabel{this}} {

    const auto statsLayout = new QGridLayout{this};  // NOLINT
    statsLayout->addWidget(xLabel, 0, 0, Qt::AlignCenter);
    statsLayout->addWidget(tieLabel, 0, 1, Qt::AlignCenter);
    statsLayout->addWidget(oLabel, 0, 2, Qt::AlignCenter);
}

void StatsView::update(const GameStats &stats) const {
    xLabel->setText(QString{"X: %1"}.arg(stats.getXWins()));
    tieLabel->setText(QString{"Tie: %1"}.arg(stats.getTies()));
    oLabel->setText(QString{"O: %1"}.arg(stats.getOWins()));
}
