import time
import board
import busio
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket

# OLED 설정
WIDTH = 128
HEIGHT = 32
i2c_oled = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(WIDTH, HEIGHT, i2c_oled)

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
        # IP 주소 가져오기
        ip_address = get_ip()

        # OLED 디스플레이에 배터리 잔량과 IP 주소 표시
        draw.rectangle((0, 0, width, height), outline=0, fill=0)
        draw.text((0, 0), "IP 주소:", font=font, fill=255)
        draw.text((0, 16), ip_address, font=font, fill=255)
        oled.image(image)
        oled.show()

        # 1초마다 반복
        time.sleep(1)

except KeyboardInterrupt:
    pass

