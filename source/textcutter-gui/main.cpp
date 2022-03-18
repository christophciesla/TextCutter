#include <QtGui>

#include "gui/main_window.h"

int main( int argc, char* argv[] )
{
    QApplication app{ argc, argv };

    QTranslator translator{};
    const bool success{translator.load(QLocale(), "textcutter-gui", "_", ":/translations")};
    if (success)
    {
        std::ignore = app.installTranslator(&translator);
    }

    app.setApplicationName(QApplication::tr("Text cutter"));

    gui::MainWindow mw{};
    mw.show();

    return app.exec();
}
