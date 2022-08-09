#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    QIcon icon(":/themes/themes/appicon.ico");
    MainWindow w;
    w.setWindowIcon(icon);
    w.show();
    QFile ssfile(":/themes/themes/Diffnes.qss");
    ssfile.open(QFile::ReadOnly);
    QString sts = QLatin1String(ssfile.readAll());
    prog.setStyleSheet(sts);
    return prog.exec();
}
