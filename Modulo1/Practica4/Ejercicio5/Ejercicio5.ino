/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta ROgelio de Jesus
 *    
 *  Practica 4 Ejercicio 5:
 *  
 *  Comandos de movimientos por puerto serial (avance de 10 [cm] y giros de 45°)
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

int distancia=0;
int angulo=0;

void loop() {
  if (Serial.available()>0 or true)                   //Si hay algo en el serial
  {
    String cmd=Serial.readString();
    cmd.remove(cmd.length());                 /*length regresa el entero del número de caracteres del String y remove corta  
                                              la cadena (posición en la cadena,número de caracteres a cortar). Esto para 
                                              cortar el salto de linea.*/

   
    String pal=palabra(cmd,1);                //Se asigna a pal la primer parte de la cadena cmd mediante la función palabra
    if(pal=="move")                           
    {
      pal=palabra(cmd,2);                     //Se asgina a pal la segunda parte de la cadena cmd
      distancia=pal.toInt();
        if(distancia==10)
        {
          adelante();
          detente();
        }else if (distancia==-10)
        {
          atras();
          detente();
        } else Serial.println("ERROR: Invalid distance. Try a valid value.");
      pal=palabra(cmd,3);                     //Se asgina a pal la tercera parte de la cadena cmd
      angulo=pal.toInt();
      if(angulo==45)
        {
          derecha();
          detente();
        } else if (angulo==-45)
        {
          izquierda();
          detente();
        } else if (angulo==0)
        {
          detente();
        } else Serial.println("ERROR: Invalid angle. Try a valid angle.");
    while(true);
    }
  }

}

String palabra(String ora,int a)            //ora es el String ingresado y a es el número de palabra
{
  
  int index=0;
  int i=0;
  String palabra;
    while(i<a){ 
      
      index = ora.indexOf(" ");             //Te da la posición del espacio
      palabra = ora.substring(0,index);     //Asigna a palabra una subcadena que empieza en 0 y termina en index (posicion del espacio)
      ora = ora.substring(index+1);         //Asigna a ora una subcadena que empieza en index+1 y termina al final de la cadena
      i++;
    } 
  return palabra;
}


void adelante()
{
  Serial.println("Adelante");
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  delay(150);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void derecha()
{
  Serial.println("Derecha");
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  delay(50);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void izquierda()
{
  Serial.println("Izquierda");
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(50);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void atras()
{
  Serial.println("Atrás");
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  delay(150);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void detente()
{
  Serial.println("STOP"); 
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}
