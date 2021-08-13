import serial, datetime, os
bancoEVR=serial.Serial('COM4',baudrate=9600,timeout=1)
fecha = datetime.datetime.now()
nombre=str(fecha.year,fecha.month,fecha.day,fecha.hour,fecha.minute,fecha.second,'_EVRtest')
file = open('C:/testEVR/',nombre,'.txt','a')
mBancoEVR=bancoEVR.readline()
mensaje=str(mBancoEVR.decode('utf-8'))

while True:
    if (mensaje!="FIN"):
        print(fecha,mensaje)
        file.write(fecha,mensaje)
    else:
        file.close()
        bancoEVR.close()
