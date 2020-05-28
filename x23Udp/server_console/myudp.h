#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class myudp : public QObject
{
    Q_OBJECT
public:
    explicit myudp(QObject *parent = nullptr);
    void helloUdp();

signals:

public slots:
    void readyRead();

private:
    QUdpSocket *socket;

};

#endif // MYUDP_H
