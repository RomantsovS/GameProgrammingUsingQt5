import QtQuick

Item {
    property real factor: 0
    x: factor > 0 ? -parent.currentPos/factor - parent.x : 0
}
