// ลง Library Ultrasonic https://github.com/ErickSimoes/Ultrasonic
// ลง Lib l2c https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
#include <Ultrasonic.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// for Ethernet
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
// Trig 11 Echo 12
Ultrasonic ultrasonic(11, 12); 
int pirpin= 3;

int distance; 


// == Ethernet ==
// Update these with values suitable for your network.
byte mac[]    = {  0xA2, 0xAD, 0xCA, 0xF2, 0xC0, 0xAB };
//IPAddress ip(172, 16, 0, 100);
IPAddress server(10, 30, 4, 111);
//char server[]="broker.mqttdashboard.com";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //  control lcd
  if(topic == "pachorn/led_onoff"){
    if(payload == "on"){
      digitalWrite(6, HIGH);
    }else{
      digitalWrite(6, LOW);
    }
  }else if(topic == "pachorn/led_con"){
    analogWrite(6,(int(payload)%100));
  }
}

EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("pachronClientv1")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("pachorn/hello","hello world");
      // ... and resubscribe
      client.subscribe("pachorn/led_onoff");
      client.subscribe("pachorn/led_con");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
//  led
  pinMode(6,OUTPUT);
  
  //  tmd
  pinMode(A0,INPUT);
  pinMode(pirpin, INPUT);

  //  temp ds1621
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
  lcd.clear();
  lcd.print("Hello, world!");

  // == Ethernet ==
//  client.setServer(server, 1883);
//  client.setCallback(callback);

//  Ethernet.begin(mac);
  // Allow the hardware to sort itself out
//  delay(1500);
}

void loop() {
  // == Ethernet ==
//    if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();
//client.publish("outTopic","hello world");
//delay(5000);
  
  // == read distance ==
  distance = ultrasonic.read(CM); 
  int whichLine = 0;
  Serial.print("Distance in CM: "); 
  Serial.println(distance);
  Serial.print("Pir:");
  Serial.println(digitalRead(pirpin));

// == read temp ds1621 ==  
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
 Serial.print("temp tmp36:");
 Serial.println(temp32(analogRead(A0)));

// == lcd ==
  lcd.clear();
  lcd.setCursor(0, whichLine);
  // print your stuff
  lcd.print("temp: ");
  lcd.print(temp);
  lcd.print(",");
  lcd.print(temp32(analogRead(A0)));
   whichLine = 1 - whichLine;   // Change 0 to 1 or 1 to 0.
  lcd.setCursor(0, whichLine);
  lcd.print("Distance: ");
  lcd.print(distance);
  delay(100);
  delay(1000);

// == led ==
//  digitalWrite(6, HIGH);
  analogWrite(6,100);
}

// cal temp
float temp32(float voltage){
  float output = (voltage/1023)*5;
  return  ((750/7)*(output-1))+50;
}
