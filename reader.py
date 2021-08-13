import serial

bancoEVR=serial.Serial('COM4',baudrate=9600,timeout=1)
mBancoEVR=bancoEVR.readline()
mensaje=str(mBancoEVR.decode('utf-8'))

while True:
    if (mensaje!='FIN'):
        print(mensaje)
    elif (mensaje==' ' or mensaje==''):
        print(None)
    else:
        bancoEVR.close()
        exit()