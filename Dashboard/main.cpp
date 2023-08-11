#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "main.h"

CanReceiver::CanReceiver() {
    // DBus 서비스 등록
    QDBusConnection::sessionBus().registerService("com.example.CanData");
    QDBusConnection::sessionBus().registerObject("/com/example/CanData/Speed", this, QDBusConnection::ExportAllSlots);
}

float CanReceiver::speed() const {
    return m_speed;
}

float CanReceiver::rpm() const {
    return m_rpm;
}

void CanReceiver::setData(double speed, double rpm) {
    m_speed = speed;
    m_rpm = rpm;
    emit speedChanged();
    emit rpmChanged();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

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
