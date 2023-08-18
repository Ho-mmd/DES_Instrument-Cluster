#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <main.h>
#include <cmath>
#include <dash_adaptor.h>

CanReceiver::CanReceiver():my_speed(0), my_rpm(0), my_battery(0), my_gear("OFF"){

    //Connect to D-Bus and Register and expose the interface
    QDBusConnection::sessionBus().registerService("com.example.CanData");

    new CanReceiverAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/com/example/CanData/Data", this);

    connect(this, SIGNAL(speedChanged(double)), this, SLOT(updateSpeed(double)));
    connect(this, SIGNAL(rpmChanged(double)), this, SLOT(updateRpm(double)));
    connect(this, SIGNAL(batteryChanged(double)), this, SLOT(updateBattery(double)));
    connect(this, SIGNAL(gearChanged(QString)), this, SLOT(updateGear(QString)));

}

void CanReceiver::setData(double speed, double rpm, double battery, QString gear){

    if(!std::isnan(speed)){
        emit speedChanged(speed);
    }
    if(!std::isnan(rpm)){
        emit rpmChanged(rpm);
    }
    if(!std::isnan(battery)){
        emit batteryChanged(battery);
    }
    if(!gear.isEmpty()){
        emit gearChanged(gear);
    }

}


void CanReceiver::updateSpeed(double speed){
    my_speed = std::round(speed*10)/10.0;
}

void CanReceiver::updateRpm(double rpm){
    my_rpm = std::round(rpm*10)/ 10.0;
}
void CanReceiver::updateBattery(double battery){
    my_battery = int(battery);
}
void CanReceiver::updateGear(QString gear){
    my_gear = gear;
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
