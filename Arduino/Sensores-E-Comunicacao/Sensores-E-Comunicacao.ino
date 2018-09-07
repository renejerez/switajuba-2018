String cartao="",a[3],cartao_anterior,inicio,fim;
char c;
int ok=0,ig=0,manutencaov,n=1,i,b=1,gasv;
//-----------------LCD-------------------//
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//----------------RTC--------------------//
#include <DS1307.h>
DS1307 rtc(A4, A5);
void setup() 
{
//-----------------LCD-------------------//
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->");
//-----------------RFID-------------------//  
  Serial.begin (9600);
  Serial1.begin (9600);
//----------------RTC--------------------//
  rtc.setTime(18, 48, 0);     //Define o horario
  rtc.setDate(1, 9, 2018);   //Define o dia, mes e ano
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
}
void loop() {
//--------------------GRAVAÇAO--------------------// 
  if(Serial1.available()>0)
  {
    c=Serial1.read();
      if(c==0x02) cartao="";
    else if(c==0x03)
    {
        if(cartao_anterior!=cartao)
        {
          for(i=0;i<3;i++)
          {
            if(cartao==a[i])
            {
              break;
            }
          }
          if(i==3)
          {
            cartao_anterior=cartao;
            a[b]=cartao;
            //--------COISAS P ENVIAR DPS DA TAG--------------//          
          Serial.print("Trabalhador ");
          Serial.println(b);
          Serial.println(cartao);
          Serial.print("Hora : ");
          Serial.print(rtc.getTimeStr());
          Serial.print(" ");
          Serial.print("Data : ");
          Serial.println(rtc.getDateStr(FORMAT_SHORT));
          b++;
          }
        }
      }
      
    else
    {
      cartao=cartao+c;
    }
    }
//----------------IGNIÇÃO----------------------//
int enter=digitalRead(50);   
int cancela=digitalRead(51); 
int pushB=digitalRead(52);
int manutencaoB=digitalRead(53);
int gasB=digitalRead(49);    
if(pushB==HIGH && ig==0){
 inicio=rtc.getTimeStr();
 Serial.print("Hora de inicio = ");  
 Serial.println(rtc.getTimeStr());
 ig=1;
    }
if(pushB==LOW && ig==1){
 inicio=rtc.getTimeStr();
 Serial.print("Hora de fim = ");  
 Serial.println(rtc.getTimeStr());
 ig=0;
    }
//----------------MANUTENÇAO-----------------//    
if(manutencaoB==HIGH){
manutencaov = 1;
}

  if(manutencaov ==1){
    
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->");
  lcd.setCursor(0, 1);
  lcd.print("Deseja manutençao?");
    
  if(enter==HIGH){
      // enviar dado sobre manutenção
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->");
  manutencaov = 0;
      }
  if(cancela==HIGH){
      // enviar dado sobre manutenção
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->"); 
  manutencaov = 0;
   }
 }
//------------------GASOLINA---------------//
if(gasB==HIGH){
gasv = 1;
}

  if(gasv ==1){
  int sensorValue = analogRead(A3);// read the input on analog pin 3:
  float  litros = sensorValue / 3.41;// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print("Litros = ");
  Serial.println(litros); 
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Litros add");
  lcd.setCursor(0, 1);
  lcd.print(litros);
  lcd.setCursor(7, 1);
  lcd.print("l.");
    
  if(enter==HIGH){
  // enviar dado sobre litros
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->");
  gasv = 0;
      }
  if(cancela==HIGH){
 
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("<-SWM--GIF->"); 
  gasv = 0;
   }
 } 
}


Enviado do meu iPhone
