import can
import dbus
from dbus.mainloop.glib import DBusGMainLoop
from gi.repository import GLib
import struct

# Initialize D-Bus main loop
DBusGMainLoop(set_as_default=True)

class DbusSpeed(dbus.service.Object):
    def __init__(self, bus_name, object_path):
        dbus.service.Object.__init__(self, bus_name, object_path)
        self.current_speed = 0.0
        self.current_rpm = 0.0

    @dbus.service.Property(dbus.Double)
    def Get_CurrentSpeed(self):
        return self.current_speed

    @dbus.service.Property(dbus.Double)
    def Get_CurrentRPM(self):
        return self.current_rpm

def receive_can_data(dbus_speed):
    bus = can.interface.Bus(channel='can0', bustype='socketcan')
    while True:
        message = bus.recv()
        if message is not None:
            data = message.data

            # Unpack data as two 4-byte floats (RPM and Speed)
            rpm, speed = struct.unpack('<ff', data)

            # Convert RPM and Speed to 8-byte long long unsigned int
            rpm_8bytes = struct.unpack('<Q', struct.pack('<f', rpm))[0]
            speed_8bytes = struct.unpack('<Q', struct.pack('<f', speed))[0]

            # Perform right shift by 32 bits
            rpm_4bytes = rpm_8bytes >> 32
            speed_4bytes = speed_8bytes >> 32

            # Convert back to double and allocate data in current_rpm && speed
            dbus_speed.current_rpm = struct.unpack('<d', struct.pack('<Q', rpm_4bytes))[0]
            dbus_speed.current_speed = struct.unpack('<d', struct.pack('<Q', speed_4bytes))[0]

            print(f"Received RPM: {dbus_speed.CurrentRPM}, Speed: {dbus_speed.CurrentSpeed}")

# Start D-Bus service
bus_name = dbus.service.BusName("com.example.CanData", dbus.SessionBus())
dbus_speed = DbusSpeed(bus_name, "/com/example/CanData/Speed")

# Start receiving CAN data and publishing on D-Bus
GLib.idle_add(receive_can_data, dbus_speed)

loop = GLib.MainLoop()
loop.run()
