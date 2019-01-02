#include "mainwindow.h"
#include <QApplication> // Controla toda la aplicación

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(329,325);
    w.show();
    return a.exec();
}
