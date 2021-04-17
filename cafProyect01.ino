//---DEFINICION_PINES--------------------------------------------------------------------------------------------------------------------
int cc = 2;       //Confirmación Cierre de Puertas.
int pulseOut = 3; //salida pulsos que simulan velocidad, se selecciona el pin11 por sus cualidades de salida PWM
int luz = 4;      //indicador que representa LUZ indicadora del TREN
int sirena = 5;   //indicador que representa la SIRENA o GRABACIÓN del tren
int puerta = 6;   //indicador que representa las PUERTAS del TREN
int X1_VT_6 = 10; //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 6
int X1_VT_05 = 7; //lectura de variable provimiente de tarjeta X1 para rele control de velocidad 05
int X7_VT_6 = 11; //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 6
int X7_VT_05 = 8; //lectura de variable provimiente de tarjeta X7 para rele control de velocidad 05
int X6_VT_6 = 12; //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 6
int X6_VT_05 = 9; //lectura de variable provimiente de tarjeta X6 para rele control de velocidad 05
int error = 13;   //variable destinada a dar indicación de ERROR a causa de alguna condición incumplida
//---DEFINICION_VARIABLES----------------------------------------------------------------------------------------------------------------
int countMax = 2320;      //es 2.5 veces la frecuencia maxima
float tiempo;             //tiempo que estara en funcion de la freciencia
float i, j;               //contadores
float vel;                //valor de la velocidad en funcion de la frecuencia
const float vel_1 = 0.5;  //velocidad para apagar el rele 1
const float vel_2 = 6;    //velocidad para apagar el rele 2
const int z = 100;        //ventanas de la rueda
const float var1 = 0.953; //diametro de la rueda en metros
const float var2 = 3.6;   //constante de velocidad del TREN
const float var3 = 100;   //ventanas de la rueda

void setup()
{
  pinMode(pulseOut, OUTPUT);
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
  pinMode(A3,OUTPUT);
}

void loop()
{
  digitalWrite(cc, LOW);
  enEstacion();
  acelerar();
  desacelerar();
}
//------------FUNCIONES-------------------------------------------------------------------------------
//---SALIDA_SEÑAL_CUADRADA----------------------------------------------------------------------------
void senalOut()
{                                 //Funcion que se encarga de generar los estados de los semiciclos correspondientes.
  tiempo = (1000 / (i / (1.25))); //tiempo de duracion de cada semiCiclo en milisegundos
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
  vel = ((i / 2.5) * PI * var1 * var2 / z);
  Serial.println(vel);
}
//---ACCIONES_EN_ESTACION-----------------------------------------------------------------------------
void enEstacion()
{
  digitalWrite(puerta, LOW);
  delay(4500);
  digitalWrite(luz, HIGH);
  delay(2000);
  digitalWrite(sirena, HIGH);
  delay(2500);
  digitalWrite(sirena, LOW);
  digitalWrite(luz, LOW);
  digitalWrite(puerta, HIGH);
  digitalWrite(cc, HIGH);
  delay(1000);
}
//---FUNCIONES_POR_ERRORES----------------------------------------------------------------------------
void error_001()
{ //error 1 cuando X1_VT_05 debiera ser HIGH
  for (;;)
  {
    digitalWrite(error, HIGH);
    delay(500);
    digitalWrite(error, LOW);
    delay(500);
  }
}
void error_002()
{ //error 2 cuando X1_VT_6 deberia ser HIGH
  for (;;)
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
}
void error_003()
{ //error 3 cuando X7_VT_05 deberia ser HIGH
  for (;;)
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
}
void error_004()
{ //error 4 cuando X7_VT_6 deberia ser HIGH
  for (;;)
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
}
void error_005()
{ //error 5 cuando X6_VT_05 deberia ser HIGH
  for (;;)
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
}
void error_006()
{ //error 6 cuando X6_VT_6 deberia ser HIGH
  for (;;)
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
}
void error_007()
{ //error 7 Ninguna lectura cambia
  for (;;)
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
}
//---LECTURAS-------------------------------------------------------------------------------------------------------------------------------------------
void lecturasEnSubida05()
{
  while (vel > vel_1)
  { //Cuando la velocidad calculada es MAYOR a 0.5KM/h y...
    if (digitalRead(X1_VT_05) == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 1
      digitalWrite(A0,HIGH);
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      digitalWrite(A3,LOW);
      error_001();
      break;
    }
    else if (digitalRead(X7_VT_05) == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 3
      digitalWrite(A0,LOW);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,LOW);
      digitalWrite(A3,LOW);
      error_003();
      break;
    }
    else if (digitalRead(X6_VT_05) == LOW)
    { //Si la lectura es 0 digital, se ejecuta el error 5
      digitalWrite(A0,HIGH);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,LOW);
      digitalWrite(A3,LOW);
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
    if (digitalRead(X1_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0,LOW);
      digitalWrite(A1,LOW);
      digitalWrite(A2,HIGH);
      digitalWrite(A3,LOW);
      error_002();
      break;
    }
    else if (digitalRead(X7_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 4
      digitalWrite(A0,HIGH);
      digitalWrite(A1,LOW);
      digitalWrite(A2,HIGH);
      digitalWrite(A3,LOW);
      error_004();
      break;
    }
    else if (digitalRead(X6_VT_6) == LOW)
    { //Si la lectura es 1 digital, se ejecuta el error 6
      digitalWrite(A0,LOW);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,HIGH);
      digitalWrite(A3,LOW);
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
  while (vel <= vel_1)
  { //Si la velocidad calculada es MENOR a 0.5KM/h y...
    if (digitalRead(X1_VT_05) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 1
      digitalWrite(A0,HIGH);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,HIGH);
      digitalWrite(A3,LOW);
      error_001();
      break;
    }
    else if (digitalRead(X7_VT_05) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 3
      digitalWrite(A0,LOW);
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      error_003();
      break;
    }
    else if (digitalRead(X6_VT_05) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 5
      digitalWrite(A0,HIGH);
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      digitalWrite(A3,HIGH);
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
  while (vel <= vel_2)
  { //Si la velocidad calculada es MENOR a 6km/h y...
    if (digitalRead(X1_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0,LOW);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,LOW);
      digitalWrite(A3,HIGH);
      error_002();
      break;
    }
    else if (digitalRead(X7_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0,HIGH);
      digitalWrite(A1,HIGH);
      digitalWrite(A2,LOW);
      digitalWrite(A3,HIGH);
      error_004();
      break;
    }
    else if (digitalRead(X6_VT_6) == HIGH)
    { //Si la lectura es 1 digital, se ejecuta el error 2
      digitalWrite(A0,LOW);
      digitalWrite(A1,LOW);
      digitalWrite(A2,HIGH);
      digitalWrite(A3,HIGH);
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
//---NOTAS--------------------------------------------------------------------------------------------
//considerar que la grafica de velocidad que se dibuja (o comprende) es lineal, por lo tanto, su aceleración es constante mientras que a travez
//de una ecuacion de posición en funcion del tiempo es parabolico, esto considerando el M.R.U.A. (movimiento rectilineo uniforme acelerado).
//El tiempo aproximado desde la salida del tren hasta la llegada a la estacion toma aproximadamente 1:09 minutos.
//Se cambio la proporcion de la frecuencia de 2.5 a 1.25 veces la frecuencia, esto debido a que el programa toma mas tiempo en las iteraciones.
//los casos de errores evalua una tarjeta a la vez, queda pendiente versionar casos de pruebas para multiples combinaciones de tarjetas.
