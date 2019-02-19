void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);
  
}

void loop() {
  if (digitalRead(7))
  {
    delay(20);
    Serial.println(prom(500));
    delay(500);   
  }
  
  
}
float prom (int muestra)
{
  float val = 0;
  for (int i=0; i<muestra;i++)  val+=analogRead(A2);
  return val/float(muestra);
}
