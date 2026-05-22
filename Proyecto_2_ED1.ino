#include <Servo.h> 

//Botones
const int b1=2; //Modo
const int b2=A2; //Alarma

//Display
const int a=4;
const int b=5;
const int c=6;
const int d=7;
const int e=8;
const int f=3;
const int g=12;

//LED RGB
const int lR = 11;	//Rojo
const int lG = 10;	//Verde
const int lB = 9;	//Azul

const int pot = A0;     //Potenciometro
const int buz = A1;     // Buzzer
const int sermo = 13;   //Servomotor

Servo servo;        	//Crear objeto tipo Servo


//Números de Display	Anodo enciende con LOW
byte numeros[3][7] = {

  //a b c d e f g

  {0,0,0,0,0,0,1}, // 0  
  {1,0,0,1,1,1,1}, // 1  
  {0,0,1,0,0,1,0}, // 2   
};

//MODOS BOTONES
int modo = 0;
int apagadobuz = 0;

//Estado Boton
int estadoB1 = 0;
int estadoB2 = 0;


void setup() {
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(lR, OUTPUT);
  pinMode(lG, OUTPUT);
  pinMode(lB, OUTPUT);

  pinMode(buz, OUTPUT);

  servo.attach(sermo);

}

void loop() {
  
  //BOTON MODO
  int estado1 = digitalRead(b1);
  delay(15);

  if (estado1 == HIGH) {
    estadoB1 = 1;
  }

  if (estadoB1 == 1 && estado1 == LOW) {
    modo++;
    if (modo > 2) {
      modo = 0;
    }
    apagadobuz = 0;
    estadoB1 = 0;
  
  }
  
  //MODO 0
  if (modo == 0) {
    mostrar(0);
    apagadoled();
    digitalWrite(buz, LOW);
    servo.write(0);
  }
  
  else if (modo==1){
    frecuencia();   
  }
  
  else if (modo==2){
    temperatura();
  } 

}

//MODO 1
void frecuencia(){
  mostrar(1);
  
  int val = analogRead(pot);
  int lpm = map(val, 0, 1023, 0, 200);
  int angulo = map(lpm, 0, 200, 0, 180);
  servo.write(angulo);

  if (lpm < 60) {   		//Bradicardia
    amarillo();
  }
  else if (lpm <= 100) {	//Normal
    verde();
  }
  else if (lpm <= 150) {	//Taquicardia
    rojo();
  }
  else {					//Taquicardia severa
    rojoparp();
  }
}
  
//MODO 2
void temperatura(){
  mostrar(2);
  
  int val = analogRead(pot);
  int temp = map(val, 0, 1023, 20, 45);

  //BOTON ALARMA
  int estado2 = digitalRead(b2);
  delay(15);

  if (estado2 == HIGH) {
    estadoB2 = 1;
  }
  
  if (estadoB2 == 1 && estado2 == LOW) {
    apagadobuz = 1;
    digitalWrite(buz, LOW);
    estadoB2 = 0;
  }

  if (temp < 35) {				//HIPOTERMIA
    morado();
    servo.write(0);
    if (apagadobuz == 0){
      digitalWrite(buz, HIGH);
    }
  }
  else if (temp <= 37) {		//NORMAL
    cyan();
    servo.write(45);
    digitalWrite(buz, LOW);
  }
  else if (temp <= 38) {		//FEBRÍCULA
    amarillo();
    servo.write(90);
    digitalWrite(buz, LOW);
  }
  else if (temp <= 39) {		//FIEBRE
    naranja();
    servo.write(135);
    digitalWrite(buz, LOW);
  }
  else {						//FIEBRE ALTA
    blanco();
    servo.write(180);
    if (apagadobuz == 0) {
      digitalWrite(buz, HIGH);
    }
  }
}
  
  

  
 
//Display Mostrar números
void mostrar(int n){
  digitalWrite(a, numeros[n][0]);
  digitalWrite(b, numeros[n][1]);
  digitalWrite(c, numeros[n][2]);
  digitalWrite(d, numeros[n][3]);
  digitalWrite(e, numeros[n][4]);
  digitalWrite(f, numeros[n][5]);
  digitalWrite(g, numeros[n][6]);  
}
  
  
//LED RGB COLORES 
//Apagado  
void apagadoled(){
  analogWrite(lR,0);
  analogWrite(lG,0);
  analogWrite(lB,0);   
}

//ROJO   
void rojo(){
  analogWrite(lR,255);
  analogWrite(lG,0);
  analogWrite(lB,0);   
}
  
//VERDE   
void verde(){
  analogWrite(lR,0);
  analogWrite(lG,255);
  analogWrite(lB,0);   
}

//AZUL   
void azul(){
  analogWrite(lR,0);
  analogWrite(lG,0);
  analogWrite(lB,255);   
}
  
//BLANCO   
void blanco(){
  analogWrite(lR,255);
  analogWrite(lG,255);
  analogWrite(lB,255);   
}
 
//AMARILLO  
void amarillo(){
  analogWrite(lR,255);
  analogWrite(lG,255);
  analogWrite(lB,0);   
}
  
//MAGENTA   
void morado(){
  analogWrite(lR,255);
  analogWrite(lG,0);
  analogWrite(lB,255);   
}
  
//CYAN  
void cyan(){
  analogWrite(lR,0);
  analogWrite(lG,255);
  analogWrite(lB,255);   
}
  
//ANARANJADO  
void naranja(){
  analogWrite(lR,200);
  analogWrite(lG,180);
  analogWrite(lB,0);   
}
    

//ROJO PARPADEA
void rojoparp() {
  rojo();
  delay(300);
  apagadoled();
  delay(300);
}