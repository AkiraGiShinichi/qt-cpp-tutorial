#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientstuff.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setStatus(bool newStatus);
    void receivedSomething(QString msg);
    void gotError(QAbstractSocket::SocketError err);

private slots:
    void on_pushButton_connectToServer_clicked();

    void on_pushButton_disconnectFromServer_clicked();

    void on_pushButton_sendMessage_clicked();

private:
    Ui::MainWindow *ui;

    ClientStuff *client;
};
#endif // MAINWINDOW_H
