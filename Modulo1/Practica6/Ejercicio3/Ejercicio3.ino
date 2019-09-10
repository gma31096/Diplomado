int EncAizq=2;
int EncAder=3;
int LastateEncAizq

void setup() {
  Serial.begin(9600);
  pinMode(EncAizq,INPUT);
  pinMode(EncAder,INPUT);
  attachInterrupt(0,interMotizq,RISING);
  attachInterrupt(1,interMotder,RISING);
  

}

void loop() {
  

}

void interMotizq()
{
  
}

void interMorder()
{
  
}

