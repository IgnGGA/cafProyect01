import serial,os,datetime,sys#importe de librerias

fecha=datetime.datetime.now()#se genera FECHA y HORA como dato en la VARIABLE
nFecha=fecha.strftime('%Y%m%d_%H%M%S')#se genera una variable con el string YMD_HMS
mFecha=fecha.strftime('%d/%m/%y')#se genera una variable con el string DMY
ncount=1#se genera un contador que empieza en 1
bancoEVR = serial.Serial('COM4',baudrate=9600,timeout=1)#se establece comunicacion serial, con el puerto COM, la velocidad de datos y el tiempo de espera
consolidado = open('C:/testEVR/{}_EVRtest.txt'.format(nFecha),'a')#se genera archivi en ruta, su nombre se genera en funcion de la fecha y hora
print('el programa Reader esta diseñado para leer\ny escribir un archivo con el historial\ndel banco de pruebas EVR V1.\nLos archivo generdos se alnacenaran en\nla carpeta: C:/testEVR')

while True:#El programa se ejecuta siempre.
    vacio1=''#primer caso vacio
    vacio2=' '#segundo caso vacio
    finEVR='FIN\n\r'#mensjae serial del arduino = a FIN
    offEVR='EVR: OFF'#mensaje serial del arduino = a EVR: OFF
    onEVR='EVR: ON'#mensaje serial del arduino = a EVR: ON
    mBancoEVR=bancoEVR.readline()#se indica la lectura de los mensajes seriales
    mensaje=str(mBancoEVR.decode('utf-8'))#se transforman los mensajes seriales en string's con formato utf-8

    if (len(mensaje)>0):#si el largo del mensaje es mayor a 0
        consolidado.write('{} {}'.format(mFecha,mensaje))#se escribe una nueva linea en el consolidado
        print('{} {}'.format(mFecha,mensaje))#se imrprime el mensaje en pantalla

    elif (mensaje==finEVR):#si el mensaje es igual al de la variable
        consolidado.close()#se cierra el archivo
        bancoEVR.close()#se cierra el puerto serial
        print('Fin del programa de analisis EVR\nrevisar en ruta indicada el historia de la prueba.')
        sys.exit()#se finaliza el programa
