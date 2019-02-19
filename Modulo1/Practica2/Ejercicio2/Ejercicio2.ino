/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta ROgelio de Jesus
 *    
 *  Practica 2 Ejercicio 1 :
 *  
 *  Sensor de temperatura en Celsius, Farenheit y Kelvin
 * 
 * 
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Volt=analogRead(A0);
  float Ctemp=(((float(Volt)/1023.0)*5.0)-0.5)*100;
  float Ftemp=(Ctemp*9/5.0)+32;
  float Ktemp=Ctemp+273.15;
  Serial.print(Ctemp);
  Serial.print("[°C] \t");
  Serial.print(Ftemp);
  Serial.print("[°F] \t");
  Serial.print(Ktemp);
  Serial.println("[K] \t");
  delay(100);
  

}
