import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import io.qt.Backend 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Backend {
        id: backend

        onStatusChanged: {
            textArea_log.append(newStatus)
        }
        onSomeMessage: {
            textArea_log.append(msg)
        }
        onSomeError: {
            textArea_log.append("Error! " + err)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Rectangle {
            height: status.height + 10
            Layout.fillWidth: true
            Layout.margins: 10
            color: "#F4F2F5"
            border.color: "gray"

            Text {
                id: status
                text: backend.currentStatus ? "CONNECTED" : "DISCONNECTED"
                anchors.centerIn: parent
                font.weight: Font.Bold
            }
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: button_connect
                text: "Connect to Server"
                padding: 10
                onClicked: {
                    textArea_log.append("Connecting to server...")
                    backend.connectClicked();
                }
            }

            Button {
                id: button_disconnect
                text: "Disconnect from Server"
                padding: 10
                onClicked: {
                    textArea_log.append("Disconnecting from server...")
                    backend.disconnectClicked();
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 10
            color: "#F4F2F5"
            border.color: "gray"

            ScrollView {
                id: scrollView
                anchors.fill: parent

                TextArea {
                    id: textArea_log
                    readOnly: true
                    selectByMouse: true
                    font.pixelSize: 14
                    wrapMode: TextInput.WrapAnywhere
                }
            }
        }

        RowLayout {
            Layout.margins: 10

            Rectangle {
                Layout.fillWidth: true
                height: button_send.height
                color: "#F4F2F5"
                border.color: "gray"

                TextInput {
                    id: textInput_msg
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    font.pixelSize: 14
                    padding: 10
                }
            }

            Button {
                id: button_send
                text: "Send"
                onClicked: {
                    textArea_log.append("Sending message...")
                    backend.sendClicked(textInput_msg.text);
                }
            }
        }
    }

    Component.onCompleted: {
        textArea_log.text = "Application started\n- - - - - - - - - - - - -"
    }
}
