#define A 8
#define B 9
#define C 4
#define D 3
#define E 2
#define F 7
#define G 6
#define dp 5
#define digits 12
#define unit 13
// e = 2, d = 3 , c = 4,dp = 5, g = 6, f = 7, a =  8 , b = 9
void setup() {
  // put your setup code here, to run once:
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);
   pinMode(dp,OUTPUT);
   pinMode(digits,OUTPUT);
   pinMode(unit,OUTPUT);
   Serial.begin(9600); 
}

void loop() {
  int count = 0;
  for(int i=0;i<30;i++){
    Serial.println(i);
    for(int j = 0;j< 500;j++){
    control(0);
    whatnum(i%10);
    delay(1);
    if(i>= 10){
    control(1);
    whatnum(i/10);
    delay(1); 
    }
    }
  }
}
void drawnum(int numa,int numb,int numc,int numd,int nume,int numf,int numg){
    digitalWrite(A, numa);
    digitalWrite(B, numb);
    digitalWrite(C, numc);
    digitalWrite(D, numd);
    digitalWrite(E, nume);
    digitalWrite(F, numf);
    digitalWrite(G, numg);
}
void control(int num){
  if(num == 0){
    digitalWrite(digits, HIGH);
    digitalWrite(unit, LOW);
  }else{
    digitalWrite(digits, LOW);
    digitalWrite(unit, HIGH);
  }
}
void whatnum(int value){
  if(value == 0) {
  drawnum(1,1,1,1,1,1,0);
  }
    else if(value == 1) {
      drawnum(0,1,1,0,0,0,0);
  }
    else if(value == 2) {
     drawnum(1,1,0,1,1,0,1);
  }
  else if(value == 3) {
    drawnum(1,1,1,1,0,0,1);
  }
  else if(value == 4) {
     drawnum(0,1,1,0,0,1,1);
  }
    else if(value == 5) {
     drawnum(1,0,1,1,0,1,1);
  }
      else if(value == 6) {
     drawnum(1,0,1,1,1,1,1);
  }
      else if(value == 7) {
     drawnum(1,1,1,0,0,0,0);
  }
      else if(value == 8) {
     drawnum(1,1,1,1,1,1,1);
  }
      else if(value == 9) {
     drawnum(1,1,1,1,0,1,1);
  }
}
