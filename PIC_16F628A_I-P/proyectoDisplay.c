#include <16F628A>
#fuses XT, NOWDT
#use delay(clock = 4000000)
#include <lcd.c>

void main()
{
   lcd_init();
   printf(lcd_putc,"\fEsperando erro en el\nREGISTRADOR DE EVENTOS"
   do{
      if (input(pin_a0) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_011: la variable X1_VT_05");
      }
      else if (input(pin_a1) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_021: la variable X7_VT_05");
      }
      else if (input(pin_a2) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_031: la variable X6_VT_05");
      }
      else if (input(pin_a3) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_011: la variable X1_VT_6");
      }
      else if (input(pin_a4) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_021: la variable X7_VT_6");
      }
      else if (input(pin_a5) == 1)
      {
         printf(lcd_putc, "\fError en:\n");
         printf(lcd_putc, "ERROR_031: la variable X6_VT_6");
      }
   }
}
