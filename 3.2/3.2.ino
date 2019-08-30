void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("A0 = ");
  Serial.print(analogRead(A0));
    Serial.print(" A1 = ");
  Serial.print(analogRead(A1));
    Serial.print(" A2 = ");
  Serial.println(analogRead(A2));
  analogWrite(8,analogRead(A0));
  analogWrite(9,analogRead(A1));
  analogWrite(10,analogRead(A2));
  delay(1000);
}
