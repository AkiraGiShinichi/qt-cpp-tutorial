#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("E:/Windows/Programs/SQLite/db/mydb.db");

    if (!mydb.open())
    {
        ui->label->setText("Failed to open the database.");
    }
    else
    {
        ui->label->setText("Database connected!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

