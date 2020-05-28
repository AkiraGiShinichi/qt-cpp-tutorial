#include <QCoreApplication>
#include "myudp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyUdp client;
    client.helloUdp();
    qDebug() << "hello allready";

    return a.exec();
}
