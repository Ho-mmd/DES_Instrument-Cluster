#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <main.h>
#include <cmath>
#include <dash_adaptor.h>
#include <QDBusReply>

CanReceiver::CanReceiver(): my_speed(0), my_rpm(0),my_battery(0), my_gear("OFF"), my_errval(0){

    //Connect to D-Bus and Register and expose the interface
    QDBusConnection::sessionBus().registerService("com.example.CanData");

    new CanReceiverAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/com/example/CanData/Data", this);

    QDBusInterface remotePy("com.example.Chkout", "/com/example/Chkout");

    connect(this, SIGNAL(errchk(int, double, double, double, QString)), this, SLOT(setData(int, double, double, double, QString)));
    connect(this, SIGNAL(speedChanged(double)), this, SLOT(updateSpeed(double)));
    connect(this, SIGNAL(rpmChanged(double)), this, SLOT(updateRpm(double)));
    connect(this, SIGNAL(batteryChanged(double)), this, SLOT(updateBattery(double)));
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

int CanReceiver::errval() const{
    return my_errval;
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

void CanReceiver::updateErrval(int errval) {

    if(errval == 0)
        qDebug() << "Connection Failed!";
    else if(my_errval != errval) {
        my_errval = errval;
        emit errchk(my_errval, my_speed, my_rpm, my_battery, my_gear);
     }
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
