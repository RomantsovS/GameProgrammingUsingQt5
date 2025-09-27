import QtQuick

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    property int dayLength: 10000 // 1 minute

    Image {
        id: sky
        source: "images/sky.png"
        anchors.fill: parent

        Image {
            source: "images/trees.png"
            x: -200
            anchors.bottom: parent.bottom
        }
        Image {
            source: "images/grass.png"
            anchors.bottom: parent.bottom
        }

        Item {
            id: sun
            x: 140
            y: root.height - 170
            Rectangle {
                id: sunVisual
                width: 40
                height: width
                radius: width / 2
                color: "yellow"
                anchors.centerIn: parent

                SequentialAnimation on color {
                    ColorAnimation {
                        from: "red"
                        to: "yellow"
                        duration: 0.2 * dayLength / 2
                    }
                    PauseAnimation {
                        duration: 2 * 0.8 * dayLength / 2
                    }
                    ColorAnimation {
                        to: "red"
                        duration: 0.2 * dayLength / 2
                    }
                    running: true
                }

                SequentialAnimation on scale {
                    NumberAnimation {
                        from: 1.6
                        to: 0.8
                        duration: dayLength / 2
                        easing.type: Easing.OutCubic
                    }
                    NumberAnimation {
                        from: 0.8
                        to: 1.6
                        duration: dayLength / 2
                        easing.type: Easing.InCubic
                    }
                }
            }
            Item {
                id: sunRays
                property int count: 10
                width: sunVisual.width
                height: width
                anchors.centerIn: parent
                x: 140
                y: root.height - 170
                z: -1
                Repeater {
                    model: sunRays.count
                    Rectangle {
                        color: "red"
                        rotation: index * 360 / sunRays.count
                        anchors.fill: parent
                    }
                }
            }
        }

        NumberAnimation {
            targets: [sun]
            property: "x"
            from: 0
            to: root.width
            duration: root.dayLength
            running: true
        }
        SequentialAnimation {
            running: true
            NumberAnimation {
                target: sun
                property: "y"
                from: root.height + sunVisual.height
                to: root.height - 270
                duration: dayLength / 2
                easing.type: Easing.OutCubic
            }
            NumberAnimation {
                target: sun
                property: "y"
                to: root.height + sunVisual.height
                duration: dayLength / 2
                easing.type: Easing.InCubic
            }
        }
    }
}
