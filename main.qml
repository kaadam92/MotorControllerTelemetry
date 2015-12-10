import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import CustomPlot 1.0


ApplicationWindow {
    title: qsTr("Elektromos jármű diagnoszikai szoftver")
    width: 1360
    height: 768
    visible: true


    objectName: "ApplicationWindow"
    id: rootwindow

    signal connectCommandCpp()
    signal hvEnableCommandCpp()
    signal driveEnableCommandCpp()
    signal stopCommandCpp()
    signal testCommandCpp()
    signal vdemandSliderChanged(var vdemand)


    menuBar: MenuBar {

        Menu {

            title: qsTr("&All")

            MenuItem {
                text: qsTr("Settings")

            }
            MenuItem {
                text: qsTr("E&xit")

                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        id: mainFormControl
        anchors.fill: parent

        onConnectCommand: {
            connectCommandCpp();
        }

        onHvEnableCommand: {
            hvEnableCommandCpp();
        }

        onDriveEnableCommand: {
            driveEnableCommandCpp();
        }

        onTestCommand: {
            testCommandCpp();
        }

        onStopCommand: {
            stopCommandCpp();
        }
    }
}
