import serial

bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)

while True:
    mBancoEVR=bancoEVR.readline()

    print(mBancoEVR)