/*
 Práctica 1
 Ejercicio 10
 Medrano Albarrán Gerardo
 Merino Texta Rogelio de Jesús
 09/02/19
 */

void setup() {
  pinMode(9, OUTPUT);
  

}

void loop() {

  float ton=analogRead(A0)/1023.0*5000.0;
  for (int i=0; i<=254; i++)  
  {
    analogWrite(9, i);
    delay(10);
  }
  analogWrite(9,255);
  delay(ton);
  for (int i=255; i>=1; i--)  
  {
    analogWrite(9, i);
    delay(10);
  }
  analogWrite(9,0);
  delay(ton);
}
  
