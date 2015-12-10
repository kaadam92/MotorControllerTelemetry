import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import CustomPlot 1.0

ColumnLayout {

    Text { text: " Current: " + curr.data.toFixed(2) + " A" ;font.bold: true ;font.pointSize: 14}
    Text { text: " Speed: " + (speed.data*3.6).toFixed(2) + " km/h" ;font.bold: true ;font.pointSize: 14}
    Text { text: " Torque: " + torq.data.toFixed(2) + " Nm"  ;font.bold: true ;font.pointSize: 14}
    Text { text: " Rail Voltage: " + vrail.data.toFixed(2) + " V" ;font.bold: true ;font.pointSize: 14 }
    Text { text: " Accu voltage: " + vacc.data.toFixed(2) + " V"  ;font.bold: true ;font.pointSize: 14 }
    Text { text: " Charge left: " + capac.data.toFixed(2) + " Ah"  ;font.bold: true ;font.pointSize: 14 }
}
