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

void receivedMessage(quint32, QByteArray message) {
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
    QDir::setCurrent("Res");

    QFontDatabase::addApplicationFont("Ubuntu_Bold.ttf");

    app.setStyle("Fusion");
    app.setStyleSheet(File::readAll("Styles.qss"));
    WinAPI::detectModeChange();
    WinAPI::detectDpiChange();
    QObject::connect(&app, &QApplication::aboutToQuit, &app, &Attr::save);
    QObject::connect(&app, &SingleApplication::receivedMessage,
                     &app, &receivedMessage);

    game = new Game();
    game->restore();
    game->show();

    return app.exec();
}