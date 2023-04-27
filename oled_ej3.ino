/*-----------------------------------------------------------------------------------------------------
  Sol Wiemeyer, Josefina Perez Roca e Isabella Mastrángelo
  5LA 2023

  Ejer3: Escribir un programa y probarlo en la board en la cual encienda el rele cuando la temperatura
  supere los 28 grados
  ----------------------------------------------------------------------------------------------------- */

/**********LIBRERIAS**************/
#include "U8g2lib.h"
#include "string"
//#include "DHT.h"
#include "DHT_U.h"
#include "Adafruit_Sensor.h"



/*********CONSTRUCTORES Y VARIABLES GLOBALES**********/
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#define PIN_RELE 18
#define PIN_LED 25
#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
  dht.begin();

  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  
}

void loop()
{
  printBMP_OLED();
  delay(2000);
}

void printBMP_OLED(void)
{
  float t = dht.readTemperature();
  Serial.println(t);
  char temp[4];
 
  sprintf(temp, "%f", t);

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0, 10, "Temperatura: ");
  u8g2.drawStr(0, 40, temp);
  u8g2.drawStr(90, 40, "C");
  u8g2.sendBuffer();

  if(t >= 28)
  {
    digitalWrite(PIN_RELE, HIGH);
    digitalWrite(PIN_LED, HIGH);
  }
  else
  {
    digitalWrite(PIN_RELE, LOW);
    digitalWrite(PIN_LED, LOW);
  }
}
