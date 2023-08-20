import can
import struct
import asyncio
from pydbus import SessionBus
import time
import sys
from piracer.vehicles import PiRacerStandard
from piracer.gamepads import ShanWanGamepadfrom

bus = SessionBus()
piracer = PiRacerStandard()
shanwan_gamepad = ShanWanGamepad()

DBUS_INTERFACE = """
<node>
    <interface name="com.example.Chkout">
        <method name="handleError">
        </method>
    </interface>
</node>
"""

class DbusData:
    """A class to interact with D-Bus and represent data."""
    
    def __init__(self):
        # Get D-Bus object
        start_time = time.time()
        while(time.time() - start_time < 10):
            try:
                self._dbus = bus.get("com.example.CanData", "/com/example/CanData/Data")
                break
            except Exception as e:
                print("Trying to Connect!!")
                time.sleep(0.5)
        
        # Initialize current speed and rpm
        self._current_speed = 0.0
        self._current_rpm = 0.0
        self._current_battery = 0
        self._current_throttle = -0.038
        self._current_gear = "OFF"

    def update(self, speed, rpm, battery, gear):
        """Update and print the current speed and rpm, then set them to the D-Bus object."""
        self._current_speed = speed
        self._current_rpm = rpm
        self._current_battery = battery
        self._current_gear = gear
        print(f"Received RPM: {self._current_rpm}, Speed: {self._current_speed} Battery: {self._current_battery}, Gear: {self._current_gear}")
        self._dbus.setData(speed, rpm, battery, gear)

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

            gamepad_input = shanwan_gamepad.read_data()
            throttle = gamepad_input.analog_stick_left.y

            if(speed == 0):
                gear = "P"
            elif(speed > 0 and throttle > -0.038):
                gear = "D"
            elif(speed > 0 and throttle <= -0.038):
                gear = "R"
            else:
                gear = "OFF"

            # Update values in dbus_speed
            dbus_data.update(speed, rpm, (((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100, gear)
            
            # Sleep for a second
            await asyncio.sleep(0.3) 

dbus_data = DbusData()

# Start receiving CAN data and run the asyncio main loop
asyncio.run(receive_can_data(dbus_data))

