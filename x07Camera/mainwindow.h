#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionStart_Camera_triggered();

    void on_actionStop_Camera_triggered();

protected:
    void listAvailableCameras();
    void setCamera(const QCameraInfo &cameraInfo);

private:
    Ui::MainWindow *ui;

    QCamera *m_camera;
    QCameraViewfinder *m_viewfinder;
};
#endif // MAINWINDOW_H
