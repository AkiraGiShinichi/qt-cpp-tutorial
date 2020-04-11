#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "clientstuff.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool currentStatus READ getStatus NOTIFY statusChanged)
public:
    explicit Backend(QObject *parent = nullptr);
    bool getStatus();

signals:
    void statusChanged(QString newStatus);
    void someMessage(QString msg);
    void someError(QString err);

public slots:
    void setStatus(bool newStatus);
    void receivedSomething(QString msg);
    void gotError(QAbstractSocket::SocketError err);
    void connectClicked();
    void disconnectClicked();
    void sendClicked(QString msg);

private:
    ClientStuff *client;
};

#endif // BACKEND_H
