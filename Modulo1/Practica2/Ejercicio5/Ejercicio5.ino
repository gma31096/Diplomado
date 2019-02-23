/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 2 Ejercicio 5 :
 *  
 *  Lectura de sensor Sharp
 *  
 *  23/02/2019
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float val = prom(100);
  Serial.print(val);
  Serial.print(",");
  Serial.println(339);
  if (val>339)  digitalWrite(13,HIGH);
  else digitalWrite(13,LOW);
  
  

}

float prom (int muestra)
{
  float val = 0;
  for (int i=0; i<muestra;i++)  val+=analogRead(A2);
  return val/float(muestra);
}
