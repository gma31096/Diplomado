/*--------------------Librerias------------------------------------*/
#include <Wire.h> //Libería para comunicación 
#include <Adafruit_ADS1015.h> //Librería para los multiplexores

Adafruit_ADS1115 ads1(0x49);
Adafruit_ADS1115 ads0(0x48);

/*-------------------------------------------Variables para A Control PID-----------------------------------------------------------------*/
float RnA,RnaA; //Es redundante inicializar las variables cuando son globales
float KuA=0.08; //K última (límite en la que empieza a oscilar el sistema)
const float KpA=0.6*KuA;
const float TuA=1.5; //[s]  //Constante de tiempo
const float KiA=1.2*KuA/TuA;
const float KdA=3.0*KuA*TuA/40.0;
float RefA=0.0;
float eA=RefA;
float eaA=RefA;
float integA;

/*-----------------------------------------------Variables para B--------------------------------------------------------------------------*/
float RnB,RnaB; //Es redundante inicializar las variables cuando son globales
const float KuB=0.08;
const float KpB=0.6*KuB;
const float TuB=1.5; //[s]
const float KiB=1.2*KuB/TuB;
const float KdB=3.0*KuB*TuB/40.0;
float RefB=0.0;
float eB=RefB;
float eaB=RefB;
float integB=0.0;
/*-------------------------------------------Variables para Control P de Feedback-----------------------------------------------------------*/
float Rnext;
float Eext;
float Kpext=0.0001;
float Rneaext;

/*-----------------------------------------------------------------Variables para relacion de W a velocidad--------------------------------*/
volatile long A;
volatile long B;
const float r=2.2250; //[cm]
const float disLlan=8.05; //[cm]
//const int ppr=300;        //Porque sólo utilizamos un canal
const float pi=3.14159265;
/*-------------------------------------------------------------------Distancia y Angulo---------------------------------------------*/
float Dis,Ang;
float Vr,Wr;
float Vra,Wra;
/*--------------------------------------------------------------------Distancia Sharp-------------------------------------------------*/
float sh[3]={0,0,0};
/*-------------------------------------------------------------------Perfil de velocidad------------------------------------------------*/
const float Vm=20;
/*---------------------------------------------------------LDR's------------------------------------------------------*/
int LDR[8] = {0,0,0,0,0,0,0,0};

float Lang;
int val;


void setup() {
  /*--------------------------------------------------Monitoreo Serie--------------------------------------------------------------------*/
  Serial.begin(9600);
  //Serial.setTimeout(5);
  /*-------------------------------------------------Pines para control de Motores----------------------------------------------------*/
  pinMode(8, OUTPUT); //Dirección M1
  pinMode(9, OUTPUT); //PWM M1
  pinMode(10, OUTPUT);  //PWM M2
  pinMode(11, OUTPUT); //Dirección M2
  /*-------------------------------------------------Pines para los encoders-----------------------------------------------------------*/
  pinMode(2,INPUT); //Enco A (interrupción)
  pinMode(4,INPUT); //Enco A
  pinMode(3,INPUT); //Enco B (interrupción)
  pinMode(5,INPUT); //Enco B
  attachInterrupt(0, EncoA,RISING); //SRI Enco A
  attachInterrupt(1, EncoB,RISING); //SRI Enco B
  /*------------------------------------------------------Multiplexores LDR-------------------------------------------*/
    ads0.begin(); //Inicializa multiplexor
    ads1.begin();
}


void loop() {
   //Move(0,-45.0*pi/180.0);
   //delay(200);
   //while(true);
   //velMot(10,10);
   //Esquiva();
   //actualizaLuz();
   //actualizaSharp();
   //Serial.println(sh[0]);
   //Serial.println(sh[1]);
   //Serial.println(sh[2]);
   //Serial.println("----------------------------");
   //FollowLuz();
   esquiva(); 
}

void FollowLuz(){
  actualizaLuz(); //Se actualizan los valores de las LDR's
  
  if (Lang==0 || fabs(Lang) == (45.0*pi/180.0)) { //Para que avance aunque la luz esté a 45°
    actualizaSharp(); //Se actualizan los valores de los sensores Sharp
    float Min = sh[0];
    if(sh[1]<Min) Min=sh[1];  //Se comparan los valores de los sensores para obtener el menor
    if(sh[2]<Min) Min=sh[2];
    if(Min>20)  Move(20,0); //Si el valor mínimo es mayor a 20 se limita a 20
    else if (Min>=6) Move(Min*0.5,0); //Si es mayor o igual a 6 se mueve una proporción
    else  Move(5,0);  //Si no, muévete 5
  }
  else Move(0,Lang);  //Si Lang es diferente a 0 o +-45, entonces gira Lang
}

void esquiva(){
  actualizaSharp(); //Se actualizan los valores de los sensores Sharp
  actualizaLuz(); //Se actualizan los valores de las LDR's
  //0-> centro
  //1-> derecha
  //2 -> Izq
  short Dumbral1 = 5; //8
  short lm = 1.4;
  int goal = 910;
  if(val>goal) {  //Si el valor de la LDR supera el umbral, giro de victoria
    Move(0,10.1);
  }else if((sh[2]>10 && sh[1]<Dumbral1*lm && sh[0]>10) || (sh[2]>10 && sh[1]<Dumbral1*lm && sh[0]<Dumbral1)){ //Si Sharp derecha o sharps derecha/centro detectan obstáculo
    Move(-5,0); //Retrocede 5[cm]
    Move(0,45.0*pi/180.0);  //Gira 45°
  } else if((sh[2]<Dumbral1*lm && sh[0]<Dumbral1 && sh[1]>10) || (sh[2]<Dumbral1*lm && sh[1]>10 && sh[0]>10)){  //Si Sharp izquierda o sharps izquierda/centro detectan obstáculo
    Move(-5,0); //Retrocede 5[cm]
    Move(0,-40.0*pi/180.0); //Gira -45° (considerando histéresis)
  }else if ((sh[2]<Dumbral1*lm && sh[1]<Dumbral1*lm && sh[0]>10)||(sh[2]<Dumbral1*lm && sh[1]<Dumbral1*lm && sh[0]<Dumbral1)){  //Si Sharp derecha/izquierda o los 3 detectan obstáculo
    Move(-5,0); //Retrocede 5[cm]
    delay(100);
    Move(0,90.0*pi/180.0);  //Gira 90°
    actualizaSharp(); //Se actualizan los valores de los sensores Sharp
    if (sh[2]>15 && sh[1]>15 && sh[0]>15){  //Si los Sharps no detectan obstáculo a 15[cm] o más
      Move(11,0); //Avanza 11[cm]
      delay(100);
      Move(0,-80.0*pi/180.0); //Gira -90°
      delay(100);
    }else {
      Move(0,pi); //Si no se cumple lo de los Sharps entonces gira 180° (llegando hasta 270°)
      delay(100);
      Move(5,0);  //Avanza 5[cm]
      delay(100);
      Move(0,90.0*pi/180.0);  //Gira 90° (para regresar a ángulo 0°
      delay(100);
    }
  }else if (sh[2]>10 && sh[1]>10 && sh[0]<Dumbral1){  //Si Sharp centro detecta obstáculo y los otros no
    Move(-5,0); //Retrocede 5[cm]
    Move(0,45*pi/180.0);  //Gira 45°
    Move(5,0);  //Avanza 45°
  }else FollowLuz();  //Si no, entonces ubica la fuente de luz
}

void Move(float dis,float ang){
  float sen = dis;
  float aux = fabs(dis);
  dis = -0.0003650572*pow(aux,4)+0.0173586426*pow(aux,3)-0.2865221528*pow(aux,2)+2.2956910052*aux;  //Regresión para ajutar distancia lineal
  float Fvel=0.0;
  float tp=(dis/(2.0*Vm))*1000.0; //Sale del despeje de dis=tp*Vm/2 (área del triángulo del perfil de velocidad)
  long t0=millis(); //Referencia de comienzo del perfil
  long tf1=t0+int(tp);  //Tiempo final 1 es igual a la referencia de incio más un tiempo parcial
  /*---------------------------------------------------------------Avance----------------------------------------------*/
  /*------------*/
RefB=0.0;
eB=RefB;
eaB=RefB;
integB=0.0;
integA=0.0;
RnA=0;
RnB=0;
RnaA=0;
RnaB=0;
/*------------------*/
  while(millis()<tf1){  //Mientras el valor de millis sea menor al tiempo final 1 
    Fvel=(Vm/tf1)*millis(); //La velocidad está dada por la ecuación Vel=Vmax*tactual/tfinal1
    (sen>0)?velMot(Fvel,Fvel):velMot(-Fvel,-Fvel);  //Si sen(dis) es mayor a 0 (motores hacia adelante), avanza, si es menor, retrocede (motores hacia atrás)
  }
  long tf2=tf1+int(tp); //Tiempo final 2 es igual al tiempo final 1 (referencia de inicio del tf2) más un tiempo parcial
  while(millis()<tf2){  //Mientras el valor de millis sea menor al tiempo final 2
    Fvel=Vm;  //La velocidad está dada por esa ecuación (velocidad constante)
    (sen>0)?velMot(Fvel,Fvel):velMot(-Fvel,-Fvel);  //Si sen(dis) es mayor a 0 (motores hacia adelante), avanza, si es menor, retrocede (motores hacia atrás)
  }
  long tf3=tf2+int(tp); //Tiempo final 3 es igual al tiempo final 2 (referencia de inicio del tf3) más un tiempo parcial
  while(millis()<tf3){  //Mientras el valor de millis sea menor al tiempo final 3
    Fvel=(3*Vm)-((Vm/tf3)*millis());  //La velocidad está dada por la ecuación Vel=(3*Vmax) - Vmax*tactual/tfinal3
    (sen>0)?velMot(Fvel,Fvel):velMot(-Fvel,-Fvel);  //Si sen(dis) es mayor a 0 (motores hacia adelante), avanza, si es menor, retrocede (motores hacia atrás)
  }
  velMot(0,0);  //Después de eso, se detienen los motores
  analogWrite(9,LOW); //Se desactivan los enable para asegurar la detención de los motores
  analogWrite(10,LOW);
  /*--------------------------------------------Giro--------------------------------*/
    /*------------*/
RefB=0.0;
eB=RefB;
eaB=RefB;
integB=0.0;
integA=0.0;
RnA=0;
RnB=0;
RnaA=0;
RnaB=0;
/*------------------*/  //Mismo proceso que con distancia lineal
  sen = ang;
  aux =fabs(ang);
  if(aux <=0.331612558) ang=-883.2408996163*pow(aux,4)+751.6288254074*pow(aux,3)-222.586252936*pow(aux,2)+28.6257522339*aux;  //Primera ecuación de ajuste para ángulo
  else ang = -0.0823543365*pow(aux,5)+0.6658597286*pow(aux,4)-1.8278459415*pow(aux,3)+1.8668172115*pow(aux,2)+0.6550714861*aux+1.422493344; //Segunda ecuación de ajuste para ángulo
  tp=((ang*r)/(2.0*Vm))*1000.0; //Sale del despeje de dis=tp*Vm/2 (área del triángulo del perfil de velocidad) (considerando distancia angualr dis=angulo*radio)
  t0=millis();  //Referencia de comienzo del perfil
  tf1=t0+int(tp);
  while(millis()<tf1){
    Fvel=(Vm/tf1)*millis();
    (sen>0)?velMot(-Fvel,Fvel):velMot(Fvel,-Fvel);
  }
  tf2=tf1+int(tp);
  while(millis()<tf2){
    Fvel=Vm;
    (sen>0)?velMot(-Fvel,Fvel):velMot(Fvel,-Fvel);
  }
  tf3=tf2+int(tp);
  while(millis()<tf3){
    Fvel=(3*Vm)-((Vm/tf3)*millis());
    (sen>0)?velMot(-Fvel,Fvel):velMot(Fvel,-Fvel);
  }
  velMot(0,0);
  analogWrite(9,0);
  analogWrite(10,0);

  
   
}
void velMot(float RA,float RB){
    short a;
    (RA==RB)?a=1:a=0; //Si velocidad del motor A es igual a la de B, entonces a=1, si no a=0
    RefA=-1*RA; //Velocidad de referencia de motor A (velocidad deseada)
    RefB=-1*RB; //Velocidad de referencia de motor B (velocidad deseada)
    float QWEA=WA();  //Se asigna el valor de la velocidad ángular del motor A
    float QWEB=WB();  //Se asigna el valor de la velocidad ángular del motor B

    Vr = (QWEA+QWEB)*0.5*r; //Conversión a velocidad lineal promedio
    Dis += 0.01*((Vr+Vra)/2.0); //Conversión a distancia lineal
    //Ang += 0.01*((Wr+Wra)/2.0);
    
    
    eA=RefA-QWEA; //Error A es igual a la referencia(valor deseado) menos la velocidad angular actual
    integA+=((eA+eaA)/2.0)*0.01;  //Integral del motor A (método del trapecio)

    eB=RefB-QWEB; //Error B es igual a la referencia(valor deseado) menos la velocidad angular actual
    integB+=((eB+eaB)/2.0)*0.01;  //Integral del motor B (método del trapecio)

    Eext=QWEA-QWEB; //Diferencia entre velocidades angulares si el los motores no giran a la misma velocidad angular
    Rnext=Rneaext+(Kpext*Eext); //Se actualiza la referencia y se le suma la diferencia multiplicada por una constante

    float pda=KdA*((eA-eaA)/0.01);  //Parte proporcional del control del motor A
    float pia=KiA*integA; //Parte integral del control del motor A
    float ppa=KpA*(eA); //Parte diferencial del control del motor A

    float pdb=KdB*((eB-eaB)/0.01);  //Parte proporcional del control del motor B
    float pib=KiB*integB; //Parte integral del control del motor B
    float ppb=KpB*(eB); //Parte diferencial del control del motor B
    
    /*---------------------------------------------------Bloqueo de ventana derivativo---------------------------------------------------*/
      if(pda>5) pda = 5;
      else if(pda<-5) pda = -5;
      
      if(pdb>5) pdb = 5;
      else if(pdb<-5) pdb = -5;
    /*---------------------------------------------------Bloqueo de ventana integral---------------------------------------------------*/
      if(pia>10) pia = 0;
      else if(pia<-10) pia = 0;
      
      if(pib>10) pib = 0;
      else if(pib<-10) pib = 0;
      /*---------------------------------------------------Bloqueo de ventana proporcional---------------------------------------------------*/
      if(ppa>10) ppa = 10;
      else if(ppa<-10) ppa = -10;
      
      if(ppb>10) ppb = 10;
      else if(ppb<-10) ppb = -10;
   
      RnA=RnaA+ppa+pda+pia;//-a*Rnext; //Control PID para motor A más la correción
      RnB=RnaB+ppb+pdb+pib;//+a*Rnext; //Control PID para motor B más la correción

    


    /*-------------------------------------------Procesos de deslinealizacion(Saturacion)-------------------------------------------------------------*/
    if(RnA>127)  RnA = 127;
    else if(RnA<-127) RnA = -127;
    if(RnB>127) RnB = 127; 
    else if(RnB<-127) RnB = -127;
    

    /*-----------------------------------------Actualización de variables involucradas en el control----------------------------------------------------*/
    eaA=eA;
    RnaA=RnA;
    eaB=eB;
    RnaB=RnB;
    Rneaext=Rnext;

    Wra = Wr;
    Vra = Vr;

    MoveMotors(1,RnA);
    MoveMotors(0,RnB);
    delay(10);
}
void MoveMotors(bool id,short vel){   //id=0 Motor derecho
  if(id){
      if(vel<0) digitalWrite(8,HIGH);
      else digitalWrite(8,LOW);
      //(vel<0)?digitalWrite(8,HIGH):digitalWrite(8,LOW);
      analogWrite(9,abs(vel*2));  //Se puede usar el mapeo pero ocupa más procesamiento y memoria
    } else if(!id)  {
      if(vel<0) digitalWrite(11,HIGH);
      else digitalWrite(11,LOW);
      analogWrite(10,abs(vel*2));
    }
}
const int tm=100;

float WA(){
float ang = A*pi/150.0; //Obtención del ángulo girado a partir del número de pulsos del encoder A
A=0;
//return ang/0.2;
return ang/0.01;  //Retorna conversión a velocidad angular del motor A
}
float WB(){
float ang = B*pi/150.0; //Obtención del ángulo girado a partir del número de pulsos del encoder B
B=0;
return ang/0.01;  //Retorna conversión a velocidad angular del motor B
//return ang/0.2;  
}

float prom (int muestra, short pin) //Se realiza un promedio de las lecturas del sensor Sharp
{
  float val = 0;
  for (int i=0; i<muestra;i++)  val+=analogRead(pin); 
  return val/float(muestra);
}

void actualizaLuz(){
  short aux = 0;
  for(int i=0;i<2;i++){ //Por los 2 módulos ADC
    for(int j=0;j<4;j++){ //Por los 4 analógicos de cada uno
      LDR[aux]=AnalogModule(i,j); //Se va guardando la lectura de cada analógico de los ADC en el arreglo de LDR's
      aux++;  //Para ir barriendo la matriz
    }
  }
  
  //Serial.println(LDR[8]);
  short index = 0;
  val = LDR[0]; //val toma el valor de la primera posición del arreglo LDR
  for(int i = 0;i<7;i++){ 
    if(LDR[i+1]>val){   //Se compara el valor de la posición i y la posición i+1
      index = i+1;      //Si el valor de la posición i+1 es mayor que el de la posición i, entonces index toma el valor de la posición de mayor valor
      val = LDR[i+1];   //Se asigna el valor de la posición index en la variable val
    }
  }
  
  //Serial.println(index);
  if(index==0) Lang =90*pi/180; //Se asignan los valores de ángulo correspondiente a la posición de la LDR
  else if(index == 1 ) Lang=135*pi/180;
  else if(index == 2 ) Lang=45*pi/180;
  else if(index == 3 ) Lang=0*pi/180;
  else if(index == 4 ) Lang=-45*pi/180;
  else if(index == 5 ) Lang=-90*pi/180;
  else if(index == 6 ) Lang=-135*pi/180;
  else if(index == 7 ) Lang=180*pi/180;
  /*--------------------------------------------------- 
   *                                Mapeo
   *                                
   *                                0->90°
   *                                1->135°
   *                                2->45°
   *                                3->0°
   *                                4->-45°
   *                                5->-90°
   *                                6->-135°
   *                                7->180°
  ----------------------------------------------------*/
  delay(10);
  
}
int AnalogModule(int module,int Analog)
{
  int16_t val = 0;
  if(module == 0) val = ads0.readADC_SingleEnded(Analog);
  else val = ads1.readADC_SingleEnded(Analog);
  return map(val,0,26856,0,1023);
}
void actualizaSharp(){
  for(int i = 0;i<3;i++){
    float val = (prom(500,14+i)/250.0)-1.0; //Se ajusta el valor a través de la red neuronal
    float c1 = ft(0.369248487925738*val+0.577389959411576);
    float c21 = ft(-3.75383949697236*c1+0.46690748083561);
    float c22 =ft(-1.27651061016856*c1+0.663313903700074);
    float c31 =ft(-0.381050371622249-3.09356404985034*c21-0.944696928934104*c22);
    float c32 = ft(1.00628577459547+0.88112646400912*c21+0.882949047865326*c22);
    float c4 = ft(1.86295227348364-3.14660083320073*c31+1.48218178229938*c32);
    sh[i] = (c4+1.0)*15.0;  //Se guarda el valor procedente de la red en cada una de las posiciones del arreglo sh
  }
  /*
        0-> Medio
        1-> Derecha
        2-> Izquierda
  */
}
double ft(double x)
{
  return (exp(x) - exp(x * (-1))) / (exp(x) + exp(x * (-1))); //Función de disparo sigmoide de la red neuronal
}
void EncoA(){

  digitalRead(4)?A++:A--; //Si se produce la interrupción en el pin 2 (asociado a 0) y el pin 4 es alto A suma, si es bajo A resta
  
}
void EncoB(){
  digitalRead(5)?B--:B++; //Si se produce la interrupción en el pin 3 (asociado a 1) yel pin 5 es alto B suma, si es bajo B resta
}
