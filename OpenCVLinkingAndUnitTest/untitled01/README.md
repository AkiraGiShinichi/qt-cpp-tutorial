# Include OpenCV

## How to simply use OpenCV in Qt:
 - Download OpenCV of mingw:  https://github.com/huihut/OpenCV-MinGW-Build
 - Add IncludePath and Libs to *.pro file like below:
```
INCLUDEPATH += E:\Windows\Programs\OpenCV\OpenCV-MinGW\include
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_core411.dll
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_highgui411.dll
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_imgcodecs411.dll
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_imgproc411.dll
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_features2d411.dll
LIBS += E:\Windows\Programs\OpenCV\OpenCV-MinGW\x64\mingw\bin/libopencv_calib3d411.dll
```
 - **Copy those *.dll files from lib into built folder(folder of *.exe file) of Qt**, such as: 
 - Sample codes:
```C++
#include <QCoreApplication>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug("HELLO\n");

    cv::Mat image = cv::imread("LG.jpg", 1);
    cv::namedWindow("My Image");
    cv::imshow("My Image", image);

    return a.exec();
}
```



## How to build your own OpenCV for Qt:
**Source article**: https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows