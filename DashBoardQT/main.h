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
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(int errval READ errval NOTIFY errchk)

public:

    //consturctor
    CanReceiver();

    //Make getter function , get data in 8bytes
    double speed() const;
    double rpm() const;
    double battery() const;
    QString gear() const;
    int errval() const;

signals:
    void speedChanged(double speed);
    void rpmChanged(double rpm);
    void batteryChanged(double battery);
    void gearChanged(QString gear);
    void errchk(int errval, double my_speed, double my_rpm, double my_battery, QString my_gear);

public slots:

    void setData(int my_errval, double my_speed, double my_rpm, double my_battery, QString my_gear);

    void updateSpeed(double speed);
    void updateRpm(double rpm);
    void updateBattery(double battery);
    void updateGear(QString gear);
    void updateErrval(int errval);

private:

    double my_speed;
    double my_rpm;
    double my_battery;
    QString my_gear;
    int my_errval;
};


#endif // MAIN_H
