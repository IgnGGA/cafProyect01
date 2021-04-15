#include <16F628A.h>
#fuses XT, NOWDT
#use delay(clock = 4000000)
#include <lcd.c>
#use standard_io(A)
#define LCD_DATA_PORT getenv("SFR:PORTB")
#define LCD_ENABLE_PIN  PIN_B0
#define LCD_RS_PIN      PIN_B1
#define LCD_RW_PIN      PIN_B2

void main()
{
   lcd_init();
   lcd_putc("\f");
   do{
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Esperando ERROR");
      lcd_gotoxy(1,2);
      printf(lcd_putc, "Registrador de Eventos");
      //funcion de arduino lecturasEnSubida05
      if      (input(PIN_A0) == 1 && input(PIN_A1)==0 && input(PIN_A2)==0 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_011: la variable X1_VT_05");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1)==1 && input(PIN_A2)==0 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_021: la variable X7_VT_05");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1)==1 && input(PIN_A2)==0 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_031: la variable X6_VT_05");
         break;
      }
      //funcion de arduino lecturasEnSubida6
      else if (input(PIN_A0) == 0 && input(PIN_A1)==0 && input(PIN_A2)==1 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_012: la variable X1_VT_6");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1)==0 && input(PIN_A2)==1 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_022: la variable X7_VT_6");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1)==1 && input(PIN_A2)==1 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_032: la variable X6_VT_6");
         break;
      }
      //funcion de arduino lecturasEnBajada05
      else if (input(PIN_A0) == 1 && input(PIN_A1)==1 && input(PIN_A2)==1 && input(PIN_A3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_013: la variable X7_VT_05");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1)==0 && input(PIN_A2)==0 && input(PIN_A3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_023: la variable X7_VT_05");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1)==0 && input(PIN_A2)==0 && input(PIN_A3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
          lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_033: la variable X6_VT_05");
         break;
      }
      //funcion de arduino lecturasEnBajadas6
      else if (input(PIN_A0) == 0 && input(PIN_A1)==1 && input(PIN_A2)==0 && input(PIN_A3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_014: la variable X7_VT_6");
         break;
      }
      else if (input(PIN_A0) == 1 && input(PIN_A1)==1 && input(PIN_A2)==0 && input(PIN_A3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_024: la variable X7_VT_6");
         break;
      }
      else if (input(PIN_A0) == 0 && input(PIN_A1)==0 && input(PIN_A2)==1 && input(PIN_A3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
          lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_034: la variable X6_VT_6");
         break;
      }
   }while(true);
}
