import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Window {
    id : cameraUI
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property int margin: 10

    VideoOutput {
        source: camera
        focus : visible // to receive focus and capture key events when visible
        anchors.fill: parent

        Camera {
            id: camera
        }

        MouseArea {
            anchors.fill: parent;
            onClicked:
            {
                camera.imageCapture.capture();
                console("captured");
            }
        }
    }

    Button {
        id: btnClose
        text: "Close"
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    Button {
        id: btnSnap
        text: "Snap"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Connections {
        target: btnSnap
        onClicked: camera.imageCapture.capture()
    }

    Connections {
        target: btnClose
        onClicked: Qt.quit()
    }
}
