#ifndef CARDASH_H
#define CARDASH_H

#include <QObject>
#include <QDBusConnection>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QMutex>
#include <dash_adaptor.h>

class carDash   :   public QObject
{
    Q_OBJECT

    Q_PROPERTY                              (double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY                              (double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY                              (double battery READ battery NOTIFY batteryChanged)
    Q_PROPERTY                              (QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY                              (int errval READ errval NOTIFY errchk)

public:
    carDash();
    double      speed()                     const;
    double      rpm()                       const;
    double      battery()                   const;
    QString     gear()                      const;
    int         errval()                    const;

signals:
    void        speedChanged                (double speed);
    void        rpmChanged                  (double rpm);
    void        batteryChanged              (double battery);
    void        gearChanged                 (QString gear);

    void        errchk                      ();

public slots:
    void        setData                     (double speed, double rpm, double battery, QString gear);

    void        updateSpeed                 (double speed);
    void        updateRpm                   (double rpm);
    void        updateBattery               (double battery);
    void        updateGear                  (QString gear);

    void        checkErrVal                 ();
    void        startThread                 ();
    void        callHandleErrorOnPython     ();

private:
    double      my_speed;
    double      my_rpm;
    double      my_battery;
    QString     my_gear;

    int         my_errval;
    int         previous_errval             = 0;
    int         my_errvalSwitchCount        = 0;
    QThread*    errvalCheckThread;
    QMutex      mutex;

};

#endif // CARDASH_H
