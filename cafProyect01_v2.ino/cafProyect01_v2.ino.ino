int salida=3;

void setup() {
  // put your setup code here, to run once:
 pinMode(salida,OUTPUT);
}

void loop() {
  digitalWrite(salida,HIGH);
  delay(1);
  digitalWrite(salida,LOW);
  delay(1);
}
