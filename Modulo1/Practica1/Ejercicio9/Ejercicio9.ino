/*
 Práctica 1
 Ejercicio 9
 Medrano Albarrán Gerardo
 Merino Texta Rogelio de Jesús
 */

void setup() {
  pinMode(9, OUTPUT);
  

}

void loop() {
  for (int i=0; i<=254; i++)  
  {
    analogWrite(9, i);
    delay(10);
  }
  analogWrite(9,255);
  delay(2000);
  for (int i=255; i>=1; i--)  
  {
    analogWrite(9, i);
    delay(10);
  }
  analogWrite(9,0);
  delay(3000);
  
}
