#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.");
        return 1;
    }

    QString interfaceName = "com.example.CanData";
    QString objectPath = "/com/example/CanData/Speed";

    if (!connection.registerService(interfaceName)) {
        qWarning() << "Cannot register service on the D-Bus session bus.";
        return 1;
    }

    int value = 0;
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        QDBusMessage message = QDBusMessage::createSignal(objectPath, interfaceName, "setData");
        message << double(value) << double(value);
        connection.send(message);
        qDebug() << "Sent data: " << value;
        value++;
    });
    timer.start(1000);

    return a.exec();
}
