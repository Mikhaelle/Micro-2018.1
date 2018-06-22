
/*Pin Connections RFID
===================================      
RFID Module       MSP430 LaunchPads        
--------------    -----------------
Pin 1  (SDA)      Pin 8  (CS)
Pin 2  (SCK)      Pin 7  (SCK)
Pin 3  (MOSI)     Pin 15 (MOSI)
Pin 4  (MISO)     Pin 14 (MISO)
Pin 5  (IRQ)      Not connected
Pin 6  (GND)      GND
Pin 7  (RST)      Pin 10
Pin 8  (3V3)      3V3

Pin Connections LCD
  ===================================
  Display Module    MSP430 LaunchPads
  --------------    -----------------
  EN                P2_4     
  RS                P2_3
  D4                P2_1
  D5                P1_4    
  D6                P2_7
  D7                P2_6  
*/
#include "Mfrc522.h"
#include "LiquidCrystal.h"
#include <SPI.h>

#define BUZZER 13 // Buzzer pino 13
#define TRAVA 3 //Trava pino 3
const int buttonPin = PUSH2; // botão da placa

//Configurações do botão para abrir a trava
int buttonState = 0;             // Estado atual de leitura do botão

LiquidCrystal lcd(P2_3, P2_4, P2_1, P1_4, P2_7, P2_6); // Pinos do LCD

int CS = 8;                                 
int NRSTDP = 5;
Mfrc522 Mfrc522(CS,NRSTDP);
unsigned char serNum[5];

void setup() 
{             
  lcd.begin(16,2);  
  lcd.setCursor( 3 , 0 );
  lcd.print("Iniciando o"); // 
  lcd.setCursor( 4 , 1 ); 
  lcd.print("Sistema...");
  delay(2000);
  lcd.clear();
  
  Serial.begin(9600);                        
  Serial.println("Iniciando sistema...\n");

  SPI.begin();
  digitalWrite(CS, LOW);                    // Initialize the card reader
  pinMode(RED_LED, OUTPUT);                 // Blink LED if card detected
  pinMode(BUZZER,OUTPUT);
  pinMode(TRAVA,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);        // Botão do tipo pull-up normalmente 1
  Mfrc522.Init();  

}

void loop()
{
  
  lcd.setCursor( 4 , 0 );
  lcd.print("Aproxime"); // 
  lcd.setCursor( 4 , 1 ); 
  lcd.print("o cartao");
  delay(200);
   digitalWrite(BUZZER, LOW);
   digitalWrite(TRAVA,LOW);

   
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {     
    // trava normalmente fechada
    digitalWrite(TRAVA, LOW);  
  } 
  else {
    // Quando botão é precionado a trava abre
    digitalWrite(TRAVA, HIGH); 
  }
  

   
  unsigned char status;
  unsigned char str[MAX_LEN];
    
  status = Mfrc522.Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
      lcd.clear();
    lcd.print("Cartao detectado");
    delay(750);
    lcd.clear();
    Serial.print("Card detected: ");
    Serial.print(str[0],BIN);
    Serial.print(" , ");
    Serial.print(str[1],BIN);
    Serial.println("");
  }

  status = Mfrc522.Anticoll(str);
  memcpy(serNum, str, 5);
  if (status == MI_OK)
  {
    digitalWrite(RED_LED, HIGH);              // Card or tag detected!
    Serial.print("O numero do cartao e: ");
    Serial.print(serNum[0]);
    Serial.print(" , ");
    Serial.print(serNum[1]);
    Serial.print(" , ");
    Serial.print(serNum[2]);
    Serial.print(" , ");
    Serial.print(serNum[3]);
    Serial.print(" , ");
    Serial.print(serNum[4]);
    Serial.println("");
 
 // Additional cards can be recognized by running the program and noting the 5 card specific numbers
 // and then adding an "else if" statement below.
    if(serNum[0] == 34 && serNum[1] == 19 && serNum[2] == 24 && serNum[3] == 13 && serNum[4] == 36) 
    {
        //buzzer da um bip
         digitalWrite(BUZZER, HIGH); //BUZZER liga se for cartão valido
         delay(500);
         digitalWrite(BUZZER, LOW); //Buzer desliga

         //comando para o lcd
          lcd.setCursor( 0 , 0 );
          lcd.print("Bem Vinda!"); // 
          lcd.setCursor( 0 , 1 ); 
          lcd.print("Mikhaelle Bueno");
          delay(2000);
          lcd.clear();

          //abre trava
         digitalWrite(TRAVA,HIGH); //trava abre
         lcd.print("Acesso liberado!");
         delay(200);
         lcd.clear();
         delay(1000);
         Serial.println("Mikhaelle\n");
    }
    else if (serNum[0] == 122 && serNum[1] == 207 && serNum[2] == 47 && serNum[3] == 48 && serNum[4] == 170)
    {
        //buzzer da um bip
         digitalWrite(BUZZER, HIGH);
         delay(500);
         digitalWrite(BUZZER, LOW);

         //comando para o lcd
          lcd.setCursor( 0 , 0 );
          lcd.print("Bem Vindo!"); // 
          lcd.setCursor( 0 , 1 ); 
          lcd.print("Matheus Moreira");
          delay(2000);
          lcd.clear();
          
         digitalWrite(TRAVA,HIGH);
         lcd.print("Acesso liberado!");
         delay(1000);
         Serial.println("Matheus\n");
         lcd.clear();
    }
    else
    {
         digitalWrite(TRAVA,LOW);
         //Buzzer da dois bips
         digitalWrite(BUZZER, HIGH);
         delay(250);
         digitalWrite(BUZZER, LOW);
         delay(250);
         digitalWrite(BUZZER, HIGH);
         delay(250);
         digitalWrite(BUZZER, LOW);
         Serial.println("Cartao Invalido!\n");    

         //comando para o lcd
          lcd.setCursor( 0 , 0 );
          lcd.print("Cartao Invalido!"); // 
          lcd.setCursor( 0 , 1 ); 
          lcd.print("Acesso negado!");
          delay(2000);
          lcd.clear();
    
    }  
    delay(1000);
    digitalWrite(RED_LED, LOW);
  }
  Mfrc522.Halt();                         
}


