import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "CAN Data Viewer"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Speed: " + canReceiver.speed + " km/h"
            font.pixelSize: 24
        }

        Text {
            text: "RPM: " + canReceiver.rpm
            font.pixelSize: 24
        }
    }
}
