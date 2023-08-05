#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWin;
	mainWin.resize(800, 480);
	mainWin.show();

	return app.exec();
}
