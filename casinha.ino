// Programa : Display LCD 16 x 2 e sensor de temperatura LM35
// Autor : NUTEC - 2015

#include <LiquidCrystal.h>
#include <virtuabotixRTC.h> 
#define Luz_Fundo  10
double Light (int RawADC0){ // variável que recebe valor do LDR
double Vout=RawADC0*0.0048828125; // Calculo com a conversão para lux
int lux=500/(10*((5-Vout)/Vout)/.0242);// usar esta equação , se o LDR está na parte superior do divisor de tensão

return lux;
}
const int botao = 8; //constante botão refere-se ao pino digital 2.

//Variável que conterá os estados do botão (0 LOW, 1 HIGH).


// Pino analogico para ligacao do LM35
int pin = 5; 
int pin1 = 6;
int pin2 = 7;
int estadoBotao = 0;
int sensorPin = A0;    // Select input pin for the potentiometer
int sensorValue = 0;   // Variable stores value coming from the sensor
int vlido = 0;
int vrecebido = -2;    // valor recebido da web


// Variaveis que armazenam a temperatura em Celsius 
double tempc = 0,tempd=0, tempe=0, tempf=0;

// Array para precisão na medição
int samples[8]; 

int i;

//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
// define os pinos do RTC
virtuabotixRTC myRTC(16, 17, 18);
//Array que desenha o simbolo de grau
byte a[8]= {B00110,B01001,B00110,B00000,B00000,B00000,B00000,B00000,}; 



void setup()
{
  Serial.begin(9600); // Inicializa comunicação serial
  myRTC.setDS1302Time(0, 0, 0, 0, 00, 00,0000); 
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(botao,INPUT); //Definindo pino digital 2 como de entrada. 
  pinMode(Luz_Fundo,OUTPUT); //define o pino como saída
  digitalWrite(Luz_Fundo,HIGH); // Liga a luz do display.
  lcd.begin(16, 2); //Inicializa 
  lcd.print("Cron.: ");
  //Atribui a "1" o valor do array "A", que desenha o simbolo de grau
  lcd.createChar(1, a); 
  lcd.setCursor(5,1); //Coloca o cursor na coluna 7, linha 1
  lcd.write(1); //Escreve o simbolo de grau
  lcd.setCursor(9,0);
  lcd.write(":");
  lcd.setCursor(12,1);
  lcd.write(1);
}

void loop()
{
   //checando serial 
   
   if (Serial.available() > 0) {
        vrecebido = Serial.read();
     
    }
    
   //sim existe valor na serial 
   
   if (vrecebido > 0) {
  
  //Lendo o estado do pino 2, constante botao, e atribuindo 
  //o resultado a variável estadoBotao.
  //estadoBotao = digitalRead(botao);    

    // mapeamento sensor de pressao

    vlido = map(analogRead(sensorPin), 0, 42, 0, 1019.78);

  /*----------------------------------------------------------*/
  
  //desliga reles da temperatura 
  
  if (vrecebido == '2'){
    
  if (Serial.available() > 0) {
    vrecebido = Serial.read();
    }
  
  digitalWrite(14,LOW);
  digitalWrite(15,LOW);
  Serial.print("ok");
  vrecebido = -2;
  
  }
  
  //liga exp temperatura 
  
  if (vrecebido == '1'){
    
  while (vrecebido == '1'){
    
  if (Serial.available() > 0) {
       vrecebido = Serial.read();
    }
  
  myRTC.updateTime();
    
    
 // Loop que faz a leitura da temperatura 8 vezes
//  for(i = 0;i<=8;i++)
//  {
 
 tempc = analogRead(pin);
 tempc = tempc * 0.4887585532746823069403714565;
 tempd = analogRead(pin2);
 tempd = tempd *  0.4887585532746823069403714565;
 tempe = analogRead(pin1);
 tempe = tempe * 0.4887585532746823069403714565; 
 tempf = analogRead(pin);
 tempf = tempf *  0.4887585532746823069403714565; 
 
// samples[i] = ( 5.0 * analogRead(pin1) * 100) / 1024.0;
//  tempf = tempf + samples[i];
  
  delay(1000);
//  }
// tempf=tempf / 8;
  sensorValue = analogRead(sensorPin);  // Read sensor
  
//As linhas abaixo escrevem o valor da temperatura na saída serial
   
    Serial.print(tempd);
    Serial.print(",");
    Serial.print(tempe);
    Serial.print(",");
    Serial.print(tempf);
    Serial.print(",");
    Serial.print(vlido,DEC);     // Display result
    Serial.print(",");
    Serial.print(int(Light(analogRead(1))));
    Serial.print(",");
    delay(100);
    
 
    
//rotinas para escrita no LCD de temperaturas
lcd.setCursor(0, 1);
lcd.setCursor(0,1);  //Posiciona o cursor na coluna 5, linha 1 do display
lcd.print(tempd,2); //Escreve no display o valor da temperatura minima
lcd.setCursor(7, 1); //Posiciona o cursor na coluna 9, linha 1 do display
lcd.print(tempe,2);  //Escreve no display o valor da temperatura maxima
//lcd.setCursor(13,1);

 
// PARAMETROS DA TEMPERATURA DE LIGAR E DESLIGAR
if (tempe<=28.00)

{

digitalWrite(14,HIGH);
digitalWrite(15,LOW);
}
//Verificando o estado do botão para definir se liga ou
  //desliga o experimento  
//  if (estadoBotao == HIGH) {
 //   digitalWrite(botao,HIGH); //Botão pressionado, acende o led.
//    digitalWrite(14,HIGH);
//  } else {
//    digitalWrite(botao,LOW);  //Botão não pressionado, apaga o led.    
//    digitalWrite(14,LOW); 
 // } 
        
if (tempe>=40.00)
{ 
  digitalWrite(14,LOW);
  digitalWrite(15,HIGH);
  
 
 
 
} 
 

Serial.print(myRTC.minutes);
if (myRTC.minutes < 10)
 {
 lcd.setCursor(8,0);
 lcd.print(myRTC.minutes);
 }
if (myRTC.minutes > 9)
 {
  lcd.setCursor(7,0);
  lcd.print(myRTC.minutes); 
 }
 

  Serial.print(":");
    
   // Adiciona um 0 caso o valor dos minutos seja <10
 if (myRTC.minutes < 10)
  {
     Serial.print("0");
     
  }
  if (myRTC.minutes < 10)
  {
     lcd.setCursor(7,0);
     lcd.print("0");  
  }
  
   Serial.println(myRTC.seconds);
   if (myRTC.seconds < 10);
   {
    lcd.setCursor(10,0);
    lcd.print(" ");
   }
   
   lcd.setCursor(10,0);
   lcd.print(myRTC.seconds);
   
 
     delay(100);
  
  
  }

  
   vrecebido = -2;
  
}




   }

}






 
