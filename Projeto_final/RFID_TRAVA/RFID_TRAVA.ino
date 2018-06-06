/*
Example for TI MSP430 LaunchPads and Energia that reads a card number 
using a RC522 MIFARE module, takes action depending on the card number,
and prints it to the serial monitor.
https://www.addicore.com/RFID-AddiKit-with-RC522-MIFARE-Module-RFID-Cards-p/126.htm
Based on code and ideas from Eelco Rouw (www.43oh.com), Grant Gibson
(www.grantgibson.co.uk), Dr.Leong (www.b2cqshop.com), and
Craig Thompson/Aaron Norris at Addicore.
Minor modifications to above by Frank Milburn 10 June 2015
Released into the public domain
Tested on MSP-EXP430G2 LaunchPad
          MSP-EXP430F5529 LaunchPad
          MSP-EXP430FR5969 LaunchPad
 
Pin Connections
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
Addicore has a very good introduction to this module, written for Arduino.
Try the site below for additional detail on the module and examples
which include writing to a card, dumping detailed information, changing
the card user ID, etc.  It will run on LaunchPads or Arduinos with the
correct pin connections:  https://github.com/miguelbalboa/rfid
*/

#include "Mfrc522.h"
#include <SPI.h>
#include <msp430g2553.h>

int CS = 8;                                 // chip select pin
int NRSTDP = 5;
Mfrc522 Mfrc522(CS,NRSTDP);
unsigned char serNum[5];
#define LEDS BIT0;
#define BUZZER1 BIT1;

void setup() 
{             
  Serial.begin(9600);                        
  Serial.println("Starting RFID-RC522 MIFARE module demonstration...\n");

  SPI.begin();
  digitalWrite(CS, LOW);                    // Initialize the card reader
  pinMode(RED_LED, OUTPUT);                 // Blink LED if card detected
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
  Mfrc522.Init(); 
   
}

void loop()
{
  P1OUT &= ~LEDS;
  unsigned char status;
  unsigned char str[MAX_LEN];
    
  status = Mfrc522.Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    Serial.print("Cartao detectado: ");
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
    Serial.print("Numero do Cartao: ");
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
      Serial.println("Mikhaelle\n");
       travaAbre();
    }
    else if (serNum[0] == 122 && serNum[1] == 207 && serNum[2] == 47 && serNum[3] == 48 && serNum[4] == 170)
    {
      Serial.println("Matheus\n");
      travaAbre();
    }
    else
    { 
      travaFecha();
   //   P1OUT &= ~LEDS;
   //   Serial.println("Cartao invalido!\n");  
     // P1OUT &= ~LEDS;  
    //  buzzer();
    } 
    delay(1000);
    digitalWrite(RED_LED, LOW);
  }
  Mfrc522.Halt();                         
}

//void atraso(volatile unsigned int i)
//{
 //while((i--)>0);
//}

int travaAbre(void)
{
    delay(2000);
    P1OUT ^= LEDS;
  return 0;
}

int travaFecha(void)
{
   P1OUT &= ~LEDS;
  delay(2000);
  
  return 0;
}

//int buzzer(void)
//{
 // WDTCTL = WDTPW | WDTHOLD;
  //P1OUT |= BUZZER1;
  //P1DIR |= BUZZER1;
  //while(1)
  //{
   // delay(1000);
    //P1OUT ^= BUZZER1;
  //}
  //return 0;
//}
