import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Item {
    id: item1
    // property alias operationFactorial: operationFactorial
    property alias reset: reset
    property alias result: result
    property alias argument2: argument2
    property alias operationMultiply: operationMultiply
    property alias operationAdd: operationAdd
    property alias argument1: argument1

    reset.onClicked: {
        argument1.text = "0"
        argument2.text = "0"
        operationAdd.checked = true
    }

    result.text: {
        var value1 = parseFloat(argument1.text)
        var value2 = parseFloat(argument2.text)
        if (operationMultiply.checked) {
            return value1 * value2
            // } else if (operationFactorial.checked) {
            //     return advancedCalculator.factorial(value1)
        } else {
            return value1 + value2
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        TextField {
            id: argument1
            width: 167
            height: 15
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: qsTr("0")
        }

        RowLayout {
            id: rowLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            RadioButton {
                id: operationAdd
                width: 23
                height: 16
                text: qsTr("+")
                checked: true
            }

            RadioButton {
                id: operationMultiply
                width: 28
                height: 16
                text: qsTr("x")
            }
        }

        TextField {
            id: argument2
            width: 167
            height: 15
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            text: qsTr("0")
        }

        Label {
            id: equalSign
            text: qsTr("=")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Label {
            id: result
            text: qsTr("Result")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: reset
            text: qsTr("reset")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }
    }
}
