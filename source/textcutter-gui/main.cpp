#include <QtGui>

#include "gui/main_window.h"

int main( int argc, char* argv[] )
{
    QApplication app{ argc, argv };

    QTranslator qt_translator{};
    bool success{ qt_translator.load(QLocale(), "qtbase", "_",
        QLibraryInfo::location(QLibraryInfo::TranslationsPath)) };
    if (success)
    {
        std::ignore = app.installTranslator(&qt_translator);
    }

    QTranslator app_translator{};
    success = app_translator.load(QLocale(), "textcutter-gui", "_", ":/translations");
    if (success)
    {
        std::ignore = app.installTranslator(&app_translator);
    }

    app.setApplicationName(QApplication::tr("Text cutter"));

    gui::MainWindow mw{};
    mw.show();

    return app.exec();
}
