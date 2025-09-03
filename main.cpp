#include <memory>

#include <QApplication>
#include <QFile>
#include <QFontDatabase>

#include "TextGame.h"
#include "QtGame.h"

std::unique_ptr<TicTacToe> newTextGame() {
    return std::make_unique<TextGame>(3, AutoSave::On);
}

std::unique_ptr<TicTacToe> newQtGame() {
    if (QFile styleSheet{":/conf/Styles.qss"};
        styleSheet.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(styleSheet.readAll());
    }
    QApplication::setStyle("Fusion");
    QFontDatabase::addApplicationFont(":/fonts/Montserrat-Variable.ttf");

    return std::make_unique<QtGame>(3, AutoSave::On);
}

int main(int argc, char *argv[]) {
    QApplication app{argc, argv};
    const auto ttt = newQtGame();
    ttt->play();
    return QApplication::exec();
}
