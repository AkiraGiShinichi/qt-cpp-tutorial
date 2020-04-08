#include <QCoreApplication>
#include <QDebug>

#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "HELLO";

    qDebug() << "Initialize Server";
    MyTcpServer server;

    return a.exec();
}
