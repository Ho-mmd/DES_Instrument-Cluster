from piracer.vehicles import PiRacerStandard
import sys
from time import sleep

if __name__ == '__main__':
    piracer = PiRacerStandard()

    with open("test_battey.txt", "a") as file:
        piracer.set_throttle_percent(0.5)

        while True:
            battery = (((piracer.get_battery_voltage() / 3) - 2.5) / 1.7) * 100
            file.write(str(battery) + "%" + "\t")
            file.write(str((piracer.get_battery_voltage() / 3)) + "V" + "\n")
            file.flush()
            sleep(1)

