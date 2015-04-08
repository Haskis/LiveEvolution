import QtQuick 2.3
import QtQuick.Controls 1.2

import ZPR 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1000
    height: 650
    title: qsTr("Hello World")
    Rectangle{
        id: topRect
        anchors.fill: parent
        Rectangle{
            id: mapRect
            anchors{
                left: parent.left;
                bottom: parent.bottom;
                top: parent.top;
                margins: 5
            }
            width: parent.width * 0.85
            color: "gray"

            MapView{
                id: mapView
                clip: true
                anchors.fill: parent
                antialiasing: true
                smooth: true
                map: mapa
            }
        }
        Rectangle{
            anchors{
                right: parent.right
                bottom: parent.bottom
                top: parent.top
                left: mapRect.right
                margins: 5

            }
            color: "lightgreen"

            Column{
                anchors{
                    left:parent.left
                    right: parent.right
                    top: parent.top
                    margins: 5
                }
                spacing: 5

                MButton{
                    text: "Start Simulation"
                    onClicked: simulation.start();
                    width: parent.width

                }
                MButton{
                    text: "Stop Simulation"
                    onClicked: simulation.stop();
                    width: parent.width
                }
                Text{
                    text: "Energy:" + mapView.selectedElement.energy.toFixed(2)
                }
            }

        }
    }
}
