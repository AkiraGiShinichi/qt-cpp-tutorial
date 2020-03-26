import QtQuick 2.0

Circle {
    id: receiverButton

    function receive(value) {
        displayText = value
        clicknotify.running = true
    }

    SequentialAnimation on buttonColor {
        id: clicknotify
        running: false


        ColorAnimation {
            from: "red"
            to: "blue"
            duration: 200
        }


        ColorAnimation {
            from: "blue"
            to: "red"
            duration: 200
        }
    }
}
