#include "Board.h"
#include "Game.h"
#include "GameBar.h"
#include "Square.h"
#include "Attr.h"

const QList<QList<int>> Board::SEQUENCES = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},    // Horizontal
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},    // Vertical
    {0, 4, 8}, {2, 4, 6}                // Diagonal
};

Board::Board(Game *game)
    : QFrame(game), game(game), gameBar(game->getGameBar()) {
    // Set up the layout
    auto gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 9; ++i) {
        // Place the square in the grid
        squares[i] = new Square(this, i);
        gridLayout->addWidget(squares[i], i / 3, i % 3);
        // Add 0-8 to the list
        notPlaced.append(i);
    }
}

Board::~Board() {

}

void Board::placeIcon(int i, const QIcon &icon, bool animated) {
    // 'Disable' the board while placing the icon to add a short delay
    setInteractive(false);
    // Mark the specified index location as placed
    notPlaced.removeOne(i);

    // Place the icon on the square
    squares[i]->setIcon(icon);
    // Disable the square
    disconnect(squares[i], &Square::clicked, nullptr, nullptr);

    // Apply animation if enabled
    if (animated) {
        squares[i]->zoomIn();
    } else {
        squares[i]->setIconSize(QSize(64, 64));
    }

    // After 500ms, make the board interactive again
    QTimer::singleShot(500, this, [this] {
        setInteractive(true);
    });
}

void Board::placeSquare(int i) {
    // If the board is not interactive, exit the function
    if (!isInteractive()) {
        return;
    }

    // If it is X's turn, place the "X" icon on the board
    if (Attr::get().xTurn) {
        placeX(i);
    // If it is O's turn, and the player is not playing against AI,
    // place the "O" icon on the board
    } else if (!Attr::get().playAI) {
        placeO(i);
    }
}

void Board::placeX(int i) {
    // Place the 'X' icon
    placeIcon(i, Icon::load("X.svg"), Attr::get().animated);
    Attr::get().xPlaced.append(i);

    // Give the next turn to 'O'
    Attr::get().xTurn = false;

    // If the round has ended after X's turn, exit the function
    if (isEnded()) {
        return;
    }

    // Update the game bar
    gameBar->setHintVisible(false);
    QTimer::singleShot(500, this, [this] {
        gameBar->setHintText("O's turn");
    });

    // If the player is playing against AI,
    // the AI will take its turn after 1s
    if (Attr::get().playAI) {
        QTimer::singleShot(1000, this, [this] {
            placeO();
        });
    }
}

void Board::placeO(int i) {
    // AI calculating O's next move
    if (i == -1) {
        i = getNextO();
    }

    // Place the 'O' icon
    placeIcon(i, Icon::load("O.svg"), Attr::get().animated);
    Attr::get().oPlaced.append(i);

    // Give the next turn to 'X'
    Attr::get().xTurn = true;

    // If the round has ended after O's turn, exit the function
    if (isEnded()) {
        return;
    }

    // Update the game bar
    gameBar->setHintVisible(Attr::get().hinted && Attr::get().playAI);
    QTimer::singleShot(500, this, [this] {
        gameBar->setHintText("X's turn");
    });
}

void Board::setInteractive(bool interactive) {
    this->interactive = interactive;
}

bool Board::isInteractive() {
    return interactive;
}

int Board::getNextO() {
    // Check if 'O' has a winning move
    int i = getWinningMove(Attr::get().oPlaced);
    // If not, try to take over X's winning move
    if (i == -1) {
        i = getWinningMove(Attr::get().xPlaced);
    }
    // If neither X nor O has a winning move, choose a random empty square
    if (i == -1) {
        i = notPlaced[QRandomGenerator::global()->bounded(notPlaced.size())];
    }

    return i;
}

int Board::getWinningMove(const QList<int> &placed) {
    // If only 1 index is missing to complete a row,
    // then that index will be the winning move
    for (const auto &seq : SEQUENCES) {
        if (placed.contains(seq[0]) && placed.contains(seq[1]) &&
            notPlaced.contains(seq[2])) {
            return seq[2];
        }
        if (placed.contains(seq[0]) && placed.contains(seq[2]) &&
            notPlaced.contains(seq[1])) {
            return seq[1];
        }
        if (placed.contains(seq[1]) && placed.contains(seq[2]) &&
            notPlaced.contains(seq[0])) {
            return seq[0];
        }
    }

    return -1;
}

bool Board::isEnded() {
    // Check if X or O has occupied a winning sequence
    for (const auto &seq : SEQUENCES) {
        // X wins
        if (containsAll(Attr::get().xPlaced, seq)) {
            xWins(seq);
            return true;
        }

        // O wins
        if (containsAll(Attr::get().oPlaced, seq)) {
            oWins(seq);
            return true;
        }
    }

    // If there is no empty square left, the round will end in a tie
    if (notPlaced.isEmpty()) {
        tie();
        return true;
    }

    return false;
}

void Board::end(const QIcon &icon, const QString &text) {
    // Update the game bar
    gameBar->setHintIcon(icon);
    gameBar->setHintText(text);
    gameBar->setRestartVisible(true);

    // After 3s, notify the player to click a square to restart
    QTimer::singleShot(3000, this, [this] {
        gameBar->setHintText("Click a square to restart...");
    });

    // Gray out all 'X' icons
    for (const auto &i : Attr::get().xPlaced) {
        squares[i]->setIcon(Icon::load("X_Gray.svg"));
    }

    // Gray out all 'O' icons
    for (const auto &i : Attr::get().oPlaced) {
        squares[i]->setIcon(Icon::load("O_Gray.svg"));
    }

    // Prevent any empty squares from placing icons on click after ending
    for (const auto &i : notPlaced) {
        disconnect(squares[i], &Square::clicked, nullptr, nullptr);
    }

    // Click any square to restart
    for (const auto &square : squares) {
        connect(square, &Square::clicked, this, [this] {
            game->restart();
        });
    }

    // Update the game progress
    Attr::get().ended = true;
}

void Board::xWins(const QList<int> &seq) {
    end(Icon::load("Win.svg"), "X wins!");

    // Update the statistics
    Attr::get().xWins++;

    // Highlight the winning sequence
    for (const auto &i : seq) {
        squares[i]->setIcon(Icon::load("X.svg"));
        // Apply animation is enabled
        if (Attr::get().animated) {
            squares[i]->flash();
        }
    }
}

void Board::oWins(const QList<int> &seq) {
    end(Icon::load(Attr::get().playAI ? "AI.svg" : "Win.svg"), "O wins!");

    // Update the statistics
    Attr::get().oWins++;

    // Highlight the winning sequence
    for (const auto &i : seq) {
        squares[i]->setIcon(Icon::load("O.svg"));
        // Apply animation is enabled
        if (Attr::get().animated) {
            squares[i]->flash();
        }
    }
}

void Board::tie() {
    end(Icon::load("Tie.svg"), "Tie!");

    // Update the statistics
    Attr::get().ties++;
}

bool Board::containsAll(const QList<int> &l1, const QList<int> &l2) {
    for (const auto &e : l2) {
        if (!l1.contains(e)) {
            return false;
        }
    }
    return true;
}
