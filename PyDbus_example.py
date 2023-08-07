import can
from pydbus import SessionBus
from gi.repository import GLib
import struct

class DbusService:
    dbus = """
    <node>
        <interface name='com.example.CanData'>
            <method name='getCurrentSpeed'>
                <arg type='d' name='speed' direction='out'/>
            </method>
            <method name='getCurrentRPM'>
                <arg type='d' name='rpm' direction='out'/>
            </method>
        </interface>
    </node>
    """

    def __init__(self):
        self.current_speed = 0.0
        self.current_rpm = 0.0

    def getCurrentSpeed(self):
        return self.current_speed

    def getCurrentRPM(self):
        return self.current_rpm

bus = SessionBus()
dbus_service = DbusService()
bus.publish("com.example.canData", dbus_service)  # Use a different name here

def receive_can_data():
    bus = can.interface.Bus(channel='can0', bustype='socketcan')
    while True:
        message = bus.recv()
        if message is not None:
            data = message.data

            # Unpack data as two 4-byte floats (RPM and Speed)
            rpm, speed = struct.unpack('<ff', data)

            # Convert RPM to 8-byte float and fill the remaining bytes with zeros
            rpm_8bytes = struct.unpack('<Q', struct.pack('<d', rpm))[0] >> 32

            # Convert Speed to 8-byte float and fill the remaining bytes with zeros
            speed_8bytes = struct.unpack('<Q', struct.pack('<d', speed))[0]

            # Update current_rpm and current_speed with the converted values
            dbus_service.current_rpm = struct.unpack('<d', struct.pack('<Q', rpm_8bytes))[0]
            dbus_service.current_speed = struct.unpack('<d', struct.pack('<Q', speed_8bytes))[0]

GLib.idle_add(receive_can_data)

loop = GLib.MainLoop()
loop.run()
