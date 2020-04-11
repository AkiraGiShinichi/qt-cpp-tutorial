#ifndef CLIENTSTUFF_H
#define CLIENTSTUFF_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>

class ClientStuff : public QObject
{
    Q_OBJECT
public:
    explicit ClientStuff(const QString hostAddress, int portNum, QObject *parent = nullptr);

public slots:
    void closeConnection();
    void connectToHost();

private slots:
    void readyRead();
    void connected();
    void connectionTimeout();

signals:
    void statusChanged(bool);
    void hasReadSome(QString msg);

public:
    QTcpSocket *tcpSocket;
    bool getStatus();

private:
    QString host;
    int port;
    bool status;
    quint16 NextBlockSize;
    QTimer *timeoutTimer;
};

#endif // CLIENTSTUFF_H
