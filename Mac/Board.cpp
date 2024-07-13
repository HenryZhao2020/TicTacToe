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

    for (int i = 0; i < 9; i++) {
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

const QIcon &Board::getRoleIcon(const Role &role, bool gray) {
    static const QIcon &X = IconUtil::load(":/icons/X.svg");
    static const QIcon &X_GRAY = IconUtil::gray(":/icons/X.svg");
    static const QIcon &O = IconUtil::load(":/icons/O.svg");
    static const QIcon &O_GRAY = IconUtil::gray(":/icons/O.svg");
    static const QIcon EMPTY;

    switch (role) {
    case Role::X:
        return gray ? X_GRAY : X;
    case Role::O:
        return gray ? O_GRAY : O;
    default:
        return EMPTY;
    }
}

void Board::place(int i, const QIcon &icon, bool animated) {
    setFrozen(true);

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
    place(i, getRoleIcon(Role::X), Attr::getSettings().animated);
    Attr::getProgress().board[i] = Role::X;
    Attr::getProgress().xTurn = false;

    if (isRoundEnded()) {
        endRound();
        return;
    }

    gameBar->setInfoVisible(false);
    QTimer::singleShot(500, this, [this] {
        gameBar->setInfoText(tr("O's turn"));
    });

    if (!Attr::getSettings().twoPlayer) {
        QTimer::singleShot(1000, this, [this] {
            placeO();
        });
    }
}

void Board::placeO(int i) {
    if (i == -1) {
        i = GameAI::getBestMove();
    }

    place(i, getRoleIcon(Role::O), Attr::getSettings().animated);
    Attr::getProgress().board[i] = Role::O;
    Attr::getProgress().xTurn = true;

    if (isRoundEnded()) {
        endRound();
        return;
    }

    gameBar->setInfoVisible(!Attr::getSettings().twoPlayer);
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
    return winner != Role::EMPTY || GameAI::isDraw();
}

void Board::endRound() {
    setFrozen(false);
    Attr::getProgress().ended = true;

    const QList<int> &winSeq = GameAI::getWinSeq();
    for (int i = 0; i < 9; i++) {
        Role role = Attr::getProgress().board[i];
        if (role == Role::X && !winSeq.contains(i)) {
            squares[i]->setIcon(getRoleIcon(Role::X, true));
        } else if (role == Role::O && !winSeq.contains(i)) {
            squares[i]->setIcon(getRoleIcon(Role::O, true));
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

    if (winner == Role::X) {
        icon = IconUtil::load(":/icons/Win.svg");
        text = tr("The winner is X!");
        Attr::getStats().xPoint++;
    } else if (winner == Role::O) {
        bool twoPlayer = Attr::getSettings().twoPlayer;
        icon = IconUtil::load(twoPlayer ? ":/icons/Win.svg" : ":/icons/AI.svg");
        text = tr("The winner is O!");
        Attr::getStats().oPoint++;
    } else {
        icon = IconUtil::load(":/icons/Tie.svg");
        text = tr("Tie!");
        Attr::getStats().tiePoint++;
    }

    gameBar->setInfoIcon(icon);
    gameBar->setInfoText(text);
    gameBar->setRestartEnabled(true);
    QTimer::singleShot(4000, this, [this] {
        gameBar->setInfoText(tr("Click any square to restart..."));
    });

    game->getScoreBoard()->updateValues();
}
