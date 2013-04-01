#include <QApplication>
#include <QtGui>
#include <QWidget>
#include <QObject>
#include <QtDebug>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow m;

    // Synliggjør or resizer MainWindow
    m.resize(800, 400);
    m.show();

    return app.exec();
}
