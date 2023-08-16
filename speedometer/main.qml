import QtQuick 2.9
import QtQuick.Window 2.2
import com.ulasdikme.speedometer 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.15

Window {
    visible: true
    width: 1280
    height: 400
    title: qsTr("Speedometer")
    color: "#000000"
//    visisbility:  "FullScreen"
    Speedometer
    {
        objectName: "speedoMeter"
        anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        alignAngle: alignAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }

//    ProgressBar {
//        from: 0
//        to: 100
//        value: 30
////        visualPosition: 0.3
//        leftInset : 50
//        topInset: 50
//        Text {
//            id: battery
//            text: qsTr("battery level")
//            color: "green"
//        }

//    }


}
