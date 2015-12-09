import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

TabView{

    frameVisible: true
    tabsVisible: true




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
            //Text { text: " Állapot: " + (currentState!=null ? currentState.statusName : "?") }
            //Text { text: " Idő: " + (currentState!=null ? currentState.timestamp : "?") }
            // Text { text: " X: " + (currentState!=null ? currentState.x.toFixed(3) : "?") }
            //Text { text: " V: " + (currentState!=null ? currentState.v.toFixed(3) : "?") }
            //Text { text: " A: " + (currentState!=null ? currentState.a.toFixed(3) : "?") }
            //Text { text: " Lámpa: " + (currentState!=null ? currentState.light.toString() : "?") }
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
           title: "Green"
           Rectangle { color: "Green" }
       }

    Tab {
           title: "Green"
           Rectangle { color: "Green" }
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



