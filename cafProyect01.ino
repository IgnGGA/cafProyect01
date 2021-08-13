int error = 2;     //variable destinada a dar indicación de ERROR a causa de alguna condición incumplida
int pulseOut = 3;  //salida pulsos que simulan velocidad, se selecciona el pin11 por sus cualidades de salida PWM
int powerEVR = 5;  //enciende el EVR con 72V
int luz = 4;       //indicador que representa LUZ indicadora del TREN
int sirena = 6;    //indicador que representa la SIRENA o GRABACIÓN del tren
int puerta = 7;    //indicador que representa las PUERTAS del TREN
int X1_VT_6 = 8;   //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 6
int X7_VT_6 = 9;   //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 6
int X6_VT_6 = 10;  //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 6
int X1_VT_05 = 11; //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 05
int X7_VT_05 = 12; //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 05
int X6_VT_05 = 13; //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 05
float tiempo;      //tiempo que estara en funcion de la freciencia
float i, j;        //contadores
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
void setup()
{
  Serial.begin(9600); //velocidad de lectura y escritura del arduino.
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
  pinMode(A0, OUTPUT); //Se usaran las entradas analogicas como salidas digitales
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop()
{
  testEVR();
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
      Serial.println("1 OK");
      break;
    }
    else if ((a == 1 && b == 1 && c == 1) && (d == 1 || e == 1 || f == 1))
    {
      serial05();
      serial6();
      delay(14000);
      Serial.println("1 PRECAUCION");
      break;
    }
    else if ((a == 0 || b == 0) && c == 1)
    {
      Serial.println("Error instancia 1, tarjeta X1 no responde como se espera");
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      serial05();
      serial6();
      error_007;
      break;
    }
    else if (a == 1 && b == 1 && c == 0)
    {
      Serial.println("Error instancia 1, tarjeta X6 no responde como se espera");
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
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
    Serial.println("2 OK");
    break;
  } while (true);
}
//------------viaje-----------------------------------------------------------------------------------
void viaje()
{
  digitalWrite(A4, HIGH);
  //digitalWrite(cc, LOW);
  enEstacion();
  Serial.println("TREN sale de ESTACIÓN");
  acelerar();
  Serial.println("VELOCIDAD MAXIMA");
  desacelerar();
  Serial.println("TREN ha llegado a DESTINO");
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
  Serial.println("acciones en estacion");
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
  m = m+1;
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
  m = m+1;
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
  m = m+1;
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
  m = m+1;
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
  m = m+1;
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
  m = m+1;
  countError();
}
void error_007()
{ //error 7 Ninguna lectura cambia
  int a = 0;
  for (a; a < 10; a++)
  {
    for (j = 0; j = 7; j++)
    {
      digitalWrite(error, HIGH);
      delay(500);
      digitalWrite(error, LOW);
      delay(500);
    }
    delay(1000);
  }
  m = m+1;
  countError();
}
//---LECTURAS-------------------------------------------------------------------------------------------------------------------------------------------
void lecturasEnSubida05()
{
  while (vel > vel_1)
  { //Cuando la velocidad calculada es MAYOR a 0.5KM/h y...
    if (digitalRead(X1_VT_05) == HIGH)
    { //Si la lectura es 0 digital, se ejecuta el error 1
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_011: X1_VT_05 = 1");
      serial05();
      error_001();
      break;
    }
    else if (digitalRead(X7_VT_05) == HIGH)
    { //Si la lectura es 0 digital, se ejecuta el error 3
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_021: X7_VT_05 = 1");
      serial05();
      error_003();
      break;
    }
    else if (digitalRead(X6_VT_05) == HIGH)
    { //Si la lectura es 0 digital, se ejecuta el error 5
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_031: X6_VT_05 = 1");
      serial05();
      error_005();
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
    if (digitalRead(X1_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_012: la variable X1_VT_6 = 1");
      serial6();
      error_002();
      break;
    }
    else if (digitalRead(X7_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 4
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_022: X7_VT_6 = 1");
      serial6();
      error_004();
      break;
    }
    else if (digitalRead(X6_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 6
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_032: la variable X6_VT_6 = 1");
      serial6();
      error_006();
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
    if (digitalRead(X1_VT_05) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 1
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      Serial.println("ERROR_013: X1_VT_05 = 0");
      serial05();
      error_001();
      break;
    }
    else if (digitalRead(X7_VT_05) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 3
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      Serial.println("ERROR_023: X7_VT_05 = 0");
      serial05();
      error_003();
      break;
    }
    else if (digitalRead(X6_VT_05) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 5
      digitalWrite(A0, HIGH);
      digitalWrite(A1, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      Serial.println("ERROR_033: X6_VT_05 = 0");
      serial05();
      error_005();
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
    if (digitalRead(X1_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0, LOW);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      Serial.println("ERROR_014: X1_VT_6 = 0");
      serial6();
      error_002();
      break;
    }
    else if (digitalRead(X7_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0, HIGH);
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(A3, HIGH);
      Serial.println("ERROR_024: X7_VT_6 = 0");
      serial6();
      error_004();
      break;
    }
    else if (digitalRead(X6_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0, LOW);
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(A3, HIGH);
      Serial.println("ERROR_034: X6_VT_6 = 0");
      serial6();
      error_006();
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
  Serial.println("EVR: ON");
  digitalWrite(powerEVR, HIGH);
}
void powerOff()
{
  delay(5000);
  Serial.println("EVR: OFF");
  digitalWrite(powerEVR, LOW);
  delay(60000);
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
  for (l = 1; l<29; l++)
  {
    l=l+m;
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
}
void countError()
{
  do{
  n=5;
  Serial.print("Errores encontrados: ");
  Serial.println(m);
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
}
  while(true);
}
void displayOn()
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, HIGH);
  delay(1000);
}
void displayOff()
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  delay(1500);
}
void endTestEVRForError()
{
  Serial.print("Revisar\tHistorial\t");
  Serial.print(m);
  Serial.println("\terrores\tencontrados");
  powerOff();
  Serial.println("Fin\tde\tla\tprueba");
  delay(500);
  Serial.print("FIN");
  exit(0);
}
