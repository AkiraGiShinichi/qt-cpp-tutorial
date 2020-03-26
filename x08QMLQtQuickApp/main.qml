import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Background {
        id: background
        anchors.fill: parent

        Sender {
            id: sender
            y: 140
            displayText: "Sender"
            buttonColor: "#0e09a1"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 50
            target: receiver
        }

        Receiver {
            id: receiver
            x: 379
            y: 140
            displayText: "Receiver"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 50
        }
    }

//    Text {
//        id: txtHello
//        text: qsTr("Hello World!")
//        anchors.centerIn: parent
//    }
}

/*##^##
Designer {
    D{i:2;anchors_x:55}D{i:1;anchors_x:76;anchors_y:55}
}
##^##*/
