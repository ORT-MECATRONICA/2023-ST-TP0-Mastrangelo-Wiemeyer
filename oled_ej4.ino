/*-----------------------------------------------------------------------------------------------------
  Sol Wiemeyer, Josefina Perez Roca e Isabella Mastrángelo
  5LA 2023

  Ejer4: Escribir un programa y probarlo en la board . Para ello se debe hacer la máquina de estado .
  Se tiene dos pantallas la primera P1 : En la cual se muestra la temperatura Actual y el valor umbral .
  En la segunda P2 se debe mostrar el valor umbral y poder modificarlo con los botones. Cuando se presiona
  SW1 se aumenta 1 grados y cuando se presiona SW2 se disminuye 1 grado.
  Para pasar de una pantalla a la otra se debe presionar los dos botones al mismo tiempo.
  ----------------------------------------------------------------------------------------------------- */

/**********LIBRERIAS**************/
#include "U8g2lib.h"
#include "string"
//#include "DHT.h"
#include "DHT_U.h"
#include "Adafruit_Sensor.h"



/*********CONSTRUCTORES Y VARIABLES GLOBALES**********/
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//#define PIN_RELE 18
//#define PIN_LED 25
#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int maquina = 0;
int VALOR_UMBRAL = 10;
#define BTN_SUMA 35
#define BTN_RESTA 34

#define pantalla1 0
#define pantalla2 1
#define limpiar1 2
#define limpiar2 3

void setup()
{
  Serial.begin(9600);
  Serial.println(F("OLED test"));
  u8g2.begin();
  dht.begin();

  pinMode(BTN_SUMA, INPUT_PULLUP);
  pinMode(BTN_RESTA, INPUT_PULLUP);

}

void loop()
{
  float t = dht.readTemperature();
  Serial.println(t);
  char temp[5];
  sprintf(temp, "%2.1f", t);
  Serial.println(temp);
  char umbral[2];
  sprintf(umbral, "%i", VALOR_UMBRAL);

  switch (maquina) {
    case pantalla1:
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 12, "Temperatura: ");
      u8g2.drawStr(5, 27, temp);
      u8g2.drawStr(90, 27, "C");
      u8g2.drawStr(0, 47, "Valor umbral:");
      u8g2.drawStr(0, 62, umbral);
      u8g2.sendBuffer();

      if (digitalRead(BTN_SUMA) == LOW && digitalRead(BTN_RESTA) == LOW) {
        maquina = limpiar1;
      }
      break;

    case limpiar1:
      u8g2.clearBuffer();
      u8g2.sendBuffer();
      if (digitalRead(BTN_SUMA) == HIGH && digitalRead(BTN_RESTA) == HIGH) {
        maquina = pantalla2;
      }
      break;

    case pantalla2:
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(0, 30, "Valor umbral: ");
      u8g2.drawStr(0, 50, umbral);
      u8g2.sendBuffer();
      if (digitalRead(BTN_SUMA) == LOW && digitalRead(BTN_RESTA) == LOW) {
        maquina = limpiar2;
      }
      while (digitalRead(BTN_SUMA) == LOW) {
        if (digitalRead(BTN_SUMA) == HIGH) {
          u8g2.clearBuffer();
          u8g2.sendBuffer();
          VALOR_UMBRAL++;
        }
      }
      while (digitalRead(BTN_RESTA) == LOW) {
        if (digitalRead(BTN_RESTA) == HIGH) {
          u8g2.clearBuffer();
          u8g2.sendBuffer();
          VALOR_UMBRAL--;
        }
      }
      break;

    case limpiar2:
      u8g2.clearBuffer();
      u8g2.sendBuffer();
      if (digitalRead(BTN_SUMA) == HIGH && digitalRead(BTN_RESTA) == HIGH) {
        maquina = pantalla1;
      }
      break;
  }
}
