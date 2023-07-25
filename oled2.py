import time
import board
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket

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
    
# Set I2C address (0x3C is the default address for SSD1306-based OLED displays)
i2c = board.I2C()
oled = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c, addr=0x3C)
ip = get_ip()

# Clear the display
oled.fill(0)
oled.show()

# Create blank image for drawing
image = Image.new("1", (oled.width, oled.height))
draw = ImageDraw.Draw(image)

# Load default font
font = ImageFont.load_default()

# Display text
draw.text((0, 0), ip, font=font, fill=255)
oled.image(image)
oled.show()

# Wait for a few seconds
#time.sleep(5)

