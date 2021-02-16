#include <Arduino.h>

//==============================================
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <MHZ19_uart.h>
MHZ19_uart mhz19;
LiquidCrystal_I2C lcd(0x27,16,2);;
float ppm_disp;
void setup() {
lcd.init();
mhz19.begin(3, 2);

}

void loop() {
ppm_disp = mhz19.getPPM();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print(ppm_disp);
}