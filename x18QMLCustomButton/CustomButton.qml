import QtQuick 2.0

Rectangle {
    id: button
    height: text.height + 20
    width: text.width + 20
    color: "red"

    signal buttonClicked()

    Text {
        id: text
        text: "Button"
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: buttonClicked()
    }
}
