#include <Servo.h> 


//Declaração dos objetos que representam os servos usados

Servo servoBase;

Servo servoPainel; 


//Definição das variáveis de controle do temporizador

unsigned long tempoAtual = 1;

const unsigned long tempoEspera = 2000;


//Definição das variáveis lógicas do movimento do painel

int TopoE, TopoD, BaseE, BaseD;

int avgT, avgB, avgE, avgD;

int posBase, posPainel;

//-------------------------------------setup-----------------------------------------------

void setup() { 


  //Indicação dos pinos que vão receber as leituras analógicas dos LDRs

  pinMode(A0,INPUT);

  pinMode(A1,INPUT);

  pinMode(A2,INPUT);

  pinMode(A3,INPUT);


  //Definição dos pinos que vão comportar os ficar os servos

  servoBase.attach(5);

  servoPainel.attach(6); 

  servoBase.write(120);
  servoPainel.write(180);


  //Inicialização do Monitor Serial a certa velocidade

  Serial.begin(9600);

} 

//-------------------------------------loop-----------------------------------------------

void loop()

{ 

  //Armazenamento da posição dos servos

  posBase = servoBase.read();
  posPainel = servoPainel.read();

  //Armazenamento das leituras analógicas dos LDR

  TopoE = analogRead(A0);
  TopoD = analogRead(A1);
  BaseE = analogRead(A2);
  BaseD = analogRead(A3); 

  //Armazenamento das médias aritiméticas de controle dos servos

  avgT = (TopoE + TopoD)/2;
  avgB = (    BaseE + BaseD)/2;
  avgE = (TopoE + BaseE)/2;
  avgD = (TopoD + BaseD)/2;


  //Comparação dos valores médios para tomada de decisão

 if (abs(avgT-avgB) > 99 )
 {
   UpDown();
 }
  if (abs(avgE-avgD) > 60) 
  {
    LeftRight();
 
  }


   

  //-----------------------------------Temporizador-------------------------------------------

    // Gerador do tempo para atualização das informações no Monitor Serial

    if ((millis() - tempoAtual) >= tempoEspera)

    {

      Serial.println("-------------------");

      Serial.print("Angulo Servo Base: ");

      Serial.println(servoBase.read());

      Serial.println("");

      Serial.print("Angulo Servo Painel: ");

      Serial.println(servoPainel.read());

      Serial.println("");

      Serial.print("TopoE: ");

      Serial.println(TopoE);

      Serial.print("TopoD: ");

      Serial.println(TopoD);

      Serial.print("BaseE: ");

      Serial.println(BaseE);

      Serial.print("BaseD: ");

      Serial.println(BaseD);


      Serial.println("");


      Serial.print("AvgT: ");

      Serial.println(avgT);

      Serial.print("AvgB: ");

      Serial.println(avgB);

      Serial.print("AvgE: ");

      Serial.println(avgE);

      Serial.print("AvgD: ");

      Serial.println(avgD);

      Serial.println("-------------------");


      tempoAtual = millis();

    }

  //-----------------------------------------------------------------------------------------


  delay(20); 

} 


//-------------------------------------UpDown-----------------------------------------------

void UpDown()
{ 
  if(avgT < avgB)
  {
    posPainel -= 2; 
  }
  else
  {
    posPainel += 2;
  }

  servoPainel.write(posPainel);

  delay(30); 
} 

//-------------------------------------LeftRight-----------------------------------------------

void LeftRight()

{ 

  if(avgE < avgD)
   { 
    posBase += 2;
    
   }
  else
   {
    posBase -= 2;
    
   }

  servoBase.write(posBase);

  delay(30); 

}



