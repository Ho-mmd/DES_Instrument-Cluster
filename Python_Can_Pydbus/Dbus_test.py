from pydbus import SessionBus
from gi.repository import GLib
import time

bus = SessionBus()
loop = GLib.MainLoop()

class DbusSpeed:
    def __init__(self):
        self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Speed")
        self._current_speed = 110
        self._current_rpm = 110

    def update_speed_rpm(self, speed, rpm):
        self._current_speed = speed
        self._current_rpm = rpm
        print(f"Sending RPM: {self._current_rpm}, Speed: {self._current_speed}")
        self._dbus.setData(speed, rpm)

def send_data_incrementally(dbus_speed):
    # Incrementally increase speed and rpm by 5
    if(dbus_speed._current_speed == 160):
    	time.sleep(10)
    	dbus_speed._current_speed = 110
    	
    dbus_speed.update_speed_rpm(dbus_speed._current_speed + 2, dbus_speed._current_rpm + 2)
    
    # Return True to keep the timeout callback active
    return True

dbus_speed = DbusSpeed()

# Schedule the function to run every second
GLib.timeout_add_seconds(1, send_data_incrementally, dbus_speed)

loop.run()
