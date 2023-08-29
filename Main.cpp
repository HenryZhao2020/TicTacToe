#include "PCH.h"
#include "Game.h"
#include "Attr.h"

Game *game;

void raiseWidget(QWidget *widget) {
    HWND hwnd = (HWND) widget->winId();
    if (IsIconic(hwnd)) {
        ShowWindow(hwnd, SW_RESTORE);
    }
    SetForegroundWindow(hwnd);
}

void receivedMessage(quint32 instanceId, QByteArray message) {
    if (message == "Raise") {
        raiseWidget(game);
    }
}

int main(int argc, char *argv[]) {
    SingleApplication app(argc, argv, true);

    if (app.isSecondary()) {
        AllowSetForegroundWindow(DWORD(app.primaryPid()));
        app.sendMessage("Raise");
        return 0;
    }

    QDir::setCurrent(QApplication::applicationDirPath());
    QFontDatabase::addApplicationFont("Fonts/Ubuntu_Bold.ttf");
    QDir::setCurrent("TicTacToe_Files");

    app.setStyle("Fusion");
    app.setStyleSheet(File::readAll("Styles.qss"));
    QObject::connect(&app, &SingleApplication::aboutToQuit, &Attr::save);
    QObject::connect(&app, &SingleApplication::receivedMessage, &receivedMessage);

    game = new Game();
    game->restore();
    game->show();

    return app.exec();
}
