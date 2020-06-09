#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUdp : public QObject
{
    Q_OBJECT
public:
    explicit MyUdp(QObject *parent = nullptr);
    void helloUdp();
    void sendTo(QString hostAddr, quint16 port, QString cmd);

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
};

#endif // MYUDP_H
