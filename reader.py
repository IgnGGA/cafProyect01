import serial,os,datetime

fecha=datetime.datetime.now()
nFecha=fecha.strftime('%y%m%d%H%M%S')
bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)
file = open('C:/testEVR/{}EVRtest.txt'.format(nFecha),'a')

while True:
    mBancoEVR=bancoEVR.readline()
    mensaje=str(mBancoEVR.decode('utf-8'))
    file.write(mensaje)
    print(mensaje)