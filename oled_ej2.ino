
/*-----------------------------------------------------------------------------------------------------
  Sol Wiemeyer, Josefina Perez Roca e Isabella Mastrángelo
  5LA 2023

  Ejer2: Escribir un programa y probarlo en la board que muestre la temperatura obtenida del sensor Dht11 en el display

  ----------------------------------------------------------------------------------------------------- */

/**********LIBRERIAS**************/
#include "U8g2lib.h"
#include "string"
//#include "DHT.h"
#include "DHT_U.h"
#include "Adafruit_Sensor.h"



/*********CONSTRUCTORES Y VARIABLES GLOBALES**********/
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
  dht.begin();
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
/*
  float a = 2;
  String as;
  sprintf(as, "%f", a);
  Serial.println(a);
  Serial.println("as: " + a);*/

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0, 30, "Temperatura: ");
  u8g2.drawStr(0, 60, temp);
  u8g2.drawStr(90, 60, "C");
  u8g2.sendBuffer();
}
