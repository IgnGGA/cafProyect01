import serial,os,datetime

fecha=datetime.datetime.now()
nFecha=fecha.strftime('%Y%m%d_%H%M%S')
mFecha=fecha.strftime('%d/%m/%Y')
bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)
file = open('C:/testEVR/{}_EVRtest.txt'.format(nFecha),'a')

while True:
    vacio1=''
    vacio2=' '
    finEVR='FIN'
    mBancoEVR=bancoEVR.readline()
    mensaje=str(mBancoEVR.decode('utf-8'))
    if (mensaje.len()>0):
        file.write('{} {}'.format(mFecha,mensaje))
        print('{} {}'.format(mFecha,mensaje))
    elif (mensaje==finEVR):
        print('{} {}'.format(mFecha,mensaje))
        file.close()
        print('{} {}'.format(mFecha,mensaje))