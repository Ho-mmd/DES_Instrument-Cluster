#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusInterface>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        qDebug() << "D-Bus connection failed";
        return 1;
    }

    // D-Bus 서비스와 인터페이스 설정
    QDBusInterface canDataInterface("com.example.CanData", "/com/example/CanData", "com.example.canData", connection);
    if (!canDataInterface.isValid()) {
        qDebug() << "Failed to connect to D-Bus interface";
        return 1;
    }

    // D-Bus의 set_data 메서드를 호출하여 데이터 가져오기
    QVariantList args;
    args << 100.0 << 50.0;  // 임의의 값
    QDBusMessage reply = canDataInterface.call("set_data", args);

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error:" << reply.errorMessage();
    } else {
        qDebug() << "Received data from D-Bus:" << reply.arguments();
    }

    return 0;
}
