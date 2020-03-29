#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_dialog = new Dialog();
    ui->stackedWidget->addWidget(m_dialog);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::on_dialog_selected);

    m_form = new Form();
    ui->stackedWidget->addWidget(m_form);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_form_selected);

    m_subWindow = new SubWindow();
    ui->stackedWidget->addWidget(m_subWindow);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_subWindow_selected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dialog_selected()
{
    qDebug() << "on_dialog_selected";
    ui->stackedWidget->setCurrentWidget(m_dialog);
}

void MainWindow::on_form_selected()
{
    qDebug() << "on_form_selected";
    ui->stackedWidget->setCurrentWidget(m_form);
}

void MainWindow::on_subWindow_selected()
{
    qDebug() << "on_subWindow_selected";
    ui->stackedWidget->setCurrentWidget(m_subWindow);
}
