/*

*/
//incluindo a biblioteca para os servo-motores
#include <Servo.h> 
//Pinagem do sensor ultrasónicou
#define echoPin A0
#define trigPin A1
//Criando objectos para os 2 servos
Servo servoDireito;
Servo servoEsquerdo;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin,INPUT);//O pin Echo configurado como entrada
  pinMode(trigPin,OUTPUT);//O pin Echo configurado como saída
  servoDireito.attach(5);// ligado ao pino 5
  servoEsquerdo.attach(6);//ligado ao pino 6
}

void loop() {
  int dist, dur; //Criando as variáveis para a distancia e duracao
  //Fazendo um reset no pino trig (Liga e desliga)
  digitalWrite(trigPin,HIGH);
  delay(200);
  digitalWrite(trigPin,LOW);    
  //A variável dur vai amazenar os valores vindo do Echo
  dur=pulseIn(echoPin,HIGH);
  //A distância é calculada a partir da duracao do som
  dist=(dur/2)/29.1;
  //Imprimir os valores da distância no monitor serial
  Serial.println("");
  Serial.println(dist);
  
  if(dist>10){// Caso a distância seja maior que 10cm
  //O robô vai para frente
    servoDireito.write(360);
    servoEsquerdo.write(-360);
  }
  else{//Caso contrário ou seja menor que 10cm
    servoDireito.write(-360);
    servoEsquerdo.write(360);
    delay(500);
    servoDireito.write(-360);
    servoEsquerdo.write(-360);
    delay(500);
    
  }
}

