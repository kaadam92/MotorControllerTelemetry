import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import CustomPlot 1.0

RowLayout {

    property color selectedColor: "grey"

    function selectColor(messageText, color)
    {
        selectedColor = color;
        eventLogModel.append( { message: messageText, colorCode: color } );
        console.log("selectColor(" + messageText + ", " + color + ")");
    }

    ScrollView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.minimumWidth: 100
        Layout.minimumHeight: 150
        Layout.preferredHeight: 150

        ListView {
            id: stateHistoryList
            anchors.rightMargin: 10
            anchors.bottomMargin: 0
            anchors.leftMargin: 10
            anchors.topMargin: 0

            ListView {
                id: eventLog
                anchors.fill: parent
                anchors.margins: 5
                delegate: GroupBox {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    Row {
                        id: row2
                        Rectangle {
                            width: 20
                            height: 20
                            radius: 10
                            color: colorCode
                        }


                        Text {
                            text: message
                            anchors.verticalCenter: parent.verticalCenter
                            font.bold: false
                        }
                        spacing: 5
                    }
                }
                model: ListModel {
                    id: eventLogModel
                    ListElement {
                        message: "Indul a program..."
                        colorCode: "grey"
                    }
                }

                onCountChanged: {
                    incrementCurrentIndex();
                    incrementCurrentIndex();
                    incrementCurrentIndex();
                    incrementCurrentIndex();
                }
            }
        }
    }
}
