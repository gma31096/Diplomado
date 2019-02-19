/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 2 Ejercicio 4 :
 *  
 *  Digitalización de fotoresistencia con umbral variable por potenciometro
 * 
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(2));
  delay(100);

}
