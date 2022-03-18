#include <QtCore>

#include "cutter/cut_text.h"

int main( int argc, char* argv[] )
{
    QCoreApplication app{ argc, argv };

    QTranslator translator{};
    const bool success{translator.load(QLocale(), "textcutter", "_", ":/translations")};
    if (success)
    {
        std::ignore = app.installTranslator(&translator);
    }

    app.setApplicationName(QCoreApplication::tr("Text cutter"));

    //return app.exec();

    return 0;
}
