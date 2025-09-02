import QtQuick

Rectangle {
    id: button
    property color topColor: "#eeeeee"
    property color bottomColor: "#777777"
    property color textColor: "black"
    property color textPressedColor: "white"
    property alias pressed: buttonMouseArea.pressed
    signal clicked
    border {
        width: 1
        color: "black"
    }
    radius: 5
    gradient: Gradient {
        GradientStop {
            position: 0
            color: button.topColor
        }
        GradientStop {
            position: 1
            color: button.bottomColor
        }
    }
    clip: true
    implicitWidth: Math.max(buttonContent.implicitWidth + 8, 80)
    implicitHeight: buttonContent.implicitHeight + 8
    Row {
        id: buttonContent
        anchors.centerIn: parent
        spacing: 4
        anchors.verticalCenterOffset: buttonMouseArea.pressed ? 1 : 0
        anchors.horizontalCenterOffset: buttonMouseArea.pressed ? 1 : 0
        Image {
            id: buttonIcon
            source: "qrc:/qt/qml/custom_button/edit-undo.png"
        }
        Text {
            id: buttonText
            text: "ButtonText"
            color: buttonMouseArea.pressed ? button.textPressedColor : button.textColor
        }
    }
    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton
        onClicked: {
            console.log(mouse.button)
            switch (mouse.button) {
            case Qt.LeftButton:
                console.log("Left button clicked")
                break
            case Qt.MiddleButton:
                console.log("Middle button clicked")
                break
            case Qt.RightButton:
                console.log("Right button clicked")
                break
            }
        }
        onPositionChanged: {
            console.log("Position: [" + mouse.x + "; " + mouse.y + "]")
        }
    }
}
