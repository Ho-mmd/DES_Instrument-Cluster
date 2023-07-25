import time
import board
import busio
import adafruit_ads1x15.ads1015 as ADS
from adafruit_ads1x15.analog_in import AnalogIn
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket

# OLED 설정
WIDTH = 128
HEIGHT = 32
i2c = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(WIDTH, HEIGHT, i2c)

# ADS1015 설정
ads = ADS.ADS1015(i2c)
chan = AnalogIn(ads, ADS.P0)

# 전압 측정 함수
def read_battery_voltage():
    # ADC 값을 전압으로 변환
    voltage = chan.voltage

    # 전압 값을 0V ~ 최대 전압 범위로 스케일링
    max_voltage = 5.0  # 배터리의 최대 전압 값으로 변경 (예: 3.7V 배터리인 경우 3.7)
    scaled_voltage = (voltage / max_voltage) * 100.0

    return scaled_voltage

# IP 주소 가져오는 함수
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
        # 배터리 전압 측정
        battery_voltage = read_battery_voltage()

        # IP 주소 가져오기
        ip_address = get_ip()

        # OLED 디스플레이에 배터리 잔량과 IP 주소 표시
        draw.rectangle((0, 0, width, height), outline=0, fill=0)
        draw.text((0, 0), "Battery Level:", font=font, fill=255)
        draw.text((0, 16), "{:.1f}%".format(battery_voltage), font=font, fill=255)
        draw.text((0, 24), "IP: {}".format(ip_address), font=font, fill=255)
        oled.image(image)
        oled.show()

        # 1초마다 반복
        time.sleep(1)

except KeyboardInterrupt:
    pass

