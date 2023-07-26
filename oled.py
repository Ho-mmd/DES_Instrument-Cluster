import time
import board
<<<<<<< HEAD
=======
import busio
>>>>>>> 90bbdac65d70cf7fb5dcc4aa3c9ac88116940f16
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket
from piracer.vehicles import PiRacerStandard, PiracerBase

<<<<<<< HEAD
=======
# OLED 설정
WIDTH = 128
HEIGHT = 32
i2c = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(WIDTH, HEIGHT, i2c)

# IP 주소 가져오는 함수
>>>>>>> 90bbdac65d70cf7fb5dcc4aa3c9ac88116940f16
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
    
piracer = PiracerStandard() 
 
# Set I2C address (0x3C is the default address for SSD1306-based OLED displays)
i2c = board.I2C()
oled = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c, addr=0x3C)

# get ip_address and battery level
ip = get_ip()
battery = piracer.get_battery_voltage()

# Clear the display
oled.fill(0)
oled.show()

# Create blank image for drawing
image = Image.new("1", (oled.width, oled.height))
draw = ImageDraw.Draw(image)

# Load default font
font = ImageFont.load_default()

<<<<<<< HEAD
# Display text
draw.text((0, 0), ip, font=font, fill=255)
draw.text((0, 0), str(round(battery, 1))+"%", font=font, fill=255)

oled.image(image)
oled.show()

# Wait for a few seconds
#time.sleep(5)

=======
try:
    while True:
        # IP 주소 가져오기
        ip_address = get_ip()

        # OLED 디스플레이에 IP 주소 표시
        draw.rectangle((0, 0, width, height), outline=0, fill=0)
        draw.text((0, 0), "IP: {}".format(ip_address), font=font, fill=255)
        oled.image(image)
        oled.show()

        # 1초마다 반복
        time.sleep(1)

except KeyboardInterrupt:
    pass
>>>>>>> 90bbdac65d70cf7fb5dcc4aa3c9ac88116940f16
