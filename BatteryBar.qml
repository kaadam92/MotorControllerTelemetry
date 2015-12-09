import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Row{
    id: row1
    width: 300

    height: 30

    spacing: 10

    property var cellname
    property var cellvoltage
    property var cellvoltagemax

    Label {
        id: label1
        width: 51
        height: 13
        anchors.horizontalCenter: parent
        text: qsTr(cellname)
        anchors.left: parent.left
        anchors.leftMargin: 0
        font.bold: true
        font.pointSize: 12
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
    }


    Rectangle {
        id: rectangle1
        width: 180*((cellvoltage-2000)/(cellvoltagemax-2000))
        height: 25
        color: "#2fde5f"
        anchors.left: label1.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        border.width: 2
    }


    Text {
        id: text1
        text: qsTr((cellvoltage/1000).toFixed(4) + " V")
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 12
    }


}

