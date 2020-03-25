#include <QCoreApplication>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "calculator2.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("HELLO\n");

    Calculator2 calc(2, 3);
    qDebug() << "sum: " << calc.Sum();

    cv::Mat image = cv::imread("LG.jpg", 1);
    cv::namedWindow("My Image");
    cv::imshow("My Image", image);

    return a.exec();
}
