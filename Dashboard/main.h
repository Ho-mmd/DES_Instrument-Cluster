#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QDBusConnection>

class CanReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(float rpm READ rpm NOTIFY rpmChanged)

public:
    CanReceiver();

    float speed() const;
    float rpm() const;

public slots:
    void setData(double speed, double rpm);

signals:
    void speedChanged();
    void rpmChanged();

private:
    double m_speed;
    double m_rpm;
};

#endif // MAIN_H
