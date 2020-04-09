#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serverstuff.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void smbConnectedToServer();
    void smbDisconnectedFromServer();
    void gotNewMessage(QString msg);

    void on_pushButton_startServer_clicked();

    void on_pushButton_stopServer_clicked();

    void on_pushButton_testConnection_clicked();

private:
    Ui::MainWindow *ui;

    ServerStuff *m_server;
};
#endif // MAINWINDOW_H
