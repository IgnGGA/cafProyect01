import serial,os,datetime#importe de librerias

fecha=datetime.datetime.now()#se genera FECHA y HORA como dato en la VARIABLE
nFecha=fecha.strftime('%Y%m%d_%H%M%S')#se genera una variable con el string YMD_HMS
mFecha=fecha.strftime('%d/%m/%y')#se genera una variable con el string DMY
ncount=1#se genera un contador que empieza en 1
bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)#se establece comunicacion serial, con el puerto COM, la velocidad de datos y el tiempo de espera
consolidado = open('C:/testEVR/{}_EVRtest.txt'.format(nFecha),'a')#se genera archivi en ruta, su nombre se genera en funcion de la fecha y hora


while True:#El programa se ejecuta siempre.
    vacio1=''#primer caso vacio
    vacio2=' '#segundo caso vacio
    finEVR='FIN'#mensjae serial del arduino = a FIN
    offEVR='EVR: OFF'#mensaje serial del arduino = a EVR: OFF
    onEVR='EVR: ON'#mensaje serial del arduino = a EVR: ON
    mBancoEVR=bancoEVR.readline()#se indica la lectura de los mensajes seriales
    mensaje=str(mBancoEVR.decode('utf-8'))#se transforman los mensajes seriales en string's con formato utf-8

    if (mensaje.len()>0):#si el largo del mensaje es mayor a 0
        consolidado.write('{} {}'.format(mFecha,mensaje))#se escribe una nueva linea en el consolidado
        print('{} {}'.format(mFecha,mensaje))#se imrprime el mensaje en pantalla
        if (mensaje==onEVR):#si el mensaje es igual al de la variable...
            premilimar  = open('C:/testEVT/preliminares/{}_EVRpremilinar{}'.format(nFecha,ncount),'a')#se genera y abre el achivo
        premilimar.write('{} {}'.format(mFecha,mensaje))#escribe una nueva linea en el archivo.

    elif (mensaje==finEVR):#si el mensaje es igual al de la variable
        consolidado.write('{} {}'.format(mFecha,mensaje))#se escribe una nueva linea
        print('{} {}'.format(mFecha,mensaje))#se imprime el mensaje en pantalla
        consolidado.close()#se cierra el archivo
        bancoEVR.close()#se cierra el puerto serial
        exit()#se finaliza el programa
    
    elif (mensaje==offEVR):#si el mensaje es igual al de la variable
        premilimar.write('{} {}'.format(mFecha,mensaje))#se escribe una nueva linea
        premilimar.close()#se cierra el archivo premilimar
        ncount=ncount+1#se suma uno al contador ncount