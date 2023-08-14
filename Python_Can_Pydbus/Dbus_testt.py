import asyncio
from pydbus import SessionBus
from piracer.vehicles import PiRacerStandard

bus = SessionBus()
piracder = PiRacerStandard()

class DbusSpeed:
    def __init__(self):
        self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Data")
        self._current_speed = 0
        self._current_rpm = 0
        self._current_battery = 0
        self._current_battery1 = 0 
        self._current_battery2 = 0
        self._current_battery3 = 0
	
    def update(self, speed, rpm, battery1, battery2, battery3):
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery = (((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100
        self._current_battery3 = self._current_battery % 10
        self._current_battery2 = (self._current_battery / 10) % 10 
        self._current_battery1 = self._current_battery / 100
        print(f"Sending RPM: {self._current_rpm}, Speed: {self._current_speed}, Battery: {self._current_battery}")
        self._dbus.setData(speed, rpm, battery1, battery2, battery3)

async def send_data_incrementally(dbus_data):
    while True:
        # Incrementally increase speed and rpm by 5
        if(dbus_data._current_speed >= 111):
            dbus_data._current_speed = 70

        if(dbus_data._current_battery <= 0):
            dbus_data._current_battery = 100
            

        dbus_data.update(dbus_data._current_speed + 1, dbus_data._current_rpm + 1, 
                         dbus_data._current_battery1, dbus_data._current_battery2, dbus_data._current_battery3)
        
        # Sleep for a second
        await asyncio.sleep(0.3)

dbus_data = DbusSpeed()

# Start the asyncio main loop
asyncio.run(send_data_incrementally(dbus_data))

