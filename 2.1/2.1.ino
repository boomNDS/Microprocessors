void setup() {
  // put your setup code here, to run once:
  pinMode(4,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(4));
  if(digitalRead(4)==1){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
