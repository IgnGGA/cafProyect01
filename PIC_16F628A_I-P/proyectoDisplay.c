#include <16F628A.h>
#fuses XT, NOWDT
#use delay(clock = 4000000)
#include <lcd.c>
#use standard_io(A)

void main()
{
   lcd_init();
   lcd_putc("\f");
   do{
      lcd_gotoxy(1,1);
      printf(lcd_putc,"Esperando ERROR");
      lcd_gotoxy(1,2);
      printf(lcd_putc, "Registrador de Eventos");
      if (input(pin_a0) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_011: la variable X1_VT_05");
         break;
      }
      else if (input(pin_a1) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_021: la variable X7_VT_05");
         break;
      }
      else if (input(pin_a2) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_031: la variable X6_VT_05");
         break;
      }
      else if (input(pin_a3) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "\fError en:\nERROR_011: la variable X1_VT_6");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_021: la variable X7_VT_05");
         break;
      }
      else if (input(pin_a4) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "\fError en:\nERROR_021: la variable X7_VT_6");
         break;
      }
      else if (input(pin_a5) == 1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "\fError en:\n\fERROR_031: la variable X6_VT_6");
         break;
      }
   }while(true);
}
