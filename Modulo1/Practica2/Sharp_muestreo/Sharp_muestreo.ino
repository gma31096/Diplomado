void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(80);
  pinMode(7, INPUT);
  
}

void loop() {
  if (Serial.available() > 0)
  {
     Serial.readString();
     Serial.println(prom(500));
     Serial.println(reg(500));
     
  }
  //if (digitalRead(7))
  //{
    //delay(20);
    //Serial.println(prom(500));
    //delay(500);   
  //}
  
  
}
float reg(int muestra)
{
  float val = prom(muestra);
  return 0.0000000208*pow(val,4)-0.00002708*pow(val,3)+0.0129675428*pow(val,2)-2.7842761466*val+247.7090506457;  
}
float prom (int muestra)
{
  float val = 0;
  for (int i=0; i<muestra;i++)  val+=analogRead(A2);
  return val/float(muestra);
}
