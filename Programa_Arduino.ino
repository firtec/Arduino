/******************************************************************************
 * Protocolo: Si recibe el caracter "a" envía la temperatura.
 *            Si recibe el caracter "b" envía la presión.
 *            Si recibe el caracter "c" limpia los buffer de comunicaciónes.
 *                            
 * Placa Arduino: UNO
 * Arduino IDE: 1.8.5
 *
 * www.firtec.com.ar
*********************************************************************************/
//#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

Adafruit_BMP280 bmp; // I2C

//SoftwareSerial mySerial(11, 12); // RX, TX
char RX_Byte ;
char base;
byte a = 0;
char msg[20];
static char Temperatura[4];
static char Presion[6];
volatile char* buffn="";

void setup() {
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial.read(); 
    
  if (!bmp.begin()) {  
    Serial.println(F("No encuentro el sensor BMP280!"));
    while (1);
  }
 }

void loop() { 
float p;   
float t;  

while(1){
if (Serial.available()> 0) {
    RX_Byte = Serial.read(); 
    if(RX_Byte=='a'){
      t =  bmp.readTemperature();
      dtostrf(t,2,1,buffn);
      sprintf(Temperatura,"%s", buffn);
      Serial.print(Temperatura);
      Serial.flush();
    
     }
    if(RX_Byte=='b'){
      p = bmp.readPressure()/100;
      dtostrf(p,3,1,buffn);
      sprintf(Presion,"%s", buffn);
      Serial.print(Presion);
      Serial.flush();
    }
    if(RX_Byte=='c'){
      Serial.read();
      Serial.flush();
    }
  }
 }
}
//*************** Fin del archivo Firtec Argentina ********************

