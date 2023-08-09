#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDBusInterface>
#include <QDebug>

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

private slots:
    void onDataReceived(double speed, double rpm);

private:
    QDBusInterface *dbusInterface;
    double m_speed;
    double m_rpm;
};

#endif // MAIN_H

