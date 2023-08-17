#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <main.h>
#include <cmath>
#include <QTimer>
#include <dash_adaptor.h>


CanReceiver::CanReceiver(): my_speed(0), my_rpm(0),my_battery(0), my_gear("OFF"){

    //Connect to D-Bus and Register and expose the interface
    QDBusConnection::sessionBus().registerService("com.example.CanData");

    new CanReceiverAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/com/example/CanData/Data", this);

    connect(this, SIGNAL(speedChanged(double)), this, SLOT(updateSpeed(double)));
    connect(this, SIGNAL(rpmChanged(double)), this, SLOT(updateRpm(double)));
    connect(this, SIGNAL(batteryChanged(double)), this, SLOT(updateBattery(double)));
    // connect(this, SIGNAL(throttleChanged(bool)), this, SLOT(updateThrottle(bool)));
    connect(this, SIGNAL(gearChanged(QString)), this, SLOT(updateGear(QString)));

}

double CanReceiver::speed() const{
    return my_speed;
}

double CanReceiver::rpm() const{
    return my_rpm;
}

double CanReceiver::battery() const{
    return my_battery;
}

QString CanReceiver::gear() const{
    return my_gear;
}

// bool CanReceiver::throttle() const{
//     return my_throttle;
// }

//QString CanReceiver::gear() const{
//    if(my_speed == 0){
//        return "P";
//    }
//    else if(my_speed > 0 && my_throttle){
//        return "D";
//    }
//    else if (my_speed > 0 && !my_throttle){
//        return "R";
//    }
//    else{
//        return "OFF";
//    }
//}


void CanReceiver::updateSpeed(double speed){
    my_speed = std::round(speed * 10) / 10.0;
    qDebug() << "Speed: " << my_speed;
}

void CanReceiver::updateRpm(double rpm){
    my_rpm = std::round(rpm*10)/ 10.0;
    qDebug() << "Rpm: " << my_rpm;
}
void CanReceiver::updateBattery(double battery){
    my_battery = int(battery);
    qDebug() << "Battery: " << my_battery;
}
// void CanReceiver::updateThrottle(bool throttle){
//     my_throttle = throttle;
//     qDebug() << "Throttle: " << my_throttle;
// }
void CanReceiver::updateGear(QString gear){
    my_gear = gear;
    qDebug() << "Gear: " << my_gear;
}


void CanReceiver::setData(double my_speed, double my_rpm, double my_battery, QString my_gear){

    if(!std::isnan(my_speed)){
        emit speedChanged(my_speed);
    }
    if(!std::isnan(my_rpm)){
        emit rpmChanged(my_rpm);
    }
    if(!std::isnan(my_battery)){
        emit batteryChanged(my_battery);
    }
//    if(!std::isnan(my_throttle)){
//        emit throttleChanged(my_throttle);
//    }
    if(1){
        emit gearChanged(my_gear);
    }
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CanReceiver canReceiver;

    engine.rootContext()->setContextProperty("canReceiver", &canReceiver);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
