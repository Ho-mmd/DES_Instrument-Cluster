import can
import struct
from gi.repository import GLib
from pydbus import SessionBus

class DbusSpeed:
    def __init__(self):
        self.current_speed = 0.0
        self.current_rpm = 0.0

    def Get_CurrentSpeed(self):
        return self.current_speed

    def Get_CurrentRPM(self):
        return self.current_rpm

bus = can.interface.Bus(channel='can0', bustype='socketcan')

def receive_can_data(dbus_speed):
    for message in bus:
        data = message.data

        # Unpack data as two 4-byte floats (RPM and Speed)
        rpm, speed = struct.unpack('<ff', data)

        # Convert RPM and Speed to 8-byte long long unsigned int
        rpm_long_long = struct.unpack('<Q', struct.pack('<f', rpm))[0]
        speed_long_long = struct.unpack('<Q', struct.pack('<f', speed))[0]

        # Perform right shift by 32 bits
        rpm_shifted = rpm_long_long >> 32
        speed_shifted = speed_long_long >> 32

        # Convert back to double and update current_rpm and current_speed
        dbus_speed.current_rpm = struct.unpack('<d', struct.pack('<Q', rpm_shifted))[0]
        dbus_speed.current_speed = struct.unpack('<d', struct.pack('<Q', speed_shifted))[0]

        print(f"Received RPM: {dbus_speed.Get_CurrentRPM()}, Speed: {dbus_speed.Get_CurrentSpeed()}")

# Start receiving CAN data
dbus_speed = DbusSpeed()

# Start receiving CAN data and publishing on D-Bus
GLib.idle_add(receive_can_data, dbus_speed)

# Create a SessionBus object to start D-Bus and register the application
session_bus = SessionBus()
session_bus.publish("com.example.CanData", dbus_speed)

loop = GLib.MainLoop()
loop.run()
