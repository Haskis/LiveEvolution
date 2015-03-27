import QtQuick 2.3
import QtQuick.Controls 1.2

import ZPR 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 400
    title: qsTr("Hello World")
    Rectangle{
        anchors.fill: parent
        MapView{
            antialiasing: true
            smooth: true
            map: mapa
            anchors.fill: parent
        }
    }
}
