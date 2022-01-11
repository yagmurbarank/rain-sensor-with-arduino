import httplib2
import serial
import time
import re

ser = serial.Serial("COM6")
ser.baundrate = 9600

yagmurVar = 0
uzaklik = 0

conn = httplib2.Http();
while True:
    ch = ser.readline().decode()
    print(ch)
    u = re.findall("mesafe=([0-9]+)", ch)
    y = re.findall("Var", ch)

    if len(y) == 0:
        yagmurVar = 0;
    else: 
        yagmurVar = 1
    
    if len(u) != 0:
        uzaklik = int(u[0])
    #print(uzaklik)
    #print(yagmurVar)
    conn.request("https://api.thingspeak.com/update?api_key=UJLIA4UHO5IFI2WV&field1=%d&field2=%d" %(yagmurVar, uzaklik))