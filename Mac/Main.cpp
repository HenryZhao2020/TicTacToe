#include "Game.h"
#include "FileUtil.h"
#include "Attr.h"

#include <QApplication>
#include <QDir>
#include <QFontDatabase>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    app.setStyleSheet(FileUtil::readAll(":/configs/Styles.qss"));
    QObject::connect(&app, &QApplication::aboutToQuit, &Attr::save);

    QDir::setCurrent(app.applicationDirPath());

    QFontDatabase::addApplicationFont(":/fonts/MontserratAlternates-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/ZCOOLKuaiLe-Regular.ttf");

    bool loaded = Attr::load();

    QTranslator baseTrans, appTrans;
    if (Attr::getSettings().lang != 0) {
        QString basePath = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
        QString code = Settings::getLangTerrCode(Attr::getSettings().lang);

        if (baseTrans.load("qtbase_" + code, basePath)) {
            app.installTranslator(&baseTrans);
        }
        if (appTrans.load(":/i18n/TTT_" + code)) {
            app.installTranslator(&appTrans);
        }
    }

    Game game;
    game.show();

    if (loaded) {
        game.loadSave();
    }

    return app.exec();
}
