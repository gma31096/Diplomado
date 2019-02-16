/*
  Practica 1
  Ejercicio 4
  Medrano Albarrán Gerardo
  Merino Texta Rogelio de Jesús
  09/02/2019
     
 */

void setup() {
 
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}

void loop() {
  int pot=analogRead(A0);
  float vol=(pot/1023.0)*5.0;
  Serial.println(vol);
  if (vol>=3) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
  delay(1);

}
