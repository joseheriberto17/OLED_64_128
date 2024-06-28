/*
  Nombre del Archivo: OLED_64_128
  Descripción: manejo de matriz SSD1306 sin librerias.
   

  Autor: jose heriberto marquez diaz
  Fecha: 27 de junio 2024

  Notas:
  - Ninguna
*/

#include <stdio.h>
#include <Wire.h>

uint16_t time;
const int16_t I2C_SLAVE = 0b00000000;
uint8_t num1;
uint8_t value;
uint8_t num = 0;
char datos[100];

void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);

  time = 1000;
}

void loop() {
    delay(time);
    toogle(LED_BUILTIN);
}

void toogle(uint8_t pin){
    if (digitalRead(pin)==0)
    {
        digitalWrite(pin,HIGH);
    }
    else
    {
        digitalWrite(pin,LOW);
    }
}


void serialEvent() {
  if (Serial.available() > 0)
  {
    // recoge los datos del serial
    String dataString = Serial.readStringUntil('\n');
    Serial.println("comando  recibido: " + dataString);
    
    // extraccion de letra y numero
        
    unsigned long numero = 0x0;
    char data[10];
    dataString.toCharArray(data,dataString.length()+1);
    
    // Convertir la cadena a un número de tipo unsigned long
    numero = strtoul(data, NULL, 16);

    Serial.print("numero: ");
    Serial.println(numero);

    // dejar formato sin espacion ntre algun valor y la comilla 
    sprintf(datos,"%u",numero);
    value = strlen(datos);

    Serial.print(datos);
    Serial.print("---");
    Serial.println(value);

    delay(120);

    Wire.beginTransmission(I2C_SLAVE);
    Wire.write((uint8_t*)datos,strlen(datos));
    num = Wire.endTransmission();

    toogle(13);
  }
}