#include "MQ135.h"
#include <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 7

const int ANALOGPIN = 0;
MQ135 gasSensor = MQ135(ANALOGPIN);

LiquidCrystal_I2C lcd(0x27, 16, 2); 
String quality = "";

void setup(){

  Serial.begin(9600); 
  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);

  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);

  lcd.init(); 
  lcd.backlight();

  lcd.setCursor(0, 0);         
  lcd.print("                ");  

  lcd.setCursor(0, 1);   
  lcd.print("                "); 

  lcd.setCursor(0, 0);         
  lcd.print("   Air Sensor   "); 

  lcd.setCursor(0, 1);   
  lcd.print("   Warming Up   ");  

  delay(2000);

  lcd.setCursor(0, 0);         
  lcd.print("                ");  

  lcd.setCursor(0, 1);   
  lcd.print("                ");   
}

void loop(){

  float ppm = gasSensor.getPPM();

  Serial.print("Air Quality = ");
  Serial.println(ppm);

  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);

  Serial.print("Humidity = ");
  Serial.print("     ");
  Serial.println(DHT.humidity);

  if(ppm < 400){
    quality = "Excellent       ";
  }
  else if (ppm > 400 && ppm < 1000){
    quality = "Fine            ";
  }
  else if (ppm >= 1000 && ppm < 1500){
    quality = "Moderate        ";
  }
  else if (ppm >= 1500 && ppm < 2000){
    quality = "Poor            ";
  }
  else if (ppm >=2000 && ppm <5000){
    quality = "Very Poor       ";
  }
  else if (ppm >= 5000){
    quality = "Severe          ";
  }

  lcd.setCursor (0,0);
  lcd.print("IAQ: ");
  lcd.print(ppm);
  lcd.print(" PPM");

  lcd.setCursor(0,1);
  lcd.print(quality);

  delay(1500);

  lcd.setCursor(0, 0);         
  lcd.print("                ");  
  lcd.setCursor(0, 1);   
  lcd.print("                ");

  delay(500);

  lcd.setCursor (0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C  ");

  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%  ");

  delay(1500);

  lcd.setCursor(0, 0);         
  lcd.print("                ");  
  lcd.setCursor(0, 1);   
  lcd.print("                ");   
  
  delay(500);
}
