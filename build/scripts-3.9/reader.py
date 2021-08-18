import serial,os,datetime,sys#importe de librerias

def pruebaEVR():
    fecha=datetime.datetime.now()#se genera FECHA y HORA como dato en la VARIABLE
    nFecha=fecha.strftime('%Y%m%d_%H%M%S')#se genera una variable con el string YMD_HMS
    mFecha=fecha.strftime('%d/%m/%y')#se genera una variable con el string DMY
    bancoEVR = serial.Serial('COM21',baudrate=9600,timeout=1)#se establece comunicacion serial, con el puerto COM, la velocidad de datos y el tiempo de espera
    consolidado = open('C:/testEVR/{}_EVRtest.txt'.format(nFecha),'a')#se genera archivi en ruta, su nombre se genera en funcion de la fecha y hora
    print('el programa Reader esta diseñado para leer\ny escribir un archivo con el historial\ndel banco de pruebas EVR V1.\nLos archivo generdos se almacenaran en\nla carpeta: C:\\testEVR')
    print('\n\npara detener la ejecucion del "Reader" presionar las teclas "Crtl" + "c" para generar el archivo hasta este punto\n\n')
    print('\nen caso de que el programa se cierre por accidente,\nvolver a ejecutarlo reiniciara la pruebas\n')
    print('\ndudas, revisar manual de uso del banco de pruebas EVR\n')
    print('Fecha de la prueba: {}\n\n'.format(fecha))
    while True:#El programa se ejecuta siempre.
        finEVR=str('FIN')#mensjae serial del arduino = a FIN
        mBancoEVR=bancoEVR.readline()#se indica la lectura de los mensajes seriales
        nBancoEVR=str(mBancoEVR.decode('utf-8'))#se transforman los mensajes seriales en string's con formato utf-8
        mensaje=nBancoEVR.strip()#limpia la variable nBancoEVR de espacios vacios
        aEvaluar=(mensaje==finEVR)#Se evalua que el mensaje tenga el mismo valor booleano que la condicion
        if (len(mensaje)>0):#si el largo del mensaje es mayor a 0no
            consolidado.write('{} {}\n'.format(mFecha,mensaje))#se escribe una nueva linea en el consolidado
            print('{} {}'.format(mFecha,mensaje))#se imrprime el mensaje en pantalla
        if (aEvaluar==True):#si el mensaje es igual al de la variable
            consolidado.write('{}',format(fecha))
            consolidado.close()#se cierra el archivo
            bancoEVR.close()#se cierra el puerto serial
            print('Fin de la prueba EVR\nrevisar en ruta indicada, el historia de la prueba.\n')
            print(fecha)
            print('C:\\testEVR\\{}_EVRtest.txt'.format(nFecha))
            print('\n\n\n\n\nCaf Chile Version 16 de Agosto de 2021')
            sys.exit()#se finaliza el programa

def preparacion():
    opcionSi=('s','S','si','Si','SI','sI','y','Y','yes','YES','Yes','YEs','yES','YeS','yEs','yeS','ok','Ok','oK','OK','okay','Okay','oKAY')
    opcionNo=('n','N','no','No','NO','nO','not','Not','NOT','NOt','nOT','nOt','noT','NoT')
    opcionSalir=('salir','Salir','Quit','quit','exit','Exit','quitar','Quitar','close','Close','esc','Esc','cerrar','Cerrar','cERRAR','Fin','FIN','fin','End','end','END')
    
    print('\n\n\tFavor de verificar:\n¿el Banco de pruebas EVR V1 esta conectado via USB al computador?\n\n(Sí) o (No)\nescriba su respuesta y presione enter\n')
    eleccion=input()
    if (eleccion in opcionSi):
        pruebaEVR()
    elif (eleccion in opcionNo):
        print("\n\tPor favor conectar via USB el Banco de pruebas EVR V1\n")
        preparacion()
    elif (eleccion in opcionSalir):
        print('Cerrando Aplicación')
        sys.exit()
    elif (eleccion not in opcionSi and eleccion not in opcionNo):
        print("\n\tesperando a una respuesta valida.\n")
        preparacion()

preparacion()