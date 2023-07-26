import board
import busio

# ADS1015_Search function 
def find_ads1015_address():
    i2c = busio.I2C(board.SCL, board.SDA)
    device_addresses = i2c.scan()

    ads1015_addresses = [0x40, 0x41, 0x3C, 0x60]  # Possible ADS1015 Address list

    for address in device_addresses:
        if address in ads1015_addresses:
            return address

    return None

# SEARCH ADS1015 Address
ads1015_address = find_ads1015_address()

if ads1015_address is not None:
    print(f"ADS1015 O_ I2C Address: 0x{ads1015_address:02X}")
else:
    print("ADS1015 X")

