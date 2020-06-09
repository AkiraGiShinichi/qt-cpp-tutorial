#include <QCoreApplication>
#include "myudp.h"
#include <QNetworkInterface>
#include <QDebug>
#include <QThread>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Hello";

//    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
//    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
//        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
//             qDebug() << address.toString();
//    }

    MyUdp client;
//    client.helloUdp();
//    qDebug() << "hello allready";
    for (int i=0; i<10; i++){
        client.sendTo("192.168.240.122", 30444, "Bind");
        Sleeper::msleep(500);
    }
    client.sendTo("192.168.240.122", 30444, "k");
    Sleeper::msleep(100);
//    client.sendTo("192.168.240.122", 30444, "X");
    Sleeper::msleep(500);
    client.sendTo("192.168.240.122", 30444, "M");
    Sleeper::msleep(500);

    return a.exec();
}
