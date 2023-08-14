import can
import struct
import asyncio
from pydbus import SessionBus

bus = SessionBus()

class DbusSpeed:
    """A class to interact with D-Bus and represent speed data."""
    
    def __init__(self):
        # Get D-Bus object
        self._dbus = bus.get_object("com.example.CanData", "/com/example/CanData/Speed")
        
        # Initialize current speed and rpm
        self._current_speed = 0.0
        self._current_rpm = 0.0

    def update_speed_rpm(self, speed, rpm):
        """Update and print the current speed and rpm, then set them to the D-Bus object."""
        self._current_speed = speed
        self._current_rpm = rpm
        print(f"Received RPM: {self._current_rpm}, Speed: {self._current_speed}")
        self._dbus.setData(speed, rpm)

async def receive_can_data(dbus_speed):
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
            dbus_speed.update_speed_rpm(speed, rpm)
            
            # Sleep for a second
            await asyncio.sleep(1)

dbus_speed = DbusSpeed()

# Start receiving CAN data and run the asyncio main loop
asyncio.run(receive_can_data(dbus_speed))

