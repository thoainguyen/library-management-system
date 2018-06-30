#include "mainwindow/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *m = new MainWindow();
    m->setWindowTitle("LIBPRO");
    m->show();
    return a.exec();
}
