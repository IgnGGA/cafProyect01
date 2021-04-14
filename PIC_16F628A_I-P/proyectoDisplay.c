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
      //funcion de arduino lecturasEnSubida05
      if      (input(pin_a0) == 1 && input(pin_a1)==0 && input(pin_a2)==0 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_011: la variable X1_VT_05");
         break;
      }
      else if (input(pin_a0) == 0 && input(pin_a1)==1 && input(pin_a2)==0 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_021: la variable X7_VT_05");
         break;
      }
      else if (input(pin_a0) == 1 && input(pin_a1)==1 && input(pin_a2)==0 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_031: la variable X6_VT_05");
         break;
      }
      //funcion de arduino lecturasEnSubida6
      else if (input(pin_a0) == 0 && input(pin_a1)==0 && input(pin_a2)==1 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_012: la variable X1_VT_6");
         break;
      }
      else if (input(pin_a0) == 1 && input(pin_a1)==0 && input(pin_a2)==1 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_022: la variable X7_VT_6");
         break;
      }
      else if (input(pin_a0) == 0 && input(pin_a1)==1 && input(pin_a2)==1 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_032: la variable X6_VT_6");
         break;
      }
      //funcion de arduino lecturasEnBajada05
      else if (input(pin_a0) == 1 && input(pin_a1)==1 && input(pin_a2)==1 && input(pin_a3)==0)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_013: la variable X7_VT_05");
         break;
      }
      else if (input(pin_a0) == 0 && input(pin_a1)==0 && input(pin_a2)==0 && input(pin_a3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_023: la variable X7_VT_05")
         break;
      }
      else if (input(pin_a0) == 1 && input(pin_a1)==0 && input(pin_a2)==0 && input(pin_a3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
          lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_033: la variable X6_VT_05")
         break;
      }
      //funcion de arduino lecturasEnBajadas6
      else if (input(pin_a0) == 0 && input(pin_a1)==1 && input(pin_a2)==0 && input(pin_a3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc, "ERROR_014: la variable X7_VT_6");
         break;
      }
      else if (input(pin_a0) == 1 && input(pin_a1)==1 && input(pin_a2)==0 && input(pin_a3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_024: la variable X7_VT_6")
         break;
      }
      else if (input(pin_a0) == 0 && input(pin_a1)==0 && input(pin_a2)==1 && input(pin_a3)==1)
      {
         lcd_putc("\f");
         lcd_gotoxy(1,1);
         printf(lcd_putc, "Error en:");
          lcd_gotoxy(1,2);
         printf(lcd_putc,"ERROR_034: la variable X6_VT_6")
         break;
      }
   }while(true);
}
