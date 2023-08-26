# Conneting Raspberry Pi using CAN Connection

### Using
###### - Raspberry Pi 4B
###### - WaveShare_2-CH CAN FD HAT

## Setting Arduino for CAN connection with Rpi

### Circuit Diagram

<img src = "https://github.com/Ho-mmd/DES_Project2/assets/55338823/2ebd3967-d65f-4534-bec2-42016171c267" width = 70% height = 70%>

### Simple Description of the code
###### - can_data_reciver.py: Receive CAN Data using python

## Setting RPI for Dbus between Python and Qt

### DBus
##### D-Bus is a system for IPC (InterProcess Communication). It has layers called libdbus, message bus daemon executable and Wrapper libraries. It is open source software, widely used ad interprocess communication for Linux desktops.

### Simple Description of the code
###### - can_recv_Pydbus.py: Receive Can Data using python
###### - chk_freq_graph.py: Plot raw speed and filtered speed to show the graph
###### - Dbus_test_without_piracer.py: Send data to Qt using DBus without CAN
###### - gamepad.py: Receive CAN Data and Send it to Qt usinf DBus
