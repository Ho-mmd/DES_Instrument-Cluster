import asyncio
from pydbus import SessionBus

bus = SessionBus()

class DbusData:
    def __init__(self):
        self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Data")
        self._current_speed = 0
        self._current_rpm = 0
        self._current_battery = 100
	
    def update(self, speed, rpm, battery):
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery -= 1
        print(f"Sending RPM: {self._current_rpm}, Speed: {self._current_speed}, Battery: {self._current_battery}")
        self._dbus.setData(speed, rpm, battery)

async def send_data_incrementally(dbus_data):
    while True:
        # Incrementally increase speed and rpm by 5
        if(dbus_data._current_speed >= 111):
            dbus_data._current_speed = 70

        if(dbus_data._current_battery <= 0):
            dbus_data._current_battery = 100
            

        dbus_data.update(dbus_data._current_speed + 1, dbus_data._current_rpm + 1, 
                         dbus_data._current_battery)
        
        # Sleep for a second
        await asyncio.sleep(0.3)

dbus_data = DbusData()

# Start the asyncio main loop
asyncio.run(send_data_incrementally(dbus_data))

