import httplib2
import serial
import time
import re

ser = serial.Serial("COM6")
ser.baundrate = 9600
itsRaining = 0
distance = 0
conn = httplib2.Http()

while True:
    ch = ser.readline().decode()
    print(ch)
    u = re.findall("distance=([0-9]+)", ch)
    y = re.findall("It is raining.", ch)

    if len(y) == 0:
        itsRaining = 0
    else: 
        itsRaining = 1
    
    if len(u) != 0:
        distance = int(u[0])
    
    conn.request("https://api.thingspeak.com/update?api_key=UJLIA4UHO5IFI2WV&field1=%d&field2=%d" %(itsRaining, distance))