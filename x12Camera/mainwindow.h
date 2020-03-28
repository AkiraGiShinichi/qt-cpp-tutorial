#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool setCamera(const QCameraInfo &cameraInfo);


private slots:
    void on_pushButton_takeImage_clicked();
    void on_image_captured(int id, const QImage& previewImage);
    void on_image_saved(int id, const QString &fileName);

    void displayViewfinder();
    void displayCapturedImage();

    void on_label_lastImagePreview_clicked();

    void on_pushButton_viewCapturedImage_clicked();

private:
    Ui::MainWindow *ui;

    QCamera *m_camera;
    QCameraViewfinder *m_cameraViewfinder;
    QCameraImageCapture *m_imageCapture;
};
#endif // MAINWINDOW_H
