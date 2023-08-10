#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QQmlContext>
#include <QDBusConnection>
#include "main.h"

CanDataAdaptor::CanDataAdaptor(CanDataReceiver *receiver)
    : QDBusAbstractAdaptor(receiver), m_receiver(receiver) {}

void CanDataAdaptor::SetData(double speed, double rpm) {
    m_receiver->onDataReceived(speed, rpm);
}

CanDataReceiver::CanDataReceiver(QObject *parent) : QObject(parent), m_speed(0), m_rpm(0) {
    new CanDataAdaptor(this);  // Adaptor 인스턴스 생성
    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService("com.example.CanData")) {
        qDebug() << "Cannot register D-Bus service.";
        return;
    }
    if (!connection.registerObject("/com/example/CanData/Speed", this)) {
        qDebug() << "Cannot register D-Bus object.";
        return;
    }
}

double CanDataReceiver::speed() const {
    return m_speed;
}

double CanDataReceiver::rpm() const {
    return m_rpm;
}

void CanDataReceiver::onDataReceived(double speed, double rpm) {
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

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));

    CanDataReceiver receiver;  // CanDataReceiver 초기화

    QQmlApplicationEngine engine(QUrl("qrc:/qml/test.qml"));
    engine.rootContext()->setContextProperty("canDataReceiver", &receiver);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
