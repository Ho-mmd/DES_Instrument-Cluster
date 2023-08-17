#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDBusConnection>
#include <QTimer>


class CanReceiver : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged)
    // Q_PROPERTY(bool throttle READ throttle NOTIFY throttleChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)


public:

    //consturctor
    CanReceiver();

    //Make getter function , get data in 8bytes
    double speed() const;
    double rpm() const;
    double battery() const;
    // bool throttle() const;
    QString gear() const; //

signals:
    void speedChanged(double speed);
    void rpmChanged(double rpm);
    void batteryChanged(double battery);
    // void throttleChanged(bool throttle);
    void gearChanged(QString gear);//

public slots:

    void setData(double my_speed, double my_rpm, double my_battery, QString my_gear);

    void updateSpeed(double speed);
    void updateRpm(double rpm);
    void updateBattery(double battery);
    // void updateThrottle(bool throttle);
    void updateGear(QString gear);


private:

    double my_speed;
    double my_rpm;
    double my_battery;
    // bool my_throttle;
    QString my_gear;
};


#endif // MAIN_H
