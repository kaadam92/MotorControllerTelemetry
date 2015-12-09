import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2


GroupBox{
    height:486
    width: 800

    property var cellmax: 4200
    property var cellv1: 3860
    property var cellv2: 3520
    property var cellv3: 3421
    property var cellv4: 2410
    property var cellv5: 2731
    property var cellv6: 4194
    property var cellv7: 2945
    property var cellv8: 3421
    property var cellv9: 3421
    property var cellv10: 3421
    property var cellv11: 3421
    property var cellv12: 3421

    Column {
        id: column1
        width: 800
        height: 478

        BatteryBar{
            id: cell1
            anchors.left: parent
            anchors.right: parent

            cellname: "Cell1"
            cellvoltage: cellv1
            cellvoltagemax: cellmax



        }
        BatteryBar{
            id: cell2

            cellname: "Cell2"
            cellvoltage: cellv2
            cellvoltagemax: cellmax
        }
        BatteryBar{
            id: cell3

            cellname: "Cell3"
            cellvoltage: cellv3
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell4

            cellname: "Cell4"
            cellvoltage: cellv4
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell5

            cellname: "Cell5"
            cellvoltage: cellv5
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell6

            cellname: "Cell6"
            cellvoltage: cellv6
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell7

            cellname: "Cell7"
            cellvoltage: cellv7
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell8

            cellname: "Cell8"
            cellvoltage: cellv8
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell9

            cellname: "Cell9"
            cellvoltage: cellv9
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell10

            cellname: "Cell10"
            cellvoltage: cellv10
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell11

            cellname: "Cell11"
            cellvoltage: cellv11
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cell12

            cellname: "Cell12"
            cellvoltage: cellv12
            cellvoltagemax: cellmax

        }

    }

}

