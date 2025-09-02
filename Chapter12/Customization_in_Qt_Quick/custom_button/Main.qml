import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        id: button
        anchors.centerIn: parent
        onPressedChanged: {
            console.log("The button is currently " + (pressed ? "" : "not ") + "pressed")
        }
    }
}
