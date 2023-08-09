/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p dbus_proxy dbus_test.xml
 *
 * qdbusxml2cpp is Copyright (C) 2023 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#pragma once
#ifndef DBUS_PROXY_H
#define DBUS_PROXY_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.example.CanData
 */
class ComExampleCanDataInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.example.CanData"; }

public:
    ComExampleCanDataInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~ComExampleCanDataInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> setData(double rpm, double speed)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(rpm) << QVariant::fromValue(speed);
        return asyncCallWithArgumentList(QStringLiteral("setData"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace com {
  namespace example {
    typedef ::ComExampleCanDataInterface CanData;
  }
}
#endif
