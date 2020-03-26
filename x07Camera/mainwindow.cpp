#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QMediaService>
#include <QMediaRecorder>

#include <QCameraInfo>
#include <QMediaMetaData>

#include <QMessageBox>
#include <QPalette>

#include <QtWidgets>

bool checkCameraAvailability()
{
    if (QCameraInfo::availableCameras().count() > 0)
        return true;
    else
        return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCamera(QCameraInfo::defaultCamera());
}

MainWindow::~MainWindow()
{
    m_camera->stop();
    delete ui;
}

void MainWindow::listAvailableCameras()
{
//    check camera
    qDebug() << "Check number of available Cameras: " << QCameraInfo::availableCameras().count();

//    list all camera devices into menubar
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true); // mark a black point at the begining of menu item as selected device.

        ui->menuDevices->addAction(videoDeviceAction); // add device into menubar "Devices"
    }
}

void MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera = new QCamera(cameraInfo);
    QCameraViewfinder *viewfinder = new QCameraViewfinder(this->ui->lblCamera);
    viewfinder->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_camera->setViewfinder(viewfinder);
//    setCentralWidget(viewfinder);

    m_camera->start();
}

void MainWindow::on_actionStart_Camera_triggered()
{
    m_camera->start();
}

void MainWindow::on_actionStop_Camera_triggered()
{
    m_camera->stop();
}
