#TEMPLATE = app
TARGET = dashboard_app
INCLUDEPATH += .
QT += quick dbus core

SOURCES += \
    main.cpp

RESOURCES += \
    dashboard.qrc

OTHER_FILES += \
    qml/Dashboard.qml \
    qml/Fuel.qml \
    qml/FuelNeedle.qml \
    qml/Gear.qml \
    qml/Info.qml \
    qml/main.qml \
    qml/Speed.qml \
    qml/SpeeNeedle.qml

DBUS_ADAPTORS += dbus_test.xml
DBUS_INTERFACES += dbus_test.xml

target.path = target.path = /home/SEAme02/DES_Project2/dashboard

INSTALLS += target

HEADERS += \
    main.h
