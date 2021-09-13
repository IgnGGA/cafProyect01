#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
int error = 2;              //variable destinada a dar indicación de ERROR a causa de alguna condición incumplida
int pulseOut = 3;           //salida pulsos que simulan velocidad, se selecciona el pin11 por sus cualidades de salida PWM
int powerEVR = 5;           //enciende el EVR con 72V
int luz = 4;                //indicador que representa LUZ indicadora del TREN
int sirena = 6;             //indicador que representa la SIRENA o GRABACIÓN del tren
int puerta = 7;             //indicador que representa las PUERTAS del TREN
int X1_VT_6 = 8;            //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 6
int X7_VT_6 = 9;            //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 6
int X6_VT_6 = 10;           //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 6
int X1_VT_05 = 11;          //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 05
int X7_VT_05 = 12;          //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 05
int X6_VT_05 = 13;          //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 05
int selector = 22;          //seleccion entre prueba manual o automatica
int selectorManual05 = 23;  //seleccion manual de señal solo para reles de 0,5km
int selectorManual6 = 24;   //seleccion manual de señal solo para reles de 6km
int selectorManualMax = 25; //seleccion manual de señal a velocidad maxima.
float tiempo;               //tiempo que estara en funcion de la freciencia
float i, j;                 //contadores
int k, l, m, n;
float vel;              //valor de la velocidad en funcion de la frecuencia
const float vel_1 = 2;  //velocidad para apagar el rele 1
const float vel_2 = 20; //velocidad para apagar el rele 2
const float vel_3 = 0.1;
const float vel_4 = 4;
const float var1 = 0.953; //diametro de la rueda en metros
const float var2 = 3.6;   //constante de velocidad del TREN
const float var3 = 100;   //ventanas de la rueda
const float var4 = 4;     //Cantidad de veces que se multiplico la frecuencia maxima
int countMax = 928 * var4;
int seleccionManual05 = digitalRead(selectorManual05);
int seleccionManual6 = digitalRead(seleccionManual6);
int seleccionManualMax = digitalRead(seleccionManualMax);
void setup()
{
  Serial.begin(9600); //velocidad de lectura y escritura del arduino.
  lcd.begin(20, 4);
  lcd.print("Banco TEST EVR");
  pinMode(error, OUTPUT);
  pinMode(pulseOut, OUTPUT);
  pinMode(powerEVR, OUTPUT);
  pinMode(puerta, OUTPUT);
  pinMode(luz, OUTPUT);
  pinMode(sirena, OUTPUT);
  pinMode(X1_VT_6, INPUT);  //se define como entrada para lectura de reaccion del REGISTRADOR DE EVENTOS
  pinMode(X1_VT_05, INPUT); //se define como entrada para lectura de reaccion del REGISTRADOR DE EVENTOS
  pinMode(X7_VT_6, INPUT);
  pinMode(X7_VT_05, INPUT);
  pinMode(X6_VT_6, INPUT);
  pinMode(X6_VT_05, INPUT);
  pinMode(error, OUTPUT);
  pinMode(selector, INPUT);
  pinMode(selectorManual05, INPUT);
  pinMode(selectorManual6, INPUT);
  pinMode(selectorManualMax, INPUT);
}

void loop()
{
  int seleccion = digitalRead(selector);
  do
  {
    if (seleccion == 1)
    {
      Serial.println('Prueba Automatica');
      testEVR();
      break;
    }
    if (seleccion == 0)
    {
      Serial.print('Prueba Manual');
      manualTestEVR();
      break;
    }
  } while (true);
}
void star()
{
  displayOff();
  displayOn();
}
void instancia01()
{
  do
  {
    int a = digitalRead(X1_VT_05);
    int b = digitalRead(X1_VT_6);
    int c = digitalRead(X6_VT_6);
    int d = digitalRead(X6_VT_05);
    int e = digitalRead(X7_VT_6);
    int f = digitalRead(X7_VT_05);
    if (a == 1 && b == 1 && c == 1 && d == 0 && e == 0 && f == 0)
    {
      serial05();
      serial6();
      delay(14000);
      mensaje001();
      break;
    }
    else if ((a == 1 && b == 1 && c == 1) && (d == 1 || e == 1 || f == 1))
    {
      serial05();
      serial6();
      delay(14000);
      mensaje002();
      break;
    }
    else if ((a == 0 || b == 0) && c == 1)
    {
      mensaje003();
      serial05();
      serial6();
      error_007;
      break;
    }
    else if (a == 1 && b == 1 && c == 0)
    {
      mensaje004();
      serial05();
      serial6();
      error_006;
      break;
    }
    else
    {
      break;
    }
    break;
  } while (true);
}
void instancia02()
{
  do
  {
    lecturasEnBajada05();
    lecturasEnBajada6();
    mensaje005();
    break;
  } while (true);
}
//------------viaje-----------------------------------------------------------------------------------
void viaje()
{
  enEstacion();
  mensaje007();
  acelerar();
  mensaje008();
  desacelerar();
  mensaje009();
}
//---SALIDA_SEÑAL_CUADRADA----------------------------------------------------------------------------
void senalOut()
{                                 //Funcion que se encarga de generar los estados de los semiciclos correspondientes.
  tiempo = (1000 / (i / (var4))); //tiempo de duracion de cada semiCiclo en milisegundos
  digitalWrite(pulseOut, HIGH);
  delay(tiempo / 2); //semiciclo positivo
  digitalWrite(pulseOut, LOW);
  delay(tiempo / 2); //semiciclo negativo
}
//---ACELERACION_DEL_TREN-----------------------------------------------------------------------------
void acelerar()
{
  for (i = 1; i < countMax; i++)
  { //se calculo que aproximadamente los 928hz se alcanzan los 100km/h
    senalOut();
    velMax();
    lecturasEnSubida05();
    lecturasEnSubida6();
  }
}
//---DESACELERACION_DEL_TREN--------------------------------------------------------------------------
void desacelerar()
{
  for (i = countMax; i >= 1; i--)
  {
    senalOut();
    velMax();
    lecturasEnBajada6();
    lecturasEnBajada05();
  }
}
//---VISUALIZAR_VELOCIDAD-----------------------------------------------------------------------------
void velMax()
{
  vel = ((i / var4) * PI * var1 * var2 / var3);
  //Serial.println(vel);
}
//---ACCIONES_EN_ESTACION-----------------------------------------------------------------------------
void enEstacion()
{
  mensaje006();
  digitalWrite(puerta, LOW);
  delay(4500);
  digitalWrite(luz, HIGH);
  delay(2000);
  digitalWrite(sirena, HIGH);
  delay(2500);
  digitalWrite(sirena, LOW);
  digitalWrite(luz, LOW);
  digitalWrite(puerta, HIGH);
  delay(1000);
}
//---FUNCIONES_POR_ERRORES----------------------------------------------------------------------------
void error_001()
{ //error 1 cuando X1_VT_05 debiera ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    digitalWrite(error, HIGH);
    delay(500);
    digitalWrite(error, LOW);
    delay(500);
  }
  m = m + 1;
  countError();
}
void error_002()
{ //error 2 cuando X1_VT_6 deberia ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 2; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
void error_003()
{ //error 3 cuando X7_VT_05 deberia ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 3; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
void error_004()
{ //error 4 cuando X7_VT_6 deberia ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 4; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
void error_005()
{ //error 5 cuando X6_VT_05 deberia ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 5; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
void error_006()
{ //error 6 cuando X6_VT_6 deberia ser HIGH
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 6; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
void error_007()
{ //error 7 Ninguna lectura cambia
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j < 7; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m + 1;
  countError();
}
//---LECTURAS-------------------------------------------------------------------------------------------------------------------------------------------
void lecturasEnSubida05()
{
  while (vel > vel_1)
  { //Cuando la velocidad calculada es MAYOR a 0.5KM/h y...
    int a = digitalRead(X1_VT_05);
    int b = digitalRead(X7_VT_05);
    int c = digitalRead(X6_VT_05);
    if (a == HIGH && b == HIGH && c == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 1
      mensajeError011();
      serial05();
      error_001();
      break;
    }
    else if (b == HIGH && a == LOW && c == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 3
      mensajeError021();
      serial05();
      error_003();
      break;
    }
    else if (c == HIGH && a == LOW && b == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 5
      mensajeError031();
      serial05();
      error_005();
      break;
    }
    else if (a == HIGH && b == HIGH && c == LOW)
    {
      mensajeError015();
      serial05();
      error_007();
      break;
    }
    else if (b == LOW && a == HIGH && c == HIGH)
    {
      mensajeError025();
      serial05();
      error_007();
      break;
    }
    else if (a == LOW && b == HIGH && c == HIGH)
    {
      mensajeError035();
      serial05();
      error_007();
      break;
    }
    else if (a == HIGH && b == HIGH && c == HIGH)
    {
      mensajeError051();
      serial05();
      error_007();
      break;
    }
    else
    {
      break;
    }
    break;
  }
}
void lecturasEnSubida6()
{
  while (vel > vel_2)
  { //Cuando la velocidad calculada es MENOR a 6km/h y...
    int a = digitalRead(X1_VT_6);
    int b = digitalRead(X7_VT_6);
    int c = digitalRead(X6_VT_6);
    if (a == HIGH && b == LOW && c == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      mensajeError012();
      serial6();
      error_002();
      break;
    }
    else if (b == HIGH && a == LOW && c == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 4
      mensajeError022();
      serial6();
      error_004();
      break;
    }
    else if (c == HIGH && a == LOW && b == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 6
      mensajeError032();
      serial6();
      error_006();
      break;
    }
    else if (a == HIGH && b == HIGH && c == LOW)
    {
      mensajeError016();
      serial6();
      error_007();
      break;
    }
    else if (b == LOW && a == HIGH && c == HIGH)
    {
      mensajeError026();
      serial6();
      error_007();
      break;
    }
    else if (a == LOW && b == HIGH && c == HIGH)
    {
      mensajeError036();
      serial6();
      error_007();
      break;
    }
    else if (a == HIGH && b == HIGH && c == HIGH)
    {
      mensajeError052();
      serial6();
      error_007();
      break;
    }
    else
    {
      break;
    }
    break;
  }
}
void lecturasEnBajada05()
{
  while (vel <= vel_3)
  { //Si la velocidad calculada es MENOR a 0.1KM/h y...
    int a = digitalRead(X1_VT_05);
    int b = digitalRead(X7_VT_05);
    int c = digitalRead(X6_VT_05);
    if (a == LOW && b == HIGH && c == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 1
      mensajeError013();
      serial05();
      error_001();
      break;
    }
    else if (b == LOW && a == HIGH && c == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 3
      mensajeError023();
      serial05();
      error_003();
      break;
    }
    else if (c == LOW && a == HIGH && b == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 5
      mensajeError033();
      serial05();
      error_005();
      break;
    }
    else if (a == LOW && b == LOW && c == HIGH)
    {
      mensajeError017();
      serial05();
      error_007();
      break;
    }
    else if (b == HIGH && a == LOW && c == LOW)
    {
      mensajeError027();
      serial05();
      error_007();
      break;
    }
    else if (a == HIGH && b == LOW && c == LOW)
    {
      mensajeError037();
      serial05();
      error_007();
      break;
    }
    else if (a == LOW && b == LOW && c == LOW)
    {
      mensajeError053();
      serial05();
      error_007();
      break;
    }
    else
    {
      break;
    }
    break;
  }
}
void lecturasEnBajada6()
{
  while (vel <= vel_4)
  { //Si la velocidad calculada es MENOR a 6km/h y...
    int a = digitalRead(X1_VT_6);
    int b = digitalRead(X7_VT_6);
    int c = digitalRead(X6_VT_6);
    if (a == LOW && b == c == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      mensajeError014();
      serial6();
      error_002();
      break;
    }
    else if (b == LOW && a == HIGH && c == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      mensajeError024();
      serial6();
      error_004();
      break;
    }
    else if (c == LOW && a == HIGH && b == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      mensajeError034();
      serial6();
      error_006();
      break;
    }
    else if (a == LOW && b == LOW && c == HIGH)
    {
      mensajeError018();
      serial6();
      error_007();
      break;
    }
    else if (a == LOW && c == LOW && b == HIGH)
    {
      mensajeError028();
      serial6();
      error_007();
      break;
    }
    else if (a == HIGH && b == LOW && c == LOW)
    {
      mensajeError038();
      serial6();
      error_007();
      break;
    }
    else if (a == LOW && b == LOW && c == LOW)
    {
      mensajeError054();
      serial6();
      error_007();
      break;
    }
    else
    {
      break;
    }
    break;
  }
}
void powerOn()
{
  delay(1000);
  lcd.clear();
  Serial.println("EVR: ON");
  lcd.setCursor(0, 1);
  lcd.print("EVR: ON     ");
  digitalWrite(powerEVR, HIGH);
}
void powerOff()
{
  delay(5000);
  mPowerOff();
  digitalWrite(powerEVR, LOW);
  delay(50000);
}
void serial05()
{
  Serial.println("VT_05");
  Serial.println(digitalRead(X1_VT_05));
  Serial.println(digitalRead(X7_VT_05));
  Serial.println(digitalRead(X6_VT_05));
}
void serial6()
{
  Serial.println("VT_06");
  Serial.println(digitalRead(X1_VT_6));
  Serial.println(digitalRead(X7_VT_6));
  Serial.println(digitalRead(X6_VT_6));
}
void infoViaje()
{
  Serial.print("Ciclo: ");
  Serial.print(l);
  Serial.print(" viaje Nº ");
  Serial.println(k);
}
void testEVR()
{
  star();
  for (l = 1; l < 49; l++)
  {
    l = l + m;
    powerOn();
    delay(7000);
    instancia01();
    instancia02();
    for (k = 1; k < 28; k++)
    {
      infoViaje();
      viaje();
    }
    powerOff();
  }
  Serial.println("FIN");
}
void countError()
{
  do
  {
    n = 5;
    mensajerErroreEncontrados();
    if (m < n)
    {
      powerOff();
      testEVR();
      break;
    }
    else
    {
      endTestEVRForError();
      break;
    }
    break;
  } while (true);
}
void displayOn()
{
  delay(1000);
}
void displayOff()
{
  delay(1500);
}
void endTestEVRForError()
{
  Serial.print("Revisar\tHistorial\t");
  Serial.print(m);
  Serial.println("\terrores\tencontrados");
  powerOff();
  Serial.println("Fin\tde\tla\tprueba");
  Serial.println("FIN");
  delay(500);
  exit(0);
}
void titulo()
{
  mCiclo();
  mViaje();
  lcd.setCursor(0, 1);
}
void mensaje001()
{
  Serial.println("1 OK");
  lcd.setCursor(0, 2);
  lcd.print("1 OK                ");
}
void mensaje002()
{
  Serial.println("1 PRECAUCION");
  lcd.setCursor(0, 2);
  lcd.print("1 PRECAUCION        ");
}
void mensaje003()
{
  Serial.println("Error instancia 1, tarjeta X1 no responde como se espera");
  lcd.setCursor(0, 2);
  lcd.print("Error instancia 1, ");
  lcd.setCursor(0, 3);
  lcd.print("Tarjeta X1          ");
}
void mensaje004()
{
  Serial.println("Error instancia 1, tarjeta X6 no responde como se espera");
  lcd.setCursor(0, 2);
  lcd.print("Error instancia 1,  ");
  lcd.setCursor(0, 3);
  lcd.print("Tarjeta X6          ");
}
void mensaje005()
{
  Serial.println("2 OK");
  lcd.setCursor(0, 3);
  lcd.print("2 OK                ");
  delay(5000);
}
void mensaje006()
{
  Serial.println("acciones en estacion");
  titulo();
  lcd.print("acciones en");
  lcd.setCursor(0, 2);
  lcd.print("estacion");
}
void mensaje007()
{
  Serial.println("TREN sale de ESTACIÓN");
  titulo();
  lcd.print("TREN sale de");
  lcd.setCursor(0, 2);
  lcd.print("ESTACION");
}
void mensaje008()
{
  Serial.println("VELOCIDAD MAXIMA");
  titulo();
  lcd.print("VELOCIDAD MAXIMA");
}
void mensaje009()
{
  Serial.println("TREN ha llegado a DESTINO");
  titulo();
  lcd.print("TREN la llegado");
  lcd.setCursor(0, 2);
  lcd.print("a DESTINO");
}
void mCiclo()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ciclo:");
  lcd.setCursor(6, 0);
  lcd.print(l);
}
void mViaje()
{
  lcd.setCursor(9, 0);
  lcd.print("Viaje N:");
  lcd.setCursor(17, 0);
  lcd.print(k);
}
void mensajeError011()
{
  Serial.println("ERROR_011: X1_VT_05 = 1");
  titulo();
  lcd.print("ERROR_011:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 1");
}
void mensajeError012()
{
  Serial.println("ERROR_012: la variable X1_VT_6 = 1");
  titulo();
  lcd.print("ERROR_012:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_06 = 1");
}
void mensajeError013()
{
  Serial.println("ERROR_013: X1_VT_05 = 0");
  titulo();
  lcd.print("ERROR_013:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 0");
}
void mensajeError014()
{
  Serial.println("ERROR_014: X1_VT_6 = 0");
  titulo();
  lcd.print("ERROR_014:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_6 = 0");
}
void mensajeError021()
{
  Serial.println("ERROR_021: X7_VT_05 = 1");
  titulo();
  lcd.print("ERROR_021:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_05 = 1");
}
void mensajeError022()
{
  Serial.println("ERROR_022: X7_VT_6 = 1");
  titulo();
  lcd.print("ERROR_022:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6 = 1");
}
void mensajeError023()
{
  Serial.println("ERROR_023: X7_VT_05 = 0");
  titulo();
  lcd.print("ERROR_023:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_05 = 0");
}
void mensajeError024()
{
  Serial.println("ERROR_024: X7_VT_6 = 0");
  titulo();
  lcd.print("ERROR_024:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6 = 0");
}
void mensajeError031()
{
  Serial.println("ERROR_031: X6_VT_05 = 1");
  titulo();
  lcd.print("ERROR_031:");
  lcd.setCursor(1, 2);
  lcd.print("X6_VT_05 = 1");
}
void mensajeError032()
{
  Serial.println("ERROR_032: la variable X6_VT_6 = 1");
  titulo();
  lcd.print("ERROR_032:");
  lcd.setCursor(1, 2);
  lcd.print("X6_VT_6 = 1");
}
void mensajeError033()
{
  Serial.println("ERROR_033: X6_VT_05 = 0");
  titulo();
  lcd.print("ERROR_033:");
  lcd.setCursor(1, 2);
  lcd.print("X6_VT_05 = 0");
}
void mensajeError034()
{
  Serial.println("ERROR_034: X6_VT_6 = 0");
  titulo();
  lcd.print("ERROR_034:");
  lcd.setCursor(1, 2);
  lcd.print("X6_VT_6 = 0");
}
void mensajeError015()
{
  Serial.println("ERROR_015: X1_VT_05 = 1 Y X7_VT_05 = 1");
  titulo();
  lcd.print("ERROR_015:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05=1");
  lcd.setCursor(1, 3);
  lcd.print("X7_VT_05=1");
}
void mensajeError025()
{
  Serial.println("ERROR_025: X1_VT_05 = 1 Y X6_VT_05 = 1");
  titulo();
  lcd.print("ERROR_025:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_05 = 1");
}
void mensajeError035()
{
  Serial.println("ERROR_035: X7_VT_05 = 1 Y X6_VT_05 = 1");
  titulo();
  lcd.print("ERROR_035:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_05 = 1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_05 = 1");
}
void mensajeError051()
{
  Serial.println("ERROR_051: X1_VT_05 = 1 Y X7_VT_05 = 1 Y X6_VT_05 = 1");
  titulo();
  lcd.print("ERROR_051:X1_VT_05=1");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_05=1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_06=1");
}
void mensajeError016()
{
  Serial.println("ERROR_016: X1_VT_6 = 1 Y X7_VT_6 = 1");
  titulo();
  lcd.print("ERROR_016:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_6=1");
  lcd.setCursor(1, 3);
  lcd.print("X7_VT_6=1");
}
void mensajeError026()
{
  Serial.println("ERROR_026: X1_VT_6 = 1 Y X6_VT_6 = 1");
  titulo();
  lcd.print("ERROR_026:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_6 = 1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6 = 1");
}
void mensajeError036()
{
  Serial.println("ERROR_036: X7_VT_6 = 1 Y X6_VT_6 = 1");
  titulo();
  lcd.print("ERROR_036:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6 = 1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6 = 1");
}
void mensajeError052()
{
  Serial.println("ERROR_052: X1_VT_6 = 1 Y X7_VT_6 = 1 Y X6_VT_6 = 1");
  titulo();
  lcd.print("ERROR_052:X1_VT_6=1");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6=1");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6=1");
}
void mensajeError017()
{
  Serial.println("ERROR_017: X1_VT_05 = 0 Y X7_VT_05 = 0");
  titulo();
  lcd.print("ERROR_017:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 0");
  lcd.setCursor(1, 3);
  lcd.print("X7_VT_05 = 0");
}
void mensajeError027()
{
  Serial.println("ERROR_027: X1_VT_05 = 0 Y X6_VT_05 = 0");
  titulo();
  lcd.print("ERROR_027:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_05 = 0");
}
void mensajeError037()
{
  Serial.println("ERROR_037: X7_VT_05 = 0 Y X6_VT_05 = 0");
  titulo();
  lcd.print("ERROR_027:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_05 = 0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_05 = 0");
}
void mensajeError053()
{
  Serial.println("ERROR_053: X1_VT_05 = 0 Y X7_VT_05 = 0 Y X6_VT_05 = 0");
  titulo();
  lcd.print("ERROR_053:X1_VT_05=0");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_05=0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_05=0");
}
void mensajeError018()
{
  Serial.println("ERROR_018: X1_VT_6 = 0 Y X7_VT_6 = 0");
  titulo();
  lcd.print("ERROR_018:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_6=0");
  lcd.setCursor(1, 3);
  lcd.print("X7_VT_6=0");
}
void mensajeError028()
{
  Serial.println("ERROR_028: X1_VT_6 = 0 Y X6_VT_6 = 0");
  titulo();
  lcd.print("ERROR_028:");
  lcd.setCursor(1, 2);
  lcd.print("X1_VT_6=0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6=0");
}
void mensajeError038()
{
  Serial.println("ERROR_038: X7_VT_6 = 0 Y X6_VT_6 = 0");
  titulo();
  lcd.print("ERROR_038:");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6=0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6=0");
}
void mensajeError054()
{
  Serial.println("ERROR_054: X1_VT_05 = 0 Y X7_VT_05 = 0 Y X6_VT_05 = 0");
  titulo();
  lcd.print("ERROR_054:X1_VT_6=0");
  lcd.setCursor(1, 2);
  lcd.print("X7_VT_6=0");
  lcd.setCursor(1, 3);
  lcd.print("X6_VT_6=0");
}
void mensajerErroreEncontrados()
{
  Serial.print("Errores encontrados: ");
  Serial.println(m);
}
void mPowerOff()
{
  Serial.println("EVR: OFF");
  titulo();
  lcd.print("EVR: OFF");
  lcd.setCursor(0, 2);
  lcd.print("Errores Encontrados:");
  lcd.setCursor(3, 3);
  lcd.print(m);
}
void manualTestEVR()
{
  mensajeManualTest();
  if (seleccionManual05 == 1 && seleccionManual6 == 1 && seleccionManualMax == 1)
  {
    Serial.println('Seleccione velocidades\nV>0,5km\tV>6km\tV=MAX\nSumando actuadores');
    lcd.setCursor(0, 1);
    lcd.print('Sume Velcidades');
  }
  else if (seleccionManual05 == 0 && seleccionManual6 == 1 && seleccionManualMax == 1)
  {
    mensajeFrecuenciaManual05();
    frecuenciaManual05();
  }
  else if (seleccionManual05 == 0 && seleccionManual6 == 0 && seleccionManualMax == 1)
  {
    mensajeFrecuenciaManual6();
    frecuenciaManual6();
  }
  else if (seleccionManual05 == 0 && seleccionManual6 == 0 && seleccionManualMax == 0)
  {
    mensajeFrecuenciaManualMax();
    frecuenciaManualMax();
  }
  else if (seleccionManual05 == 0 && seleccionManual6 == 1 && seleccionManualMax == 0 || seleccionManual05 == 1 && seleccionManual6 == 0 && seleccionManualMax == 0 || seleccionManual05 == 1 && seleccionManual6 == 0 && seleccionManualMax == 1 || seleccionManual05 == 1 && seleccionManual6 == 1 && seleccionManualMax == 0)
  {
    lcd.clear();
    lcd.print('Seleccione\nCombinacion\nValida');
  }
}
void frecuenciaManual05()
{
  do
  {
    int timePulse(26);
    for (;;)
    {
      digitalWrite(pulseOut, HIGH);
      delay(timePulse);
      digitalWrite(pulseOut, LOW);
      delay(timePulse);
    }
    break;
  } while (true);
}
void frecuenciaManual6()
{
  do
  {
    int timePulse(5300);
    for (;;)
    {
      digitalWrite(pulseOut, HIGH);
      delayMicroseconds(timePulse);
      digitalWrite(pulseOut, LOW);
      delayMicroseconds(timePulse);
      break;
    }
  } while (true);
}
void frecuenciaManualMax()
{
  do
  {
    int timePulse(530);
    for (;;)
    {
      digitalWrite(pulseOut, HIGH);
      delayMicroseconds(timePulse);
      digitalWrite(pulseOut, LOW);
      delayMicroseconds(timePulse);
      break;
    }
  } while (true);
}
void mensajeManualTest00()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print('Manual Test EVR');
}
void mensajeManualTest01()
{
  lcd.setCursor(0, 1);
  lcd.print('Velocidad Manual:');
  lcd.setCursor(0, 2);
}
void mensajeManualTest()
{
  Serial.println('\tPrueba\tManual\tEVR\n');
  mensajeManualTest00();
  mensajeSelectores();
}
void mensajeFrecuenciaManual05()
{
  mensajeManualTest00();
  mensajeManualTest01();
  lcd.print('Velocidad > 0,5');
  mensajeSelectores();
}
void mensajeFrecuenciaManual6()
{
  mensajeManualTest00();
  mensajeManualTest01();
  lcd.print('Velocidad > 6');
  mensajeSelectores();
}
void mensajeFrecuenciaManualMax()
{
  mensajeManualTest00();
  mensajeManualTest01();
  lcd.print('Velocidad = MAX');
  mensajeSelectores();
}
void mensajeSelectores()
{
  lcd.setCursor(0, 3);
  Serial.println("Seleccion Manual velocidad 0,5");
  Serial.println(seleccionManual05);
  lcd.print(seleccionManual05);
  lcd.setCursor(3, 3);
  Serial.println("Seleccion Manual velocidad 6");
  Serial.println(seleccionManual6);
  lcd.print(seleccionManual6);
  lcd.setCursor(6, 3);
  Serial.println("Seleccion Manual velocidad MAX");
  Serial.println(seleccionManualMax);
  lcd.print(seleccionManualMax);
}