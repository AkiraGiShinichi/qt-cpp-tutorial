#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_btnImage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (QString::compare(filename, QString()) != 0)
    {
        QImage image;
        bool valid = image.load(filename);
        if (valid)
        {
//            1st way
//            image = image.scaledToWidth(ui->lblImage->width(), Qt::SmoothTransformation);
//            ui->lblImage->setPixmap(QPixmap::fromImage(image));

//            2nd way
            QPixmap image(filename);
            int w = ui->lblImage->width();
            int h = ui->lblImage->height();
            ui->lblImage->setPixmap(image.scaled(w, h, Qt::KeepAspectRatio));
        }
        else
        {
            // error handling
        }
    }
}
