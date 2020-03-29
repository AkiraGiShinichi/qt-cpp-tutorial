#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_cameraForm = new CameraForm();
    ui->stackedWidget->addWidget(m_cameraForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionCamera_triggered()
{
    qDebug() << "on_actionCamera_triggered" << " - selected cameraForm";
    m_cameraForm->setCamera(QCameraInfo::defaultCamera()); // initialize camera before showing out
    ui->stackedWidget->setCurrentWidget(m_cameraForm);
}
