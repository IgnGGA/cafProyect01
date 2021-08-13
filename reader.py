import serial,os

bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)
file = open('C:/testEVR/test.txt','a')

while True:
    mBancoEVR=bancoEVR.readline()
    mensaje=str(mBancoEVR.decode('utf-8'))
    file.write(mensaje)
    print(mensaje)