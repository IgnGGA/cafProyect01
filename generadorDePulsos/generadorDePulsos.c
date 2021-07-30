#include <16F628A.h>
#use delay(clock = 4000000) /* OSCILADOR INTERNO */ //No aplica, ya que se activo el cristal interno
#FUSES NOWDT                                        /* No Watch Dog Timer*/
//#FUSES HS                     /* High speed Osc (> 4mhz)*/                     //Se usa con un cristal mayor al de 4Mhz, se recomienda usar el cristal interno
#FUSES PUT        /* Power Up Timer*/
#FUSES NOPROTECT  /* Code not protected from reading*/
#FUSES NOBROWNOUT /* No brownout reset*/
#FUSES NOMCLR     /* Master Clear pin disabled*/
#FUSES NOLVP      /* No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O*/
#FUSES NOCPD
#FUSES INTRC //Activacion uso cristal interno

#use fast_IO(A)
#use fast_IO(B)
byte i=0;

void main()
{

if (input(pin_a1)==1)//cuando la se�al que viene del ARDUINO sea igual a 1
{
   do{
      //velUp();
      //velDown();
      output_low(pin_b4);//vel0
      delay_ms(4000);
      for(i=0;i<186;i++){//vel1
         output_high(pin_b4);
         delay_us(10778);
         output_low(pin_b4);
         delay_us(10778);
      }
      for(i=0;i<742;i++){//vel2
         output_high(pin_b4);
         delay_us(2695);
         output_low(pin_b4);
         delay_us(2695);
      }
      for(i=0;i<1485;i++){//vel3
         output_high(pin_b4);
         delay_us(1347);
         output_low(pin_b4);
         delay_us(1347);
      }
      for(i=0;i<2230;i++){//vel4
         output_high(pin_b4);
         delay_us(897);
         output_low(pin_b4);
         delay_us(897);
      }
      for(i=0;i<2969;i++){
         output_high(pin_b4);
         delay_us(673);
         output_low(pin_b4);
         delay_us(673);
      }
      for(i=0;i<3711;i++){
         output_high(pin_b4);
         delay_us(539);
         output_low(pin_b4);
         delay_us(539);
      }
   } 
   while(true);
}
else if(input(pin_a1)==0){
   OUTPUT_B(0);
}
}

/*void vel0(void){//velocidad 0 absoluto por 4 segundos
   output_low(pin_b4);
   delay_ms(4000);
}*/
/*void vel1(void){//velocidad aprox 5km/h por 4 segundos
   for(i=0;i<186;i++){
   output_high(pin_b4);
   delay_us(10778);
   output_low(pin_b4);
   delay_us(10778);
   }
}*/
/*void vel2(void){//velocidad aprox 20km/h por 4 segundos
   for(i=0;i<742;i++){
   output_high(pin_b4);
   delay_us(2695);
   output_low(pin_b4);
   delay_us(2695);
   }
}*/
/*void vel3(void){//velocidad aprox 40km/h por 4 segundos
   for(i=0;i<1485;i++){
      output_high(pin_b4);
      delay_us(1347);
      output_low(pin_b4);
      delay_us(1347);
   }
}*/
/*void vel4(void){//velocidad aprox 60km/h por 4 segundos
   for(i=0;i<2230;i++){
      output_high(pin_b4);
      delay_us(897);
      output_low(pin_b4);
      delay_us(897);
   }
}*/
/*void vel5(void){//velocidad aprox 80KM/h por 4 segundos
   for(i=0;i<2969;i++){
      output_high(pin_b4);
      delay_us(673);
      output_low(pin_b4);
      delay_us(673);
   }
}*/
/*void vel6(void){//velocidad aprox 100km/h por 4 segudos
   for(i=0;i<3711;i++){
   output_high(pin_b4);
      delay_us(539);
      output_low(pin_b4);
      delay_us(539);
   }
}*/
/*void velUp(void){
   output_high(pin_b5);
   vel0();
   vel1();
   vel2();
   vel3();
   vel4();
   vel4();
   vel6();
}*/
/*void velDown(void){
   output_low(pin_b5);
   vel6();
   vel5();
   vel4();
   vel3();
   vel2();
   vel1();
   vel0();
}*/