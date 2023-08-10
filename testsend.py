import can
import struct
from pydbus import SessionBus
from gi.repository import GLib

bus = SessionBus()
loop = GLib.MainLoop()

class DbusSpeed:
    def __init__(self):
        self._dbus = bus.get_object("com.example.CanData", "/com/example/CanData/Speed")
        self._current_speed = 0.0
        self._current_rpm = 0.0

    def update_speed_rpm(self, speed, rpm):
        self._current_speed = speed
        self._current_rpm = rpm
        print(f"Received RPM: {self._current_rpm}, Speed: {self._current_speed}")
        self._dbus.setData(speed, rpm)

def receive_can_data(dbus_speed):
    can_bus = can.interface.Bus(channel='can0', bustype='socketcan')
    while True:
        message = can_bus.recv()
        if message is not None:
            data = message.data

            # Unpack data as two 4-byte floats (RPM and Speed)
            rpm, speed = struct.unpack('<ff', data)

            # Update values in dbus_speed
            dbus_speed.update_speed_rpm(speed, rpm)

dbus_speed = DbusSpeed()

# Start receiving CAN data
GLib.idle_add(receive_can_data, dbus_speed)

loop.run()

