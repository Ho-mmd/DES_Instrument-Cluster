import time
import board
import busio
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket
import adafruit_ads1x15.ads1015 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# 함수: IP 주소 가져오기
def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

# I2C 설정
i2c_oled = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c_oled, addr=0x3C)

# ADS1015 설정
i2c_ads = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1015(i2c_ads, address=0x3C)  # ADS1015의 주소는 0x3C입니다.

# 아날로그 입력 핀 설정
analog_in = AnalogIn(ads, ADS.P0)  # P0 핀으로부터 아날로그 입력을 읽어옵니다.

# OLED 초기화
oled.fill(0)
oled.show()
width = oled.width
height = oled.height
image = Image.new("1", (width, height))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()

try:
    while True:
        # IP 주소 가져오기
        ip_address = get_ip()

        # ADS1015를 통해 배터리 전압 측정
        battery_voltage = analog_in.voltage

        # 배터리의 최대 전압 (예: 4.2V)
        max_voltage = 4.2

        # 배터리 잔량 계산
        battery_level = (battery_voltage / max_voltage) * 100

        # OLED 디스플레이에 배터리 잔량과 IP 주소 표시
        draw.rectangle((0, 0, width, height), outline=0, fill=0)
        draw.text((0, 0), "IP 주소:", font=font, fill=255)
        draw.text((0, 16), ip_address, font=font, fill=255)
        draw.text((0, 24), f"배터리 잔량: {battery_level:.2f}%", font=font, fill=255)
        oled.image(image)
        oled.show()

        # 1초마다 반복
        time.sleep(1)

except KeyboardInterrupt:
    pass

