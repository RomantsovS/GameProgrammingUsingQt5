import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Image {
        id: image
        anchors.centerIn: parent
        source: "qrc:/qt/qml/pinch/wilanow.jpg"
    }

    PinchArea {
        anchors.fill: parent
        pinch {
            target: image
            minimumScale: 0.2
            maximumScale: 2.0
            minimumRotation: -90
            maximumRotation: 90
        }
    }
}
