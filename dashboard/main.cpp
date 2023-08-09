#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QQmlContext>
#include "main.h"

CanDataReceiver::CanDataReceiver(QObject *parent) : QObject(parent), m_speed(0), m_rpm(0)
{
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.isConnected()) {
        qDebug() << "Cannot connect to D-Bus.";
        return;
    }

    dbusInterface = new QDBusInterface("com.example.CanData", "/com/example/CanData/Speed",
                                       "com.example.CanData", connection, this);

    if (!dbusInterface->isValid()) {
        qDebug() << "D-Bus interface is not valid:" << dbusInterface->lastError().message();
        return;
    }

    bool success = connection.connect("com.example.CanData",
                                      "/com/example/CanData/Speed",
                                      "com.example.CanData",
                                      "setData",
                                      this,
                                      SLOT(onDataReceived(double,double)));

    if (!success) {
        qDebug() << "Failed to connect to setData signal.";
    }
}

double CanDataReceiver::speed() const {
    return m_speed;
}

double CanDataReceiver::rpm() const {
    return m_rpm;
}

void CanDataReceiver::onDataReceived(double speed, double rpm)
{
    qDebug() << '1' << speed;
    qDebug() << '2' << rpm;

    if(m_speed != speed) {
        m_speed = speed;
        emit speedChanged(speed);
    }

    if(m_rpm != rpm) {
        m_rpm = rpm;
        emit rpmChanged(rpm);
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));

    CanDataReceiver receiver;  // Initialize the CanDataReceiver
    qmlRegisterType<CanDataReceiver>("CanData", 1, 0, "CanDataReceiver");


    QQmlApplicationEngine engine(QUrl("qrc:/qml/test.qml"));
    engine.rootContext()->setContextProperty("canDataReceiver", &receiver);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
