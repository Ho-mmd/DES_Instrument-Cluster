import can
import struct
import asyncio
from pydbus import SessionBus
from piracer.vehicle import PiRacerStandard

bus = SessionBus()

class DbusSpeed:
    """A class to interact with D-Bus and represent speed data."""
    
    def __init__(self):
        # Get D-Bus object
        self._dbus = bus.get_object("com.example.CanData", "/com/example/CanData/Speed")
        
        # Initialize current speed and rpm
        self._current_speed = 0.0
        self._current_rpm = 0.0
        self._current_battery = 0.0

    def update_speed_rpm_battery(self, speed, rpm, battery):
        """Update and print the current speed, rpm, and battery, then set them to the D-Bus object."""
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery = battery
        print(f"Sending RPM: {self._current_rpm}, Speed: {self._current_speed}, Battery: {self._current_battery}")
        self._dbus.setData(speed, rpm, battery)

async def receive_can_data_and_battery(dbus_speed):
    """Function to receive CAN data and battery info, and update the DbusSpeed instance asynchronously."""
    
    # Initialize CAN bus interface
    can_bus = can.interface.Bus(channel='can0', bustype='socketcan')
    
    # Create PiRacerStandard object
    piracer = PiRacerStandard()
    
    while True:
        # Asynchronous sleep for non-blocking behavior
        await asyncio.sleep(0.01)

        # Receive CAN message
        message = can_bus.recv()
        
        if message is not None:
            data = message.data

            # Unpack data as two 4-byte floats (RPM and Speed)
            rpm, speed = struct.unpack('<ff', data)

            # Get battery info from the piracer
            battery = (((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100

            # Update values in dbus_speed
            dbus_speed.update_speed_rpm_battery(speed, rpm, battery)
            
            # Sleep for a second
            await asyncio.sleep(1)

# Start receiving CAN data and battery info, and run the asyncio main loop
dbus_speed = DbusSpeed()
asyncio.run(receive_can_data_and_battery(dbus_speed))
