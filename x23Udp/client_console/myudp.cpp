#include "myudp.h"

MyUdp::MyUdp(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // The most common way to use QUdpSocket class is to bind to an address and port using bind()
    socket->bind(QHostAddress::LocalHost, 1235);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUdp::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress senderHost;
    quint16 senderPort;
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port (unless the pointers are 0).
    socket->readDatagram(buffer.data(), buffer.size(), &senderHost, &senderPort);

    qDebug() << "Message from: " << senderHost.toString();
    qDebug() << "Message port: " << senderPort;
    qDebug() << "Message: " << buffer;
}

void MyUdp::helloUdp()
{
    QByteArray Data;
    Data.append("Hello from UDP client");

    // Sends the datagram datagram to the host address and at port.
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}
