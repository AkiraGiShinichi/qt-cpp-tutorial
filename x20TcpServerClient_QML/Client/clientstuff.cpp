#include "clientstuff.h"
#include <QDebug>
#include <QDataStream>

ClientStuff::ClientStuff(const QString hostAddress,
                         int portNum,
                         QObject *parent) : QObject(parent), NextBlockSize(0)
{
    status = false;
    host = hostAddress;
    port = portNum;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);
}

void ClientStuff::closeConnection()
{
    qDebug() << " - closeConnection";

    timeoutTimer->stop();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state()) { // Q: What are "tcpSocket.state()"?
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
void ClientStuff::connectToHost()
{
    qDebug() << " - connectToHost";

    timeoutTimer->start(3000);
    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

void ClientStuff::readyRead()
{
    qDebug() << " - readyRead";

    QDataStream in(tcpSocket);
    for (;;)
    {
        if (!NextBlockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> NextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < NextBlockSize)
            break;

        QString str;
        in >> str;
        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        NextBlockSize = 0;
    }
}
void ClientStuff::connected()
{
    qDebug() << " - connected";

    status = true;
    emit statusChanged(status);
}
void ClientStuff::connectionTimeout()
{
    qDebug() << " - connectionTimeout";

    if (tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

bool ClientStuff::getStatus()
{
    qDebug() << " - getStatus";

    return status;
}
