#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDBusConnection>


class CanReceiver : public QObject
{
    Q_OBJECT


    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double battery READ battery NOTIFY batteryChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)


public:

    //consturctor
    CanReceiver();

    //Make getter function , get data in 8bytes
    double speed() const { return my_speed; }
    double rpm() const { return my_rpm; }
    double battery() const { return my_battery; }
    QString gear() const { return my_gear; }//

signals:

    void speedChanged(double speed);
    void rpmChanged(double rpm);
    void batteryChanged(double battery);
    void gearChanged(QString gear);//

public slots:

    void setData(double speed, double rpm, double battery, QString gear);


    void updateSpeed(double speed); //
    void updateRpm(double rpm);
    void updateBattery(double battery);
    void updateGear(QString gear); //


private:

    double my_speed;
    double my_rpm;
    double my_battery;
    QString my_gear; //


};


#endif // MAIN_H
