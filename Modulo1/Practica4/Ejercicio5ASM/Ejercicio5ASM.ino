/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta ROgelio de Jesus
 *    
 *  Practica 4 Ejercicio 5.1:
 *  
 *  Algoritmo de evasión de obstáculos (avance de 10 [cm] y giros de 45°)
 * 
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode(6,INPUT); //Contacto lado derecho
  pinMode(7,INPUT); //Contacto lado izquierda
  pinMode(8, OUTPUT); //Dirección M1
  pinMode(9, OUTPUT); //PWM M1
  pinMode(10, OUTPUT);  //PWM M2
  pinMode(11, OUTPUT); //Dirección M2

}

int estado;
short vel1=100;
short vel2=100;


void loop() {
  
      int Sd = digitalRead(6);
      int Si = digitalRead(7);
      if(Sd==0 && Si==0)  {
        adelante();
        detente();
      } else if(Sd==1 && Si==0) {
        atras();
        derecha();
        detente();
      } else if(Sd==0 && Si==1) {
        atras();
        izquierda();
        detente();
      } else if(Sd==1 && Si==1) {
        atras();
        derecha();
        derecha();
        adelante();
        adelante();
        izquierda();
        izquierda();
      }


}

void adelante()
{
  Serial.println("Adelante");
  digitalWrite(8,HIGH);
  analogWrite(9,vel1);
  analogWrite(10,vel2);
  digitalWrite(11,HIGH);
  delay(300);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void derecha()
{
  Serial.println("Derecha");
  digitalWrite(8,LOW);
  analogWrite(9,vel1);
  analogWrite(10,vel2);
  digitalWrite(11,HIGH);
  delay(130);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void izquierda()
{
  Serial.println("Izquierda");
  digitalWrite(8,HIGH);
  analogWrite(9,vel1);
  analogWrite(10,vel2);
  digitalWrite(11,LOW);
  delay(130);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void atras()
{
  Serial.println("Atrás");
  digitalWrite(8,LOW);
  analogWrite(9,vel1);
  analogWrite(10,vel2);
  digitalWrite(11,LOW);
  delay(500);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void detente()
{
  Serial.println("STOP"); 
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}
