import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Image {
        id: backgroundImage
        source: "qrc:/qt/qml/dashboard/dashboard.png"
        Item {
            id: leftContainer
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: -550
            width: 400
            height: width
        }
        Item {
            id: middleContainer
            property int value: carData.speed
            anchors.centerIn: parent
            width: 700
            height: width

            function calculatePosition(angle, radius) {
                if (radius === undefined) {
                    radius = width / 2 * 0.8
                }
                var a = angle * Math.PI / 180
                var px = width / 2 + radius * Math.cos(a)
                var py = width / 2 + radius * Math.sin(a)
                return Qt.point(px, py)
            }

            Repeater {
                model: 24 / 2

                Item {
                    property point pt: middleContainer.calculatePosition(
                                           120 + index * 12 * 2)
                    x: pt.x
                    y: pt.y
                    Label {
                        anchors.centerIn: parent
                        text: index * 20
                    }
                }
            }

            Repeater {
                model: 120 - 4

                Item {
                    property point pt: middleContainer.calculatePosition(
                                           120 + index * 1.2 * 2,
                                           middleContainer.width * 0.35)
                    x: pt.x
                    y: pt.y
                    Rectangle {
                        width: 2
                        height: index % 5 ? 5 : 10
                        color: "white"
                        rotation: 90 + 120 + index * 1.2 * 2
                        anchors.centerIn: parent
                        antialiasing: true
                    }
                }
            }

            Text {
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 40
                text: "SPEED\n[kph]"
                horizontalAlignment: Text.AlignHCenter
                color: "#aaa"
                font.pixelSize: 16
            }

            Needle {
                anchors.centerIn: parent
                length: parent.width * 0.35
                size: 4
                rotation: 210 + (middleContainer.value * 1.2)
                color: "yellow"
            }
        }
        Item {
            id: rightContainer
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 525
            width: 400
            height: width
        }
    }
}
