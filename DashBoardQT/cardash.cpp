#include "cardash.h"

carDash::carDash():     my_speed(0), my_rpm(0),my_battery(0), my_gear("OFF"), my_errval(-1)
{

    //Connect to D-Bus and Register and expose the interface
    QDBusConnection::sessionBus().registerService("com.example.CanData");

    new CarDashAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/com/example/CanData/Data", this);

    startThread();

    connect             (this, SIGNAL(speedChanged(double)), this, SLOT(updateSpeed(double)));
    connect             (this, SIGNAL(rpmChanged(double)), this, SLOT(updateRpm(double)));
    connect             (this, SIGNAL(batteryChanged(double)), this, SLOT(updateBattery(double)));
    connect             (this, SIGNAL(gearChanged(QString)), this, SLOT(updateGear(QString)));

}

double                  carDash::speed()        const
{
    return              my_speed;
}

double                  carDash::rpm()          const
{
    return              my_rpm;
}

double                  carDash::battery()      const
{
    return              my_battery;
}

QString                 carDash::gear()         const
{
    return              my_gear;
}

int                     carDash::errval()       const
{
    return              my_errval;
}

void                    carDash::updateSpeed(double speed)
{
    my_speed            = std::round(speed*10)/10.0;
}

void                    carDash::updateRpm(double rpm)
{
    my_rpm              = std::round(rpm*10)/ 10.0;
}

void                    carDash::updateBattery(double battery)
{
    my_battery          = int(battery);
}

void                    carDash::updateGear(QString gear)
{
    my_gear             = gear;
}

void                    carDash::setData(double my_speed, double my_rpm, double my_battery, QString my_gear)
{

    if(!std::isnan(my_speed))
    {
                        emit speedChanged(my_speed);
    }
    if(!std::isnan(my_rpm))
    {
                        emit rpmChanged(my_rpm);
    }
    if(!std::isnan(my_battery))
    {
                        emit batteryChanged(my_battery);
    }
    if(1)
    {
                        emit gearChanged(my_gear);
    }

    {
                        QMutexLocker locker(&mutex);
                        my_errval           = (my_errval == 1) ? 2 : 1;
    }

    emit                errchk();
}

void                    carDash::startThread()
{
    errvalCheckThread   = QThread::create([this] { checkErrVal(); });
    errvalCheckThread   -> start();
}

void                    carDash::checkErrVal()
{
    while(true)
    {

                        QThread::sleep(1);

                        qDebug() << "Error Count: " << my_errvalSwitchCount;

                        if (my_errval == previous_errval)
                        {
                                            my_errvalSwitchCount++;
                        }
                        else
                        {
                                            my_errvalSwitchCount                        = 0;
                        }

                        if  (my_errvalSwitchCount == 5)
                        {
                                            my_errval                                   = -1;
                                            emit                                        errchk();
                                            emit                                        speedChanged(-1);
                                            emit                                        rpmChanged(my_rpm);
                                            emit                                        batteryChanged(-1);
                                            emit                                        gearChanged("OFF");
                                            callHandleErrorOnPython();
                                            qDebug() << "error";
                        }

                        if  (my_errvalSwitchCount >= 10)
                        {
                                            QCoreApplication::exit(0);
                        }

                        {
                                            QMutexLocker locker(&mutex);
                                            previous_errval                             = my_errval;
                        }
    }
}

void                    carDash::callHandleErrorOnPython()
{
    QDBusInterface      callPy("com.example.Chkout", "/com/example/Chkout", "com.example.Chkout");

    if (callPy.isValid())
    {
                        callPy.call("handleError");
    }
    else
    {
                        qDebug() << "Failed to access the D-Bus interface!";
    }
}
