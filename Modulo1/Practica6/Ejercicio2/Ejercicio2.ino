volatile long A;
volatile long B;
const float radio=42.0; //[mm]
const float disLlan=80.5; //[mm]
const int ppr=300;        //Porque sólo utilizamos un canal
const float pi=3.14159265;


void setup() {
  Serial.begin(9600);
  
  Serial.setTimeout(5);
  pinMode(8, OUTPUT); //Dirección M1
  pinMode(9, OUTPUT); //PWM M1
  pinMode(10, OUTPUT);  //PWM M2
  pinMode(11, OUTPUT); //Dirección M2

  
  pinMode(2,INPUT);
  pinMode(4,INPUT);

  pinMode(3,INPUT);
  pinMode(5,INPUT);
  attachInterrupt(0, EncoA,RISING);
  attachInterrupt(1, EncoB,RISING);

  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);

   MoveMotors(0,0);
   MoveMotors(1,0);
   delay(5000);   //Tiempo de espera para que la velocidad del motor se estabilice
}

void loop() {
  
  A = 0;
  delay(100);
  int Aa = A;   //La asignación es para evitar que A siga contando en lo que se ejecuta la instrucción
  Serial.println(Aa);
  while(true);
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

void EncoA(){

  digitalRead(4)?A++:A--;
  
}
void EncoB(){
  digitalRead(5)?B--:B++;
}
