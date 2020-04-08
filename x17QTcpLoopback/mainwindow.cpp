#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

static const int TotalBytes = 50 * 1024 * 1024;
static const int PayloadSize = 64 * 1024;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // request button - initially disabled
    ui->pushButton_requestConnection->setEnabled(false);

    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(&tcpClient, SIGNAL(connected()), this, SLOT(clientSendMessageToServer()));
    connect(&tcpClient, SIGNAL(bytesWritten(qint64)), this, SLOT(updateClientProgress(qint64)));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// start button
void MainWindow::on_pushButton_startListening_clicked()
{
    qDebug() << "on_pushButton_startListening_clicked";

    startListening();
}
void MainWindow::startListening()
{
    qDebug() << "startListening";

    ui->pushButton_startListening->setEnabled(false);

    bytesWritten = 0;
    bytesReceived = 0;

    while (!tcpServer.isListening() && !tcpServer.listen())
    {
        QMessageBox::StandardButton ret = QMessageBox::critical(this,
                                                                tr("Loopback"),
                                                                tr("Unable to start the test: %1.").arg(tcpServer.errorString()),
                                                                QMessageBox::Retry | QMessageBox::Cancel);
        if (ret == QMessageBox::Cancel) return;
    }

    ui->label_serverStatus->setText(tr("Listening...")); // Q: What is "tr(...)"?(difference with normal string?)
    ui->pushButton_requestConnection->setEnabled(true);
}
// request button
void MainWindow::on_pushButton_requestConnection_clicked()
{
    qDebug() << "on_pushButton_requestConnection_clicked";

    requestConnection();
}
void MainWindow::requestConnection()
{
    qDebug() << "requestConnection";

    ui->pushButton_requestConnection->setEnabled(false);
    ui->label_clientStatus->setText(tr("Connecting.."));
    tcpClient.connectToHost(QHostAddress::LocalHost, tcpServer.serverPort());
}
// server accepts a request from a client
void MainWindow::acceptConnection()
{
    qDebug() << "acceptConnection";

    tcpServerConnection = tcpServer.nextPendingConnection();

    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(updateServerProgress()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->label_serverStatus->setText(tr("Accepted connection."));
    tcpServer.close();
}
// client starts sending at the acceptance of a connection request
void MainWindow::clientSendMessageToServer()
{
    qDebug() << "clientSendMessageToServer";

    bytesToWrite = TotalBytes - (int)tcpClient.write(QByteArray(PayloadSize, '@')); // Q: What is new style cast?
    ui->label_clientStatus->setText(tr("Connected"));
}
// slot for server progress bar
void MainWindow::updateServerProgress()
{
    qDebug() << "updateServerProgress";

    bytesReceived += (int)tcpServerConnection->bytesAvailable();
    tcpServerConnection->readAll();

    ui->progressBar_server->setMaximum(TotalBytes);
    ui->progressBar_server->setValue(bytesReceived);
    ui->label_serverStatus->setText(tr("Received %1MB").arg(bytesReceived / (1024 * 1024)));

    if (bytesReceived == TotalBytes)
    {
        tcpServerConnection->close();
        ui->pushButton_startListening->setEnabled(true);
#ifndef QT_NO_CURSOR
        qDebug() << "|QT_NO_CURSOR| - updateServerProgress";
        QApplication::restoreOverrideCursor(); // Q: What is "restoreOverrideCursor" for?
#endif
    }
}
// slot for client progress bar
void MainWindow::updateClientProgress(qint64 numBytes)
{
    qDebug() << "updateClientProgress";

    bytesWritten += (int)numBytes;

    if (bytesToWrite > 0 && tcpClient.bytesToWrite() <= 4 * PayloadSize)
    {
        bytesToWrite -= (int)tcpClient.write(QByteArray(qMin(bytesToWrite, PayloadSize), '@'));
    }

    ui->progressBar_client->setMaximum(TotalBytes);
    ui->progressBar_client->setValue(bytesWritten);
    ui->label_clientStatus->setText(tr("Sent %1MB").arg(bytesWritten / (1024 * 1024)));
}
void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "displayError";

    if (socketError == QTcpSocket::RemoteHostClosedError)
    {
        qDebug() << "displayError" << " - " << "socketError == QTcpSocket::RemoteHostClosedError";
        return;
    }

    QMessageBox::information(this, tr("Network Error"), tr("The following error occurred: %1.").arg(tcpClient.errorString()));

    tcpClient.close();
    tcpServer.close();

    ui->progressBar_client->reset();
    ui->progressBar_server->reset();
    ui->label_clientStatus->setText("Client Status");
    ui->label_serverStatus->setText("Server Status");
    ui->pushButton_startListening->setEnabled(true);
    ui->pushButton_requestConnection->setEnabled(false);
#ifndef QT_NO_CURSOR
    qDebug() << "|QT_NO_CURSOR| - displayError";
    QApplication::restoreOverrideCursor();
#endif
}

void MainWindow::on_pushButton_quit_clicked()
{
    close();
}
