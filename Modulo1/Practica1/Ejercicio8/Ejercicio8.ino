/*
Práctica 1
Ejercicio 8
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
      for (int i=0;i<=9; i++)
    {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
    led=false;
  }
  

}

void prende()
{
  led=true;
}
