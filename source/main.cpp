#include <QtGui>
#include "gui/main_window.h"

int main( int argc, char* argv[] )
{
	QApplication app{ argc, argv };

	gui::MainWindow mw{};
	mw.show();

	return app.exec();
}
