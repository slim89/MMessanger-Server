#include <QtGui/QApplication>
#include "mainwindow.h"
#include "QPointer"
#include "chatwindow.h"

QString globalbuff [2][50];
int socketSender =-1;
QString ourNick;
//int nextmessage=0;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
