/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta ROgelio de Jesus
 *    
 *  Practica 2 Ejercicio 0 :
 *  
 *  Maquina de estados de un robot movil que da vuelta a un pista y se estaciona:
 * 
 * 
 */

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);

}


void loop() {

  mov(50, 65);
  delay(1400);
  mov(250, 45);
  delay(600);
  mov(50, 65);
  delay(500);
  mov(250, 45);
  delay(600);
  mov(50, 65);
  delay(1000);
  mov(0, 0);
  delay(500);
  mov(-45, -250);
  delay(300);
  mov(0, 0);
  while (true);


}

void mov(short der, short izq)
{
  if (der == 0)
  {
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(3, 0);
  } else if (der > 0)
  {
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    analogWrite(3, der);
  } else
  {
    digitalWrite(8, LOW);
    digitalWrite(7, HIGH);
    analogWrite(3, der);
  }

  if (izq == 0)
  {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    analogWrite(5, 0);
  } else if (izq > 0)
  {
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    analogWrite(5, izq);
  } else
  {
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    analogWrite(5, izq);
  }
}
