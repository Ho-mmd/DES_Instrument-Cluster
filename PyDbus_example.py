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
bus.publish("com.example.CanData", dbus_service)

def receive_can_data():
    bus = can.interface.Bus(channel='can0', bustype='socketcan')
    while True:
        message = bus.recv()
        if message is not None:
            data = message.data
            rpm, speed = struct.unpack('<ff', data[:4]), struct.unpack('<ff', data[4:])
            dbus_service.current_rpm = rpm[0]
            dbus_service.current_speed = speed[0]

GLib.idle_add(receive_can_data)

loop = GLib.MainLoop()
loop.run()
