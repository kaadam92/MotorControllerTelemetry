import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import CustomPlot 1.0


Item {

    Connections
    {
        id: hvenBtnConnection
        target: hven
        ignoreUnknownSignals: true
        onDataChanged:
        {
            hvenBtn.gradcolor1 = (hven.data > 1) ? "#0c0" : "#ccc";
            hvenBtn.gradcolor2 = (hven.data > 1) ? "#0e0" : "#eee";
            hvenBtn.gradcolor3 = (hven.data > 1) ? "#0a0" : "#aaa";
            hvenBtn.gradcolor4 = (hven.data > 1) ? "#0c0" : "#ccc";
        }
    }
    Connections
    {
        id: drenBtnConnection
        target: dren
        ignoreUnknownSignals: true
        onDataChanged:
        {
            drenBtn.gradcolor1 = (dren.data > 1) ? "#0c0" : "#ccc";
            drenBtn.gradcolor2 = (dren.data > 1) ? "#0e0" : "#eee";
            drenBtn.gradcolor3 = (dren.data > 1) ? "#0a0" : "#aaa";
            drenBtn.gradcolor4 = (dren.data > 1) ? "#0c0" : "#ccc";
        }
    }
    Connections
    {
        id: stopBtnConnection
        target: stop
        ignoreUnknownSignals: true
        onDataChanged:
        {
            stopBtn.gradcolor1 = (stop.data > 1) ? "#0c0" : "#f99";
            stopBtn.gradcolor2 = (stop.data > 1) ? "#0e0" : "#f66";
            stopBtn.gradcolor3 = (stop.data > 1) ? "#0a0" : "#f66";
            stopBtn.gradcolor4 = (stop.data > 1) ? "#0c0" : "#e55";
        }
    }

    id: item1
    width: 1360
    height: 768
    anchors.fill: parent
    objectName: "MainWindow"

    property color selectedColor: "grey"

    function selectColor(messageText, color)
    {
        selectedColor = color;
        eventLogModel.append( { message: messageText, colorCode: color } );
        console.log("selectColor(" + messageText + ", " + color + ")");
    }

    // Signalok, melyek a kiadott parancsokat jelzik és a nyomógombok
    //  eseménykezelői aktiválják őket.
    signal connectCommand;
    signal hvEnableCommand;
    signal driveEnableCommand;
    signal stopCommand;
    signal testCommand;

    // A parancs nyomógombok elemcsoportja
    GroupBox {
        id: commandsGB
        title: "Parancsok"
        // Bal oldalon és fent követi a szülőt. A szélessége fix.
        anchors.left : parent.left
        anchors.top : parent.top
        width: 250
        height: 500

        // A nyomógombokat oszlopba rendezzük
        ColumnLayout {
            id: columnLayout1
            anchors.bottomMargin: 0
            // Az oszlop kitölti a szülőt, vagyis a commandsGB-t.
            anchors.fill: parent

            // Reset nyomógomb. Oldal irányba kitöltik a szülőt, 0 pixel margó kihagyásával.
            //  Megnyomása esetén (Button.Clicked signal) meghívja a resetCommand signalt. (Ez
            //  a signal látható innen, mivel a Button egyik ősében definiáltuk.)
            RowLayout{
                anchors.fill: parent
                anchors.topMargin: 10
            Button {
                id: connectBtn
                objectName: "connectBtnObj"
                anchors.left: parent.left
                height: 210
                width: columnLayout1.width/2
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 50
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                        }
                    }
                }
                text: qsTr("Connect")
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                onClicked: connectCommand()
            }
            Button {
                id: selfTestBtn
                objectName: "connectBtnObj"
                anchors.right: parent.right
                height: 210
                width: columnLayout1.width/2
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 50
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                            GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                        }
                    }
                }
                text: qsTr("Test")
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                onClicked: testCommand()
            }
            }

            Button {
                id: hvenBtn
                objectName: "hvenBtnObj"
                anchors.left: parent.left
                anchors.right: parent.right
                property color gradcolor1: "#ccc"
                property color gradcolor2: "#eee"
                property color gradcolor3: "#aaa"
                property color gradcolor4: "#ccc"
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 50
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? hvenBtn.gradcolor1 : hvenBtn.gradcolor2 }
                            GradientStop { position: 1 ; color: control.pressed ? hvenBtn.gradcolor3 : hvenBtn.gradcolor4 }
                        }
                    }
                }
                text: qsTr("HV Enable")
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                onClicked: hvEnableCommand()
            }

            Button {
                id: drenBtn
                objectName: "drenBtnObj"
                anchors.left: parent.left
                anchors.right: parent.right
                property color gradcolor1: "#ccc"
                property color gradcolor2: "#eee"
                property color gradcolor3: "#aaa"
                property color gradcolor4: "#ccc"
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 50
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? drenBtn.gradcolor1 : drenBtn.gradcolor2 }
                            GradientStop { position: 1 ; color: control.pressed ? drenBtn.gradcolor3 : drenBtn.gradcolor4 }
                        }
                    }
                }
                text: qsTr("Drive Enable")
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                onClicked: driveEnableCommand();
            }

            Button {
                id: stopBtn
                objectName: "stopBtnObj"
                anchors.left: parent.left
                anchors.right: parent.right
                property color gradcolor1: "#ccc"
                property color gradcolor2: "#eee"
                property color gradcolor3: "#aaa"
                property color gradcolor4: "#ccc"
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 100
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        color: "#F66"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? stopBtn.gradcolor1 : stopBtn.gradcolor2 }
                            GradientStop { position: 1 ; color: control.pressed ? stopBtn.gradcolor3 : stopBtn.gradcolor4 }
                            //GradientStop { position: 1 ; color: control.pressed ? "#F66" : "#E55" }
                            //GradientStop { position: 0 ; color: control.pressed ? "#F99" : "#F66" }
                        }
                    }
                }
                text: qsTr("Stop")
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                onClicked: stopCommand()
            }

            Slider {
                id: vdemand
                height: 50
                stepSize: 1
                maximumValue: 40
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.horizontalCenter: commandsGB.horizontalCenter
                onValueChanged: {
                    console.log("Slider value :" + vdemand.value)
                    rootwindow.vdemandSliderChanged(vdemand.value)
                }
            }


        }
    }

    // Aktuális értékek elemcsoportja

    // Oszlopba rendezett további elemek
    TabView{
        objectName: "graphTabView"
        height: 486
        currentIndex: 0
        frameVisible: true
        tabsVisible: true

        id: mainView
        anchors.bottom: logWindow.top
        anchors.bottomMargin: 0
        anchors.leftMargin: 6
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: -6
        anchors.left : commandsGB.right
        anchors.top : parent.top


        Tab{
            title:"Pillanatnyi értékek"

            ColumnLayout {
                width: 351
                anchors.bottomMargin: 259
                // Felfelé, lefelé és balra a szülő széléhez illeszkedik. Jobbra nem, mert
                //  széthúzni felesleges őket.
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                // Sima szövegek (Text elemek), amiknek az értéke egy a C++ oldalon definiált currentState
                //  értékétől függ. (Ha az értéke null, akkor "?" jelenik meg.)
                // A currentState-et a MainWindowsEventHandling::historyChanged metódus regisztrálja be, hogy
                //  látható legyen a QML oldalról is. (Hivatkozás a RobotStateHistory::currentState-re.)
                Text { text: " Current: " + curr.data.toFixed(2) + " A" ;font.bold: true ;font.pointSize: 14}
                Text { text: " Speed: " + (speed.data*3.6).toFixed(2) + " km/h" ;font.bold: true ;font.pointSize: 14}
                Text { text: " Torque: " + torq.data.toFixed(2) + " Nm"  ;font.bold: true ;font.pointSize: 14}
                Text { text: " Rail Voltage: " + vrail.data.toFixed(2) + " V" ;font.bold: true ;font.pointSize: 14 }
                Text { text: " Accu voltage: " + vacc.data.toFixed(2) + " V"  ;font.bold: true ;font.pointSize: 14 }
                Text { text: " Charge left: " + capac.data.toFixed(2) + " Ah"  ;font.bold: true ;font.pointSize: 14 }
            }
        }


        Tab {
            objectName: "graphTab"
            title: "Grafikon"
            Item {

                objectName: "graphTabItem"
                CustomPlotItem {

                    objectName: "customPlot"
                    id: customPlot
                    anchors.fill: parent

                    Component.onCompleted: initCustomPlot()

                }
            }
        }

        Tab {
            id: battTab
            title: "Battery"

            BatteryView{
                id: battery
                anchors.fill: parent
            }
        }



        style: TabViewStyle {
            frameOverlap: 0
            tab: Rectangle {
                color: styleData.selected ? "grey" :"lightgrey"
                border.color:  "#888"
                implicitWidth: Math.max(text.width + 4, 100)
                implicitHeight: 25
                radius: 1
                Text {
                    id: text
                    anchors.centerIn: parent
                    text: styleData.title
                    color: styleData.selected ? "white" : "black"
                }
            }
            frame: Rectangle { color: "white" }
        }




    }



    // Delegate: this is the appearance of a list item
    // A későbbi history listának szüksége van egy delegate-re. Minden lista elem ennek a komponensnek egy
    //  példánya lesz.
    Component {
        // ID, hogy tudjuk a listánál hivatkozni erre, mint a lista delegatejére.
        id: stateDelegate
        Row {
            // Itt a model az, ami a list egyik eleme. (Bármi is legyen majd az.)
            Text { text: model.statusName }
            Text { text: " X: " + model.x.toFixed(3) }
            Text { text: " V: " + model.v.toFixed(3) }
            Text { text: " A: " + model.a.toFixed(3) }
        }
    }

    // Az állapot lista és a grafikon GroupBoxa.
    GroupBox {
        id: logWindow
        title: qsTr("Event Log")
        // Oldalra és lefelé kitölti a szülőt.
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        // Felfelé a commandsGB és currentValuesGB GroupBoxok közül ahhoz igazodik, aminek lejjebb van az alja.
        anchors.top: commandsGB.bottom
        anchors.topMargin: 0


        // Sorban egymás mellett van a lista és a grafikon
        RowLayout {
            // Kitölti a szülőt és nem hagy helyet az elemek között.
            anchors.fill: parent
            spacing: 0
            // A history lista egy scrollozható elemen belül van.
            ScrollView {
                // A scrollohzató elem igazítása a szölő RowLayouthoz.
                // Itt a ScrollViewon belül adjuk meg, hogy a RowLayoutban
                //  mik legyenek a rá (ScrollViewra) vonatkozó méret beállítások,
                //  mert ezeket a RowLayout kezeli ebben az esetben.
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth: 100
                Layout.minimumHeight: 150
                Layout.preferredHeight: 150


                // Itt jön a tényleges lista.
                ListView {
                    id: stateHistoryList
                    anchors.rightMargin: 10
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 10
                    anchors.topMargin: 0
                    // A model az, ahonnan az adatokat vesszük.
                    // A historyModel változót a MainWindowsEventHandling::historyChanged metódus teszi
                    //  elérhetővé a QML oldalon is.
                    //  Típusa QList<QObject*>, a tárolt pointerek valójában RobotState-ekre mutatnak.

                    //model: historyModel

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

            // A HistoryGraph példányosítása, melyet külön fájlban definiáltunk.
            //  (A rendszer név alapján találja meg a fájlt.)


        }
    }
}
