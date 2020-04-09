#include "serverstuff.h"
#include <QDataStream>

ServerStuff::ServerStuff(QObject *parent) : QObject(parent), NextBlockSize(0)
{
    tcpServer = new QTcpServer(this);
}

void ServerStuff::newConnection()
{
    qDebug() << " - newConnection";

    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerStuff::gotDisconnection);

    tcpClients << clientSocket; // Add new connected client into client list
    sendToClient(clientSocket, "Reply: connection established"); // Notify client that connection is already established
}
void ServerStuff::readClient()
{
    qDebug() << " - readClient";

    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    QDataStream in(clientSocket);
    for (;;)
    {
        if (!NextBlockSize)
        {
            if (clientSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> NextBlockSize;
        }

        if (clientSocket->bytesAvailable() < NextBlockSize)
            break;

        QString str;
        in >> str;

        emit gotNewMessage(str);
        NextBlockSize = 0;

        if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(str)) == -1)
        {
            qDebug() << "readClient" << " - " << "Some error occured";
        }
    }
}
void ServerStuff::gotDisconnection()
{
    qDebug() << " - gotDisconnection";

    tcpClients.removeAt(tcpClients.indexOf((QTcpSocket*)sender()));
    emit smbDisconnected();
}
qint64 ServerStuff::sendToClient(QTcpSocket *socket, const QString &str)
{
    qDebug() << " - sendToClient";

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}
QList<QTcpSocket *> ServerStuff::getClients()
{
    return tcpClients;
}


