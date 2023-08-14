import can
import struct
import asyncio
from piracer.vehicles import PiRacerStandard
from pydbus import SessionBus

bus = SessionBus()
piracer = PiRacerStandard()

class DbusData:
    """A class to interact with D-Bus and represent data."""
    
    def __init__(self):
        # Get D-Bus object
        self._dbus = bus.get_object("com.example.CanData", "/com/example/CanData/Data")
        
        # Initialize current speed and rpm
        self._current_speed = 0.0
        self._current_rpm = 0.0
        self._current_battery = 0

    def update(self, speed, rpm, battery):
        """Update and print the current speed and rpm, then set them to the D-Bus object."""
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery = battery
        print(f"Received RPM: {self._current_rpm}, Speed: {self._current_speed} Battery: {self._current_battery}")
        self._dbus.setData(speed, rpm, battery)

async def receive_can_data(dbus_data):
    """Function to receive CAN data and update the DbusSpeed instance asynchronously."""
    
    # Initialize CAN bus interface
    can_bus = can.interface.Bus(channel='can0', bustype='socketcan')
    
    while True:
        # Asynchronous sleep for non-blocking behavior
        await asyncio.sleep(0.01)

        # Receive CAN message
        message = can_bus.recv()
        
        if message is not None:
            data = message.data

            # Unpack data as two 4-byte floats (RPM and Speed)
            rpm, speed = struct.unpack('<ff', data)

            # Update values in dbus_speed
            dbus_data.update(speed, rpm, (((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100)
            
            # Sleep for a second
            await asyncio.sleep(0.3)

dbus_data = DbusData()

# Start receiving CAN data and run the asyncio main loop
asyncio.run(receive_can_data(dbus_data))

