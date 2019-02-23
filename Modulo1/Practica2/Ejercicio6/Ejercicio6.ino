/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 2 Ejercicio 6 :
 *  
 *  Lectura de sensores mediante comandos de selección
 *  
 *  23/02/2019
 * 
 */
 
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);//Indica cual es el tiempo de salida en ms (por defecto se tarda 1 s por linea, es tipo String)
  pinMode(2, INPUT);
  pinMode(3, INPUT);

}

void loop() {
  if (Serial.available()>0)
  {
    String var=Serial.readString();
    if (var=="shs contact\n")
    {
        bool push = digitalRead(2);
        Serial.print("contact ");
        Serial.print(push);
        Serial.println("_sensado");
    } else if (var=="shs photora\n")
    {
        short photo = analogRead(A0);
        Serial.print("photora ");
        Serial.print(photo);
        Serial.println("_sensado");
    } else if (var=="shs photord\n")
    {
        Serial.print("photord ");
        Serial.print(digitalRead(3));
        Serial.println("_sensado");
    } else if (var=="shs temp\n")
    {
        short temp = analogRead(A1);
        Serial.print("temp ");
        float Ctemp=(((float(temp)/1023.0)*5.0)-0.5)*100;
        Serial.print(Ctemp);
        Serial.println("_sensado");
    } else if (var=="shs infrared\n")
    {
        Serial.print("infrared ");
        Serial.print(reg(500));//Toma 500 muestras
        Serial.println("_sensado");
    }
  }
  

}

float reg(int muestra)
{
  float val = prom(muestra);
  return 0.0000000208*pow(val,4)-0.00002708*pow(val,3)+0.0129675428*pow(val,2)-2.7842761466*val+247.7090506457;  
}
float prom (int muestra)
{
  float val = 0;
  for (int i=0; i<muestra;i++)  val+=analogRead(A2);
  return val/float(muestra);
}
