#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (username == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "Username & Password is correct");
        hide();
        secondDialog = new SecondDialog(this);
        secondDialog->show();
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username & Password is NOT correct");
    }
}
