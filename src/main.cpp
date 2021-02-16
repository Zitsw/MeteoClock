#include <Arduino.h>
#define print_time // time of print
#define B_LIGHT 5 // leg blue light 
#define G_LIGHT 6 // leg green light
#define R_LIGHT 9 // leg red light
//==============================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include "RTClib.h"
RTC_DS1307 rtc;

#include <MHZ19_uart.h>
MHZ19_uart mhz19;

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;

void start_menu();

int ppm_disp;
float temp_disp;
float hum_disp;

void setup() {
pinMode(R_LIGHT,OUTPUT);
pinMode(G_LIGHT,OUTPUT);
pinMode(B_LIGHT,OUTPUT);
rtc.begin();
lcd.init();
bme.begin();
mhz19.begin(3, 2);

rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
start_menu();

}

void loop() {
DateTime now = rtc.now();
ppm_disp = mhz19.getPPM();
temp_disp = bme.readTemperature();
hum_disp = bme.readHumidity();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("ppm=");
lcd.print(ppm_disp);
lcd.setCursor(10,0);
lcd.print(now.hour());
lcd.print(":");
lcd.print(now.minute());
lcd.setCursor(0,1);
lcd.print("T=");
lcd.print(temp_disp);
lcd.setCursor(9,1);
lcd.print("H=");
lcd.print(hum_disp);
if(ppm_disp <=1000){
    analogWrite(G_LIGHT,20);
}
else if(ppm_disp>1000&&ppm_disp<1400){
    analogWrite(B_LIGHT,20);
}
else{
    analogWrite(R_LIGHT,20);
}
delay(3000);

}


void start_menu(){
lcd.backlight();
lcd.setCursor(3,0);
lcd.print("MeteoClock :)");
lcd.setCursor(0,1);
lcd.print("pre-alfa version");
delay(5000);
lcd.clear();
lcd.setCursor(5,1);
lcd.print("by Zitsw");
delay(5000);
lcd.clear();
}