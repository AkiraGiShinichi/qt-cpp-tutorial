#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString db_address = "E:/WORKSPACES/Qt/QtTutorial/x11LoginSQLite/UserData.db";
    connectDB(db_address);
}

MainWindow::~MainWindow()
{
    disconnectDB();
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();
    qDebug() << "username: " << username << "password: " << password;

    if (!m_database.open())
    {
        qDebug() << "on_pushButton_login_clicked - " << "database is not connected yet";
        return;
    }

    QSqlQuery query;
    if (query.exec("select * from users where username='" + username + "' and password='" + password + "'"))
    {
        int count=0;
        while (query.next())
        {
            count++;
        }
        if (count==1)
        {
            ui->label_status->setText("username & password are correct");
            this->hide();
            UserInfo userInfo;
            userInfo.setModal(true);
            userInfo.exec();
        }
        else if (count < 1)
        {
            ui->label_status->setText("username & password are NOT correct");
        }
        else
        {
            ui->label_status->setText("username & password are duplicated");
        }
    }
}

bool MainWindow::connectDB(const QString &address)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(address);
    if (!m_database.open())
    {
        ui->label_status->setText("Failed connecting database.");
        return false;
    }
    else
    {
        ui->label_status->setText("Connected database successfully!");
        ui->lineEdit_username->setEnabled(true);
        ui->lineEdit_password->setEnabled(true);
        return true;
    }
}

void MainWindow::disconnectDB()
{
    if (m_database.open())
    {
        m_database.close();
        m_database.removeDatabase(QSqlDatabase::defaultConnection);
    }
}
