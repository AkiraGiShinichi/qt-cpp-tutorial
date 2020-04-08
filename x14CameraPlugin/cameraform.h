#ifndef CAMERAFORM_H
#define CAMERAFORM_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

namespace Ui {
class CameraForm;
}

class CameraForm : public QWidget
{
    Q_OBJECT

public:
    explicit CameraForm(QWidget *parent = nullptr);
    ~CameraForm();

    void setCamera(const QCameraInfo &cameraInfo);

private slots:
    void on_pushButton_takePhoto_clicked();
    void on_image_captured(int id, const QImage& previewImage);
    void on_image_saved(int id, const QString &fileName);

    void displayViewfinder();
    void displayPhotoPreview();

    void on_label_photoPreview_clicked();

    void on_pushButton_preview_clicked();

private:
    Ui::CameraForm *ui;

    class Impl;
    Impl *m_Impl;
};

#endif // CAMERAFORM_H
