
#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"
#include <QThread>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

    QPixmap pixmap(":/res/images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loaded Resource ..");
    Q_INIT_RESOURCE(SpriteAltasPacker);

    a.processEvents();

    splash.showMessage("Start Window ..");

    MainWindow w;
    w.show();

    splash.finish(&w);
    int r = a.exec();

    Q_CLEANUP_RESOURCE(SpriteAltasPacker);
	return r;
}
