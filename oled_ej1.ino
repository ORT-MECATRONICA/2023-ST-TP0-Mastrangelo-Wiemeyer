/*-----------------------------------------------------------------------------------------------------
  Sol Wiemeyer, Josefina Perez Roca e Isabella Mastrángelo 
  5LA 2023 

  Ejer1: Escribir un programa y probarlo en la board que muestre por el Display OLED I2C el texto “Hola mundo”
 ----------------------------------------------------------------------------------------------------- */

/**********LIBRERIAS**************/
#include <U8g2lib.h>

/*********CONSTRUCTORES Y VARIABLES GLOBALES**********/
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() 
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
}
  
void loop() 
{
    printBMP_OLED();
    delay(2000);
}

void printBMP_OLED(void)
{
    u8g2.clearBuffer();        
    u8g2.setFont(u8g2_font_ncenB14_tr); 
    u8g2.drawStr(0,30,"Hola mundo");  
    u8g2.sendBuffer();          
}
