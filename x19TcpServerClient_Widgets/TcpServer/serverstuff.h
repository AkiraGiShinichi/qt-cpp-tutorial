#ifndef SERVERSTUFF_H
#define SERVERSTUFF_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerStuff : public QObject
{
    Q_OBJECT
public:
    explicit ServerStuff(QObject *parent = nullptr);

public slots:
    virtual void newConnection(); // Q: What "virtual" means? and When to use?
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QString &str);

signals:
    void gotNewMessage(QString msg);
    void smbDisconnected();

public:
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();

private:
    quint16 NextBlockSize;
    QList<QTcpSocket *> tcpClients;

};

#endif // SERVERSTUFF_H
