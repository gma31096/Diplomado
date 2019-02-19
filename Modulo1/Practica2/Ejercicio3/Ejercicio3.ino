/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 2 Ejercicio 3 :
 *  
 *  Lectura de fotoresistencia
 * 
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A1));
  delay(200);

}
