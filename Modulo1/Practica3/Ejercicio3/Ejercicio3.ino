/*
 *  Diplomado Inteligencia artificial
 *  
 *  By:
 *    Medrano Albarrán Gerardo
 *    Merino Texta Rogelio de Jesus
 *    
 *  Practica 3 Ejercicio 3 :
 *  
 *  Control de velocidad y dirección de los motores mediante PWM
 *  
 *  23/02/2019
 * 
 */
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

}
int vel=0;
void loop() {
  if (Serial.available()>0)
  {
    String cmd=Serial.readString();
    cmd.remove(cmd.length());                 /*length regresa el entero del número de caracteres del String y remove corta  
                                              la cadena (posición en la cadena,número de caracteres a cortar). Esto para 
                                              cortar el salto de linea.*/
    String pal=palabra(cmd,1);                //Asigna a pal la primera palabra
    if(pal=="A1")
    {
      pal=palabra(cmd,2);                    //Asigna a pal la segunda palabra
        if(pal=="speed")
        {
          pal=palabra(cmd,3);               //Asigna a pal la tercera palabra
          vel=pal.toInt();                  //Asigna a vel el valor ingresado en la cadena (lo convierte a entero)
          vel = map(vel, -127, 127, 0, 255);
          analogWrite(3, vel);
        }
    }else if(pal=="A2")
    {
      pal=palabra(cmd,2);                   //Asigna a pal la segunda palabra
        if(pal=="speed")
        {
          pal=palabra(cmd,3);               //Asigna a pal la tercera palabra
          vel=pal.toInt();                  //Asigna a vel el valor ingresado en la cadena (lo convierte a entero)
          vel = map(vel, -127, 127, 0, 255);//Mapeo
          analogWrite(5, vel);  
        }
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
