import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2


GroupBox{
    height:486
    width: 800

    property var cellmax: 4200


    Column {
        id: column1
        width: 800
        height: 478

        BatteryBar{
            id: cellid1
            anchors.left: parent
            anchors.right: parent

            cellname: "Cell1"
            cellvoltage: cell1.data
            cellvoltagemax: cellmax
        }
        BatteryBar{
            id: cellid2
            cellname: "Cell2"
            cellvoltage: cell2.data
            cellvoltagemax: cellmax
        }
        BatteryBar{
            id: cellid3

            cellname: "Cell3"
            cellvoltage: cell3.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid4

            cellname: "Cell4"
            cellvoltage: cell4.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid5

            cellname: "Cell5"
            cellvoltage: cell5.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid6

            cellname: "Cell6"
            cellvoltage: cell6.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid7

            cellname: "Cell7"
            cellvoltage: cell7.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid8

            cellname: "Cell8"
            cellvoltage: cell8.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid9

            cellname: "Cell9"
            cellvoltage: cell9.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid10

            cellname: "Cell10"
            cellvoltage: cell10.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid11

            cellname: "Cell11"
            cellvoltage: cell11.data
            cellvoltagemax: cellmax

        }
        BatteryBar{
            id: cellid12

            cellname: "Cell12"
            cellvoltage: cell12.data
            cellvoltagemax: cellmax

        }

    }

}

