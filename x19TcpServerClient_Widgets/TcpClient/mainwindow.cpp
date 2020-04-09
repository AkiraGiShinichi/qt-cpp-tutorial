#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_disconnectFromServer->setEnabled(false);
    client = new ClientStuff("localhost", 6547);
    setStatus(client->getStatus());
    connect(client, &ClientStuff::statusChanged, this, &MainWindow::setStatus);
    connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(gotError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
}

void MainWindow::setStatus(bool newStatus)
{
    qDebug() << " * MainWindow::setStatus";

    if (newStatus)
    {
        ui->label_status->setText(tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connectToServer->setEnabled(false);
        ui->pushButton_disconnectFromServer->setEnabled(true);
    }
    else
    {
        ui->label_status->setText(tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->pushButton_connectToServer->setEnabled(true);
        ui->pushButton_disconnectFromServer->setEnabled(false);
    }
}
void MainWindow::receivedSomething(QString msg)
{
    qDebug() << " * MainWindow::receivedSomething";

    ui->textEdit_log->append(msg);
}
void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    qDebug() << " * MainWindow::SocketError";

    QString strError = "unknown";
    switch (err) { // Q: Where to check SocketError?
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

    ui->textEdit_log->append(strError);
}

void MainWindow::on_pushButton_connectToServer_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_connectToServer_clicked";

    client->connectToHost();
}

void MainWindow::on_pushButton_disconnectFromServer_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_disconnectFromServer_clicked";

    client->closeConnection();
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_sendMessage_clicked";

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out << quint16(0) << ui->lineEdit_message->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}
