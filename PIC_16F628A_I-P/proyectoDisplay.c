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

#include <lcd.c>              /*libreria para usar el lcd*/
#define LCD_ENABLE_PIN PIN_B0 /* ASIGNAMOS EL PIN "B0" COMO SALIDA PARA E */
#define LCD_RS_PIN PIN_B1     /* ASIGNAMOS EL PIN "B1" COMO SALIDA PARA RS*/
#define LCD_RW_PIN PIN_B2     /* ASIGNAMOS EL PIN "B2" COMO SALIDA PARA RW*/
#define LCD_DATA4 PIN_B4      /* ASIGNAMOS EL PIN "B4" COMO SALIDA PARA D4*/
#define LCD_DATA5 PIN_B5      /* ASIGNAMOS EL PIN "B5" COMO SALIDA PARA D5*/
#define LCD_DATA6 PIN_B6      /* ASIGNAMOS EL PIN "B6" COMO SALIDA PARA D6*/
#define LCD_DATA7 PIN_B7      /* ASIGNAMOS EL PIN "B7" COMO SALIDA PARA D7*/

void main()
{
   output_high(pin_a4);
   delay_ms(500);
   output_low(pin_a4);
   lcd_init();
   lcd_putc("\f");
   do
   {
      lcd_gotoxy(1, 1);
      printf(lcd_putc, "Banco de Pruebas");
      lcd_gotoxy(1, 2);
      printf(lcd_putc, "EVR");
      //funcion de arduino lecturasEnSubida05
      if (input(PIN_A0) == 1 && input(PIN_A1) == 0 && input(PIN_A2) == 0 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_011: X1_VT_05");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 1 && input(PIN_A2) == 0 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_021: X7_VT_05");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 1 && input(PIN_A2) == 0 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_031: X6_VT_05");
         break;
      }
      //funcion de arduino lecturasEnSubida6
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 0 && input(PIN_A2) == 1 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_012: X1_VT_6");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 0 && input(PIN_A2) == 1 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_022: X7_VT_6");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 1 && input(PIN_A2) == 1 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_032: X6_VT_6");
         break;
      }
      //funcion de arduino lecturasEnBajada05
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 1 && input(PIN_A2) == 1 && input(PIN_A3) == 0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_013: X1_VT_05");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 0 && input(PIN_A2) == 0 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_023: X7_VT_05");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 0 && input(PIN_A2) == 0 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_033: X6_VT_05");
         break;
      }
      //funcion de arduino lecturasEnBajadas6
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 1 && input(PIN_A2) == 0 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_014: X1_VT_6");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 1 && input(PIN_A2) == 0 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_024: X7_VT_6");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 0 && input(PIN_A2) == 1 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_034: X6_VT_6");
         break;
      }
      //el la preparacion
      else if (input(PIN_A0) == 1 && input(PIN_A1) == 0 && input(PIN_A2) == 1 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_001: Preparacion X1");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1) == 1 && input(PIN_A2) == 1 && input(PIN_A3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1, 1);
         printf(lcd_putc, "ERROR!!!");
         lcd_gotoxy(1, 2);
         printf(lcd_putc, "ERROR_002: Preparacion X6");
         break;
      }
   } while (true);
}