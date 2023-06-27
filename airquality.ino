#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();
int co2 =0;
double multiplier = 1;// 1 for 2% =20000 PPM, 10 for 20% = 200,000 PPM
uint8_t buffer[25];
uint8_t ind =0;
uint8_t index =0;

int fill_buffer();  // function prototypes here
int format_output();

void readco2()
{
  fill_buffer();  // function call that reacds CO2 sensor and fills buffer
 
    Serial.print("Buffer contains: ");
  for(int j=0; j<ind; j++)Serial.print(buffer[j],HEX);
 index = 0;
 format_output();
  Serial.print(" Raw PPM        ");
 
  index = 8;  // In ASCII buffer, filtered value is offset from raw by 8 bytes
  format_output();
  Serial.println(" Filtered PPM\n\n");
  }
  int fill_buffer(void){
 

// Fill buffer with sensor ascii data
ind = 0;
while(buffer[ind-1] != 0x0A){  // Read sensor and fill buffer up to 0XA = CR
//  if(mySerial.available()){
    buffer[ind] = mySerial.read();
    ind++;
    }
  }
  // buffer() now filled with sensor ascii data
  // ind contains the number of characters loaded into buffer up to 0xA =  CR
  ind = ind -2; // decrement buffer to exactly match last numerical character
  }

 int format_output(void){ // read buffer, extract 6 ASCII chars, convert to PPM and print
   co2 = buffer[15-index]-0x30;
  co2 = co2+((buffer[14-index]-0x30)*10);
  co2 +=(buffer[13-index]-0x30)*100;
  co2 +=(buffer[12-index]-0x30)*1000;
  co2 +=(buffer[11-index]-0x30)*10000;
  Serial.print("\n CO2 = ");
void setup() {
  Serial.begin(9600);

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate I2C address
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}

void loop() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(1000);
}
