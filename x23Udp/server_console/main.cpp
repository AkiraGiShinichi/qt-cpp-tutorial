#include <QCoreApplication>
#include <QDebug>
#include "myudp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "HIHI";
    qWarning() << "C++ Style Warning Message";
    qDebug() << "HOHO";
    qCritical() << "C++ Style Critical Error Message";

    myudp client;
//    client.helloUdp();
//    while (1) {client.helloUdp();}

    return a.exec();
}
