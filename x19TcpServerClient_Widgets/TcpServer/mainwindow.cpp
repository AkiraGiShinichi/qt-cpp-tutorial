#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_server = new ServerStuff(this);
    connect(m_server, &ServerStuff::gotNewMessage, this, &MainWindow::gotNewMessage);
    connect(m_server->tcpServer, &QTcpServer::newConnection, this, &MainWindow::smbConnectedToServer);
    connect(m_server, &ServerStuff::smbDisconnected, this, &MainWindow::smbDisconnectedFromServer);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_startServer_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_startServer_clicked";

    if (!m_server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        ui->textEdit_log->append(tr("<font color=\"red\"><b>Error!</b></font>"));
        return;
    }
    connect(m_server->tcpServer, &QTcpServer::newConnection, m_server, &ServerStuff::newConnection);
    ui->textEdit_log->append(tr("<font color=\"green\"><b>Server started</b>, port is openned.</font>"));
}

void MainWindow::on_pushButton_stopServer_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_stopServer_clicked";

    if (m_server->tcpServer->isListening())
    {
        disconnect(m_server->tcpServer, &QTcpServer::newConnection, m_server, &ServerStuff::newConnection);

        QList<QTcpSocket *> clients = m_server->getClients();
        for (int i=0; i<clients.count(); i++)
        {
            m_server->sendToClient(clients.at(i), "0");
        }

        m_server->tcpServer->close();
        ui->textEdit_log->append(tr("<b>Server stopped</b>, post is closed"));
    }
    else
    {
        ui->textEdit_log->append(tr("<b>Error!</b> Server was not running"));
    }
}

void MainWindow::on_pushButton_testConnection_clicked()
{
    qDebug() << " * MainWindow::on_pushButton_testConnection_clicked";

    if (m_server->tcpServer->isListening())
    {
        ui->textEdit_log->append(QString("%1 %2")
                                 .arg("Server is listening, number of connected clients:")
                                 .arg(QString::number(m_server->getClients().count())));
    }
    else
    {
        ui->textEdit_log->append(QString("%1 %2")
                                 .arg("Server is not listening, number of connected clients:")
                                 .arg(QString::number(m_server->getClients().count())));
    }
}

void MainWindow::smbConnectedToServer()
{
    qDebug() << " * MainWindow::smbConnectedToServer";

    ui->textEdit_log->append(tr("Somebody has connected"));
}
void MainWindow::smbDisconnectedFromServer()
{
    qDebug() << " * MainWindow::smbDisconnectedFromServer";

    ui->textEdit_log->append(tr("Somebody has disconnected"));
}
void MainWindow::gotNewMessage(QString msg)
{
    qDebug() << " * MainWindow::gotNewMesssage";

    ui->textEdit_log->append(QString("New message: %1").arg(msg));
}
