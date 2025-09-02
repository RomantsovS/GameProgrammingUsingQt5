import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: circle
        width: 60
        height: width
        radius: width / 2
        color: "red"

        MouseArea {
            anchors.fill: parent
            drag.target: circle
        }
    }
}
