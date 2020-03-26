import QtQuick 2.4

Item {
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#4facfe"
            }

            GradientStop {
                position: 1
                color: "#00f2fe"
            }
        }
        anchors.fill: parent
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:108;anchors_y:128}
}
##^##*/
