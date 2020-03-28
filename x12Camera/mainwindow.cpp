#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCamera(QCameraInfo::defaultCamera());
    displayViewfinder();
    connect(ui->label_lastImagePreview , SIGNAL(clicked()), this, SLOT(on_label_lastImagePreview_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera = new QCamera(cameraInfo);
    m_imageCapture = new QCameraImageCapture(m_camera);

//    1st way to display CameraViewfinder: through QLabel
//    m_cameraViewfinder = new QCameraViewfinder(this->ui->label_viewfinder);
//    m_cameraViewfinder->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
//    m_camera->setViewfinder(m_cameraViewfinder);
//    this->setCentralWidget(m_cameraViewfinder);

//    2nd way to display CameraViewfinder: through customwidgets QWidget for QCameraViewfinder
    m_camera->setViewfinder(this->ui->viewfinder);

    connect(m_imageCapture, &QCameraImageCapture::imageCaptured, this, &MainWindow::on_image_captured);
    connect(m_imageCapture, &QCameraImageCapture::imageSaved, this, &MainWindow::on_image_saved);

    m_camera->start();
}

void MainWindow::on_pushButton_takeImage_clicked()
{
    m_imageCapture->capture();
}

void MainWindow::on_image_captured(int id, const QImage& previewImage)
{
    Q_UNUSED(id);
    QImage scaledImage = previewImage.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->label_lastImagePreview->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, &MainWindow::displayViewfinder);
}

void MainWindow::on_image_saved(int id, const QString &fileName)
{
    Q_UNUSED(id);
//    ui->statusbar->showMessage("");
    ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));
}

void MainWindow::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_label_lastImagePreview_clicked()
{
//    QTimer::singleShot(1, this, &MainWindow::displayViewfinder);
    displayViewfinder();
    qDebug() << "on_label_lastImagePreview_clicked"; // why this event happens 2 times??
}

void MainWindow::on_pushButton_viewCapturedImage_clicked()
{
    displayCapturedImage();
}
