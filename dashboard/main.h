#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDBusInterface>
#include <QDBusAbstractAdaptor>
#include <QDebug>

class CanDataReceiver;

class CanDataAdaptor : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.example.CanData")

private:
    CanDataReceiver *m_receiver;

public:
    CanDataAdaptor(CanDataReceiver *receiver);

public slots:
    void SetData(double speed, double rpm);
};

class CanDataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)

public:
    explicit CanDataReceiver(QObject *parent = nullptr);

    double speed() const;
    double rpm() const;

signals:
    void speedChanged(double newSpeed);
    void rpmChanged(double newRpm);

public slots:
    void onDataReceived(double speed, double rpm);

private:
    QDBusInterface *dbusInterface;
    double m_speed;
    double m_rpm;
};

#endif // MAIN_H
