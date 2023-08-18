#include "PCH.h"
#include "Game.h"
#include "Attr.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QDir::setCurrent(QApplication::applicationDirPath());
    QFontDatabase::addApplicationFont("Fonts/Ubuntu_Bold.ttf");
    QDir::setCurrent("TicTacToe_Files");

    app.setStyle("Fusion");
    app.setStyleSheet(File::readAll("Styles.qss"));
    QObject::connect(&app, &QApplication::aboutToQuit, &app, &Attr::save);

    Game game;
    game.restore();
    game.show();

    return app.exec();
}
