import QtQuick 2.15
import QtQuick.Controls 2.15
import CanData 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Speed: " + canDataReceiver.speed + " km/h"
            font.pixelSize: 24
        }

        Text {
            text: "RPM: " + canDataReceiver.rpm
            font.pixelSize: 24
        }
    }
}
