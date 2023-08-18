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
    Q_PROPERTY(int errval READ errval NOTIFY errchk)

public:

    //consturctor
    CanReceiver();

    //Make getter function , get data in 8bytes
<<<<<<< HEAD
    double speed() const;
    double rpm() const;
    double battery() const;
    QString gear() const;
    int errval() const;
=======
    double speed() const { return my_speed; }
    double rpm() const { return my_rpm; }
    double battery() const { return my_battery; }
    QString gear() const { return my_gear; }//
>>>>>>> origin

signals:

    void speedChanged(double speed);
    void rpmChanged(double rpm);
    void batteryChanged(double battery);
<<<<<<< HEAD
    void gearChanged(QString gear);
    void errchk(int errval, double my_speed, double my_rpm, double my_battery, QString my_gear);

public slots:

    void setData(int my_errval, double my_speed, double my_rpm, double my_battery, QString my_gear);
=======
    void gearChanged(QString gear);//

public slots:

    void setData(double speed, double rpm, double battery, QString gear);
>>>>>>> origin


    void updateSpeed(double speed); //
    void updateRpm(double rpm);
    void updateBattery(double battery);
<<<<<<< HEAD
    void updateGear(QString gear);
    void updateErrval(int errval);
=======
    void updateGear(QString gear); //

>>>>>>> origin

private:

    double my_speed;
    double my_rpm;
    double my_battery;
<<<<<<< HEAD
    QString my_gear;
    int my_errval;
=======
    QString my_gear; //


>>>>>>> origin
};


#endif // MAIN_H
