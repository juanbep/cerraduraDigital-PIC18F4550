#include<18f4550.h> //pic
#use delay(clock=400000) //reloj interno del pic 
#fuses hs, nowdt //fusibles 
#include <lcd.c> //directivas 
#include <kbd1.c>

   int x=1;
   INT t;
   int i,y;
   char k;
   char c[] = {'0','1','9','9','8'}; //arreglo con la contraseņa de nuestra cerradura 
   char d[] = {"00000"};
   
   
  void main()
  {
  
       set_tris_A(0x00); //declarar el puerto A como salida 
       lcd_init(); //iniciar el lcd 
       kbd_init(); //iniciar el teclado matricial 
       port_b_pullups(true);
       
       do
       {
         k = kbd_getc();  //valor del teclado matricial 
         t = k-48;
         lcd_gotoxy(1,1);
         printf(lcd_putc,"INGRESE LA CLAVE: ");
         output_A(0x02);     //sistema apagado
         
         if((k!=0)&&(k!='#')&&(k!='*') )
         {
            lcd_gotoxy(x,2);
            printf(lcd_putc, "%c",k);
            d[x]=k;
            x++;
         }
         if((k!=0)&&(k=='*'))
         {
            i = 0;
            for(i=0;i<5;i++)
            {
               
               if(d[i]!=c[i])
               {
                  break;
               }
            
            }
            if (i==5)
            {
               do
               {
                  k = kbd_getc();
                  lcd_gotoxy(1,2);
                  printf(lcd_putc, "ClAVE CORRECTA");
                  output_A(0x01);
                  y = 0;
               }while(k!='*');
               
               x = 1;
               d = "00000";
               i = 0;
               printf(lcd_putc, "\f");
               delay_ms(5); //50
            
         }
         else
         {
             lcd_gotoxy(1,2);
             printf(lcd_putc, "ClAVE INCORRECTA");
             delay_ms(600);
             x = 1;
             y++;
             d = "00000";
             i = 0;
             printf(lcd_putc, "\f");
         }
         }
         if((k!=0)&&(k=='#'))
         {
            x--;
            d[x] = '0';
            lcd_gotoxy(x,2);
            printf(lcd_putc, " ");
         }
         
         if(x==0)
         {
            x = 1;
         }
         
         //bloqueo del sistema por maximo numero de intentos 
         
         if (y==3)
         {
           do
           {
               printf(lcd_putc, "\fSISTEMA BLOQUEADO");
               delay_ms(5); //50
           }while(true);
            
         }
         
       }while(true);
  
   
  
  }
  
