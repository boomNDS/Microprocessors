#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte customChar[] = {
  B10101,
  B01010,
  B10100,
  B01001,
  B10010,
  B00101,
  B01010,
  B10101
};
void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(6, OUTPUT); // 4 = Trig
  pinMode(7, INPUT); // 2 = Echo
//  lcd.createChar(0, customChar);
  lcd.begin(16, 2);
//  lcd.write(1);
}
void loop() {
//  Serial.println(analogRead(A2));
  lcd.setCursor(0, 1);
//  lcd.print(analogRead(A2)*(5.0/1023));
  digitalWrite(6, HIGH);
  delayMicroseconds(10);
  digitalWrite(6, LOW);
  int pulseWidth = pulseIn(7, HIGH);
  Serial.print("Pulse Width: ");
  Serial.println(pulseWidth);
  long distance = pulseWidth/29/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distance);
  delay(100);
}
