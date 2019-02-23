/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 3 Ejercicio 2 :
 *  
 *  Control de velocidad y dirección mediante comandos
 *  
 *  23/02/2019
 * 
 */
 
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(3, LOW);//Enable1
  digitalWrite(5, LOW);//Enable2
  pinMode(2, OUTPUT);//Dirección M1
  pinMode(4, OUTPUT);//Dirección M2

}

void loop() {
  if (Serial.available()>0)
  {
    String cmd=Serial.readString();
    cmd.remove(cmd.length());       /*length regresa el entero del número de caracteres del String y remove corta la cadena (posición en la 
                                    cadena,número de caracteres a cortar). Esto para cortar el salto de linea.*/
    String pal=palabra(cmd,1);      //Asigna a pal la primera palabra
    if(pal=="A1")
    {
      pal=palabra(cmd,2);       //Asigna a pal la segunda palabra
        if(pal=="on")
        {
          digitalWrite(3, HIGH);  //Activa el Enable1
          pal=palabra(cmd,3);   //Asigna a pal la tercera palabra
          if(pal=="left\n")
          {
            digitalWrite(2, HIGH);  //Activa direción izquierda
          }else digitalWrite(2, LOW); //Activa dirección derecha
        }else digitalWrite(3,LOW); //Desactiva el Enable1
    }else if(pal=="A2")
    {
      pal=palabra(cmd,2);       //Asigna a pal la segunda palabra
        if(pal=="on")
        {
          digitalWrite(5, HIGH);  //Activa el Enable2
          pal=palabra(cmd,3);   //Asigna a pal la tercera palabra
          if(pal=="left\n")
          {
            digitalWrite(4, HIGH);  //Activa direción izquierda
          }else digitalWrite(4, LOW); //Activa dirección derecha
        }else digitalWrite(5,LOW); //Desactiva el Enable2
    }
  }
}

String palabra(String ora,int a)  //ora es el String ingresado y a es el número de palabra
{
  
  int index=0;
  int i=0;
  String palabra;
    while(i<a){ 
      
      index = ora.indexOf(" "); //Te da la posición del espacio
      palabra = ora.substring(0,index); //Asigna a palabra una subcadena que empieza en 0 y termina en index (posicion del espacio)
      ora = ora.substring(index+1); //Asigna a ora una subcadena que empieza en index+1 y termina al final de la cadena
      i++;
    } 
  return palabra;
}
