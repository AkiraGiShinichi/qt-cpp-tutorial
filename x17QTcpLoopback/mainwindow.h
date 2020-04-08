#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
    // start button
    void startListening();
    // request button
    void requestConnection();
    // server accepts a request from a client
    void acceptConnection();
    // client starts sending at the acceptance of a connection request
    void clientSendMessageToServer();
    // slot for server progress bar
    void updateServerProgress();
    // slot for client progress bar
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);

private slots:
    void on_pushButton_startListening_clicked();

    void on_pushButton_requestConnection_clicked();

    void on_pushButton_quit_clicked();

private:
    Ui::MainWindow *ui;

    QTcpServer tcpServer;
    QTcpSocket tcpClient;
    QTcpSocket *tcpServerConnection;

    int bytesToWrite;
    int bytesWritten;
    int bytesReceived;

};
#endif // MAINWINDOW_H
