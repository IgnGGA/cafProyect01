import serial,os,datetime

from serial.win32 import ERROR_INVALID_USER_BUFFER

fecha=datetime.datetime.now()
nFecha=fecha.strftime('%Y%m%d_%H%M%S')
mFecha=fecha.strftime('%d/%m/%y')
ncount=1
bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)
consolidado = open('C:/testEVR/{}_EVRtest.txt'.format(nFecha),'a')


while True:
    vacio1=''
    vacio2=' '
    finEVR='FIN'
    offEVR='EVR: OFF'
    onEVR='EVR: ON'
    premilimar  = open('C:/testEVT/preliminares/{}_EVRpremilinar{}'.format(nFecha,ncount),'a')
    mBancoEVR=bancoEVR.readline()
    mensaje=str(mBancoEVR.decode('utf-8'))

    if (mensaje.len()>0):
        consolidado.write('{} {}'.format(mFecha,mensaje))
        print('{} {}'.format(mFecha,mensaje))
        if (mensaje==onEVR):
            premilimar  = open('C:/testEVT/preliminares/{}_EVRpremilinar{}'.format(nFecha,ncount),'a')
        premilimar.write('{} {}'.format(mFecha,mensaje))

    elif (mensaje==finEVR):
        consolidado.write('{} {}'.format(mFecha,mensaje))
        print('{} {}'.format(mFecha,mensaje))
        consolidado.close()
        bancoEVR.close()
        exit()
    
    elif (mensaje==offEVR):
        premilimar.write('{} {}'.format(mFecha,mensaje))
        consolidado.close()
        ncount=ncount+1