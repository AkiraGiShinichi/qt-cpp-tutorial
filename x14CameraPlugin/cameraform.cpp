#include "cameraform.h"
#include "ui_cameraform.h"
#include <QTimer>
#include <QDir>

CameraForm::CameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraForm)
{
    ui->setupUi(this);

//    setCamera(QCameraInfo::defaultCamera());
}

CameraForm::~CameraForm()
{
    delete ui;
}

void CameraForm::setCamera(const QCameraInfo &cameraInfo)
{
    qDebug() << "setCamera";
    m_camera = new QCamera(cameraInfo);
    m_imageCapture = new QCameraImageCapture(m_camera);

    m_camera->setViewfinder(this->ui->viewfinder);

    connect(m_imageCapture, &QCameraImageCapture::imageCaptured, this, &CameraForm::on_image_captured);
    connect(m_imageCapture, &QCameraImageCapture::imageSaved, this, &CameraForm::on_image_saved);

    displayViewfinder();
    m_camera->start();
}

void CameraForm::on_pushButton_takePhoto_clicked()
{
    qDebug() << "on_pushButton_takePhoto_clicked";
    m_imageCapture->capture();
}

void CameraForm::on_image_captured(int id, const QImage& previewImage)
{
    qDebug() << "on_image_captured";
    Q_UNUSED(id);
    QImage scaledImage = previewImage.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->label_photoPreview->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayPhotoPreview();
    QTimer::singleShot(4000, this, &CameraForm::displayViewfinder);
}

void CameraForm::on_image_saved(int id, const QString &fileName)
{
    qDebug() << "on_image_saved";
    Q_UNUSED(id);
//    ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    qDebug() << tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName));
}

void CameraForm::displayViewfinder()
{
    qDebug() << "displayViewfinder";
    this->ui->stackedWidget->setCurrentWidget(this->ui->page_viewfinder);
}

void CameraForm::displayPhotoPreview()
{
    qDebug() << "displayPhotoPreview";
    ui->stackedWidget->setCurrentWidget(ui->page_photoPreview);
}

void CameraForm::on_label_photoPreview_clicked()
{
    qDebug() << "on_label_photoPreview_clicked";
    displayViewfinder();
}

void CameraForm::on_pushButton_preview_clicked()
{
    qDebug() << "on_pushButton_preview_clicked";
    displayPhotoPreview();
}


