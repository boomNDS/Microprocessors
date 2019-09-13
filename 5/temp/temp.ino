#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup()
{
  
 Serial.begin(9600);
 Wire.begin();
 Wire.beginTransmission(0x48); // connect to DS1621 (#0)
 Wire.write(0xAC); // Access Config
 Wire.write(0x02); // set for continuous conversion
 Wire.beginTransmission(0x48); // restart
 Wire.write(0xEE); // start conversions
 Wire.endTransmission();
   // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
//  lcd.print("Hello, world!");
//  lcd.setCursor(0, 1);
//  lcd.print("Arduitronics.com");        

 
}
void loop()
{
 int8_t firstByte;
 int8_t secondByte;
 float temp = 0;
 delay(1000); // give time for measurement
 Wire.beginTransmission(0x48);
 Wire.write(0xAA); // read temperature command
 Wire.endTransmission();
 Wire.requestFrom(0x48, 2); // request two bytes from DS1621 (0.5 deg. resolution)
 firstByte = Wire.read(); // get first byte
 secondByte = Wire.read(); // get second byte
 temp = firstByte;
 if (secondByte) // if there is a 0.5 deg difference
 temp += 0.5 ;
 Serial.println(temp);
  lcd.clear();
  lcd.print("temp: ");
  lcd.print(temp);
  delay(100);
 
}
