#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//	a.addLibraryPath("..");
    MainWindow w;
	if (argc > 1)
		w.open(argv[1]);
    w.show();
    return a.exec();
}
