import asyncio
from pydbus import SessionBus

bus = SessionBus()

class DbusSpeed:
    def __init__(self):
        self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Speed")
        self._current_speed = 0
        self._current_rpm = 0

    def update_speed_rpm(self, speed, rpm):
        self._current_speed = speed
        self._current_rpm = rpm
        print(f"Sending RPM: {self._current_rpm}, Speed: {self._current_speed}")
        self._dbus.setData(speed, rpm)

async def send_data_incrementally(dbus_speed):
    while True:
        # Incrementally increase speed and rpm by 5
        if(dbus_speed._current_speed == 111):
            await asyncio.sleep(10)
            dbus_speed._current_speed = 0
            
        dbus_speed.update_speed_rpm(dbus_speed._current_speed + 1, dbus_speed._current_rpm + 1)
        
        # Sleep for a second
        await asyncio.sleep(0.3)

dbus_speed = DbusSpeed()

# Start the asyncio main loop
asyncio.run(send_data_incrementally(dbus_speed))

