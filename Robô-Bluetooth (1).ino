// Incluindo a biblioteca do bluetooth e servo
#include <SoftwareSerial.h>
#include <Servo.h>
//Iniciando o objeto BT (RX,TX)
SoftwareSerial BT(3, 2); // RXD, TXD
//Pinagem do sensor ultrasónicou
#define echopin A0  // echo pin
#define trigpin A1// Trigger pin

//Criando objectos para os 2 servos
Servo servoDireito;
Servo servoEsquerdo;

int estado = 0;// criando uma variavel para receber os valores do BT 
int timer = 0;//variável para o cronômetro
int distancia;//distância
long duration;//duração

void setup() {
    pinMode (trigpin, OUTPUT);//O pin Echo configurado como entrada
    pinMode (echopin, INPUT );//O pin Echo configurado como saída
    servoDireito.attach(5);//ligado ao pino 5
    servoEsquerdo.attach(6);//ligado ao pino 6
    // iniciar a comunicação serial com uma velocidade de 9600 bits/s:
    Serial.begin(9600);
    BT.begin(9600); // configuração do baud rate da biblioteca SoftwareSerial  
    delay(500); 
}

void loop() {
  //Se algum dado é enviado, vai ser lido e armazenado no estado
    if(BT.available() > 0){     
      estado = BT.read();       
     }  
   //A variavel distancia recebe os parâmetro do da função data()  
   distancia = data();
             
   // se o estado recebe o valor 1 o robô vai para frente
   if (estado == 1){ emfrente();Serial.println("Forward!");}

   else if (estado == 2){atras();Serial.println("Reverse!");}
    
   else if (estado == 3){esquerda();Serial.println("Turn LEFT");}
    
   else if (estado == 4){direita();Serial.println("Turn RIGHT");}
      
   // se o estado é 5 o robô para
   else if (estado == 5) {Stop();Serial.println("STOP!");}    
    // caso o estado seja igual 6 o robô vai para o modo autônomo
   else if (estado == 6) {obstaculo();Serial.println("obstaculo");}  

// configuração para enviar o valor do sensor no APP
timer = timer+1;
Serial.println(timer);

if(timer==200)
{
if(distancia>200){distancia=200;} 
 BT.print("A");
 BT.print(";");
 BT.print(distancia); //envia a distância no APP
 BT.println(";");
 timer = 0;
}

delay(1); 
}
//Funções para cotrolar os servos
void emfrente(){
    servoDireito.write(360);
    servoEsquerdo.write(-360);
}

void atras(){
 servoDireito.write(-360);
 servoEsquerdo.write(360);
}

void direita(){
 servoDireito.write(360);
 servoEsquerdo.write(360);
}

void esquerda(){
 servoDireito.write(-360);
 servoEsquerdo.write(-360);
}

void Stop(){
    servoDireito.write(1500);
    servoEsquerdo.write(1500);
}

long data()
{  //Fazendo um reset no pino trig (Liga e desliga)
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  duration=pulseIn (echopin,HIGH);
  return duration / 29 / 2; 
}
void obstaculo(){
    int distancia, duration; ////Criando as variáveis para a distancia e duracao
  //Fazendo um reset no pino trig (Liga e desliga)
  digitalWrite(trigpin,HIGH);
  delay(200);
  digitalWrite(trigpin,LOW);    
  //A variável duration vai amazenar os valores vindo do Echo
  duration=pulseIn(echopin,HIGH);
  //A distância é calculada a partir da duracao do som
  distancia=(duration/2)/29.1;
  //Imprimir os valores da distância no monitor serial
  Serial.println("");
  Serial.println(distancia);
  
  if(distancia>10){// Caso a distância seja maior que 10cm
   //O robô vai para frente  
    servoDireito.write(360);
    servoEsquerdo.write(-360);
  }
  else{//Caso contrário ou seja menor que 10cm
    //O robô vai pra trás e curva a direita
    servoDireito.write(-360);
    servoEsquerdo.write(360);
    delay(500);
    servoDireito.write(-360);
    servoEsquerdo.write(-360);
    delay(500);
    }
  }
