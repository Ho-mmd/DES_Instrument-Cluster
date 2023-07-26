import time
import board
import busio
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont
import socket
from piracer.vehicles import PiRacerStandard
from piracer.gamepads import ShanWanGamepad
import threading

# OLED 설정
WIDTH = 128
HEIGHT = 32
i2c = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(WIDTH, HEIGHT, i2c)

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

# OLED에 IP 주소와 배터리 잔량 표시하는 함수
def display_ip_and_battery():
    ip = get_ip()
    battery = piracer.get_battery_voltage()

    oled.fill(0)
    image = Image.new("1", (oled.width, oled.height))
    draw = ImageDraw.Draw(image)

    font = ImageFont.load_default()

    draw.text((0, 0), ip, font=font, fill=255)
    draw.text((0, 16), str(round(battery, 1)) + "%", font=font, fill=255)

    oled.image(image)
    oled.show()

# 스레드로 OLED 정보를 주기적으로 업데이트
def oled_thread():
    while True:
        display_ip_and_battery()
        time.sleep(5.0)

# 컨트롤러 조작 처리
def controller_handler():
    while True:
        gamepad_input = shanwan_gamepad.read_data()
        throttle = gamepad_input.analog_stick_left.y
        steering = gamepad_input.analog_stick_right.y

        print(f'throttle={throttle}, steering={steering}')

        piracer.set_throttle_percent(throttle * 0.5)
        piracer.set_steering_percent(steering)

# OLED 스레드와 컨트롤러 핸들러 스레드를 생성하고 실행
oled_thread = threading.Thread(target=oled_thread)
controller_thread = threading.Thread(target=controller_handler)

oled_thread.start()
controller_thread.start()

# 메인 스레드가 종료되지 않도록 유지
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass
