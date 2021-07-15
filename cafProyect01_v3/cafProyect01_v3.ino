int pulseOut = 3;
int tiempoSemiCiclo1 = 10778;//microsegundos
int tiempoSemiCiclo2 = 2694;
int tiempoSemiCiclo3 = 1347;
int tiempoSemiCiclo4 = 897;
int tiempoSemiCiclo5 = 673;
int tiempoSemiCiclo6 = 538;

void setup() {
  pinMode (pulseOut, OUTPUT);
}

void loop() {
  aceleracion();
  desaceleracion();

}
void velocidad0(){
  digitalWrite(pulseOut, LOW);
  delay(5000);
}
void velocidad1(){
  int i=0;
  for(i=0;i<231;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo1);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo1);
  }
}
void velocidad2(){
  int i=0;
  for(i=0;i<928;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo2);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo2);
  }
}
void velocidad3(){
  int i=0;
  for(i=0;i<1856;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo3);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo3);
  }
}
void velocidad4(){
  int i=0;
  for(i=0;i<2787;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo4);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo4);
  }
}
void velocidad5(){
  int i=0;
  for(i=0;i<3711;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo5);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo5);
  }
}
void velocidad6(){
  int i=0;
  for(i=0;i<4639;i++){
    digitalWrite(pulseOut, LOW);
    delayMicroseconds(tiempoSemiCiclo6);
    digitalWrite(pulseOut, HIGH);
    delayMicroseconds(tiempoSemiCiclo6);
  }
}
void aceleracion(){
  velocidad0();
  velocidad1();
  velocidad2();
  velocidad3();
  velocidad4();
  velocidad5();
  velocidad6();
}
void desaceleracion(){
  velocidad6();
  velocidad5();
  velocidad4();
  velocidad3();
  velocidad2();
  velocidad1();
  velocidad0();
}
