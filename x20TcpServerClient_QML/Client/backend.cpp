#include "backend.h"
#include <QDataStream>

Backend::Backend(QObject *parent) : QObject(parent)
{
    qDebug() << " * Backend::Backend";

    client = new ClientStuff("localhost", 6547);

    connect(client, &ClientStuff::statusChanged, this, &Backend::setStatus);
    connect(client, &ClientStuff::hasReadSome, this, &Backend::receivedSomething);
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(gotError(QAbstractSocket::SocketError)));
}

bool Backend::getStatus()
{
    qDebug() << " * Backend::getStatus";

    return client->getStatus();
}

void Backend::setStatus(bool newStatus)
{
    qDebug() << " * Backend::setStatus";

    if (newStatus) emit statusChanged("CONNECTED");
    else emit statusChanged("DISCONNECTED");
}
void Backend::receivedSomething(QString msg)
{
    qDebug() << " * Backend::receivedSomething";

    emit someMessage(msg);
}
void Backend::gotError(QAbstractSocket::SocketError err)
{
    qDebug() << " * Backend::gotError";

    QString strError = "unknown";
    switch (err) {
    case 0:
        strError = "Connection was refused";
        break;
    case 1:
        strError = "Remote host closed the connection";
        break;
    case 2:
        strError = "Host address was not found";
        break;
    case 5:
        strError = "Connection timed out";
        break;
    default:
        strError = "Unknown error";
    }
}

void Backend::connectClicked()
{
    qDebug() << " * Backend::connectClicked";

    client->connectToHost();
}
void Backend::disconnectClicked()
{
    qDebug() << " * Backend::disconnectClicked";

    client->closeConnection();
}
void Backend::sendClicked(QString msg)
{
    qDebug() << " * Backend::sendClicked";

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << msg;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    client->tcpSocket->write(arrBlock);
}
