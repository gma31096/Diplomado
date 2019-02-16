/*
 Práctica 1
 Ejercicio 6
 Medrano Albarrán Gerardo
 Merino Texta Rogelio de Jesús
 */
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

}

void loop() {
  for (int i=0;i<=4; i++)
  {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(2000);
  }
  digitalWrite(13,HIGH);
  while(true);
}
