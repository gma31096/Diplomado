/*
Práctica 1
Ejercicio 5
Medrano Albarrán Gerardo
Merino Texta Rogelio de Jesús
*/


volatile bool led;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  attachInterrupt(0, prende, RISING);

}

void loop() {
  
  if (led==true)
  {
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13,LOW);
    led=false;
  }
  

}

void prende()
{
  led=true;
}
