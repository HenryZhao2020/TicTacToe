#include "Board.h"
#include "Game.h"
#include "GameBar.h"
#include "Square.h"
#include "ScoreBoard.h"
#include "Attr.h"
#include "GameAI.h"
#include "IconUtil.h"

#include <QGridLayout>

Board::Board(Game *game)
    : QFrame(game), game(game), gameBar(game->getGameBar()) {
    setFrozen(false);

    auto boardLayout = new QGridLayout(this);
    boardLayout->setSpacing(0);
    boardLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 9; ++i) {
        squares[i] = new Square(this, i);

        int row = i / 3;
        int col = i % 3;
        boardLayout->addWidget(squares[i], row * 2, col * 2);

        if (row != 2) {
            auto hLine = new QFrame(this);
            hLine->setObjectName("line");
            boardLayout->addWidget(hLine, row * 2 + 1, 0, 1, 5);
        }

        if (col != 2) {
            auto vLine = new QFrame(this);
            vLine->setObjectName("line");
            boardLayout->addWidget(vLine, row * 2, col * 2 + 1);
        }
    }
}

Board::~Board() {}

const QIcon &Board::getSquareIcon(SquareIcon icon, bool gray) {
    static const QIcon &X = IconUtil::load(":/icons/X.svg");
    static const QIcon &X_GRAY = IconUtil::gray(":/icons/X.svg");
    static const QIcon &O = IconUtil::load(":/icons/O.svg");
    static const QIcon &O_GRAY = IconUtil::gray(":/icons/O.svg");
    static const QIcon EMPTY;

    switch (icon) {
    case SquareIcon::X:
        return gray ? X_GRAY : X;
    case SquareIcon::O:
        return gray ? O_GRAY : O;
    default:
        return EMPTY;
    }
}

void Board::place(int i, const QIcon &icon, bool animated) {
    setFrozen(true);

    if (i < 0 || i > 8) {
        qCritical() << "Square index out of bounds!";
    }

    disconnect(squares[i], &Square::clicked, nullptr, nullptr);
    squares[i]->setIcon(icon);

    int size = squares[i]->width() * 0.70;
    if (animated) {
        squares[i]->zoomIn(size);
    } else {
        squares[i]->setIconSize(QSize(size, size));
    }

    QTimer::singleShot(500, this, [this] {
        setFrozen(false);
    });
}

void Board::placeX(int i) {
    place(i, getSquareIcon(SquareIcon::X), Attr::get().animated);
    Attr::get().board[i] = SquareIcon::X;
    Attr::get().xTurn = false;

    if (isRoundEnded()) {
        endRound();
        return;
    }

    gameBar->setInfoVisible(false);
    QTimer::singleShot(500, this, [this] {
        gameBar->setInfoText(tr("O's turn"));
    });

    if (!Attr::get().twoPlayer) {
        QTimer::singleShot(1000, this, [this] {
            placeO();
        });
    }
}

void Board::placeO(int i) {
    if (i == -1) {
        i = GameAI::getBestMove();
    }

    place(i, getSquareIcon(SquareIcon::O), Attr::get().animated);
    Attr::get().board[i] = SquareIcon::O;
    Attr::get().xTurn = true;

    if (isRoundEnded()) {
        endRound();
        return;
    }

    gameBar->setInfoVisible(!Attr::get().twoPlayer);
    QTimer::singleShot(500, this, [this] {
        gameBar->setInfoText(tr("X's turn"));
    });
}

void Board::setFrozen(bool frozen) {
    this->frozen = frozen;
}

bool Board::isFrozen() {
    return frozen;
}

bool Board::isRoundEnded() {
    winner = GameAI::getWinner();
    return winner != SquareIcon::EMPTY || GameAI::isDraw();
}

void Board::endRound() {
    setFrozen(false);
    Attr::get().ended = true;

    const QList<int> &winSeq = GameAI::getWinSeq();
    for (int i = 0; i < 9; ++i) {
        SquareIcon icon = Attr::get().board[i];
        if (icon == SquareIcon::X && !winSeq.contains(i)) {
            squares[i]->setIcon(getSquareIcon(SquareIcon::X, true));
        } else if (icon == SquareIcon::O && !winSeq.contains(i)) {
            squares[i]->setIcon(getSquareIcon(SquareIcon::O, true));
        } else {
            disconnect(squares[i], &Square::clicked, nullptr, nullptr);
        }
        connect(squares[i], &Square::clicked, game, &Game::restart);
    }

    for (int i : winSeq) {
        squares[i]->flash();
    }

    QIcon icon;
    QString text;

    if (winner == SquareIcon::X) {
        icon = IconUtil::load(":/icons/Win.svg");
        text = tr("The winner is X!");
        ++Attr::get().xPoint;
    } else if (winner == SquareIcon::O) {
        bool twoPlayer = Attr::get().twoPlayer;
        icon = IconUtil::load(twoPlayer ? ":/icons/Win.svg" : ":/icons/AI.svg");
        text = tr("The winner is O!");
        ++Attr::get().oPoint;
    } else {
        icon = IconUtil::load(":/icons/Tie.svg");
        text = tr("Tie!");
        ++Attr::get().tiePoint;
    }

    gameBar->setInfoIcon(icon);
    gameBar->setInfoText(text);
    gameBar->setRestartEnabled(true);
    QTimer::singleShot(4000, this, [this] {
        gameBar->setInfoText(tr("Click any square to restart..."));
    });

    game->getScoreBoard()->updateValues();
}
