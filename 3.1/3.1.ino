void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(temp(analogRead(A0)));
  delay(1000);
}
float temp(float voltage){
  float output = (voltage/1023)*5;
  return  ((750/7)*(output-1))+50;
}
