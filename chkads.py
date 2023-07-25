import board
import busio

# I2C 주소 검색 함수
def find_ads1015_address():
    i2c = busio.I2C(board.SCL, board.SDA)
    device_addresses = i2c.scan()

    ads1015_addresses = [0x40, 0x41, 0x3C, 0x60]  # ADS1015의 가능한 I2C 주소 리스트

    for address in device_addresses:
        if address in ads1015_addresses:
            return address

    return None

# ADS1015 주소 검색
ads1015_address = find_ads1015_address()

if ads1015_address is not None:
    print(f"ADS1015가 검색되었습니다. I2C 주소: 0x{ads1015_address:02X}")
else:
    print("ADS1015가 검색되지 않았습니다.")

