#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void MyTcpServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->write("Hello Client\n");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}
