Para todas as questões, utilize os LEDs e/ou os botões da placa Launchpad do MSP430.

1. Escreva um código em C que pisca os LEDs ininterruptamente.
'''c
#include <msp430g2553.h>
#define LED1 BIT0   //Bit0 é o led vermelhor e foi definido como LED1
#define LED2 BIT6   //bit6 é o led verde e foi definido como led2
#define LEDS (LED1|LED2) //para manipular led1 e led2 igualmente foi utilizado outro define

void atraso(volatile unsigned int i) {
  
  while((i--)>0) // enquanto n chegar em 0 vai ter atraso
}

int main() {

  WDTCTL = WDTPW | WDTHOLD; //
  P1OUT |= LEDS; //define os leds como saida digital
  P1DIR |= LEDS; //define apenas os leds como saida e o restante como entrada
  while(1) //loop infinito
  {
    P1OUT ^= LEDS; //acende leds
    atraso(0xffff);
  }
 return 0;
}
'''
2. Escreva um código em C que pisca os LEDs ininterruptamente. No ciclo que pisca os LEDs, o tempo que os LEDs ficam ligados deve ser duas vezes maior do que o tempo que eles ficam desligados.
'''c
#include <msp430g2553.h>
#define LED1 BIT0   //Bit0 é o led vermelhor e foi definido como LED1
#define LED2 BIT6   //bit6 é o led verde e foi definido como led2
#define LEDS (LED1|LED2) //para manipular led1 e led2 igualmente foi utilizado outro define

void atraso(volatile unsigned int i) {
  
  while((i--)>0)
  {
    P1OUT &= ~LEDS;// enquanto n chegar em 0 vai ter atraso
  }
}

void tempo(volatile unsigned int j)
{
  while((j--)>0)
  {
    P1OUT ^= LEDS; 
  }
}

int main() {

  WDTCTL = WDTPW | WDTHOLD; //
  P1OUT |= LEDS; //define os leds como saida digital
  P1DIR |= LEDS; //define apenas os leds como saida e o restante como entrada
  while(1) //loop infinito
  {
    tempo(0xffff);
    atraso(0x7f9b);
  }
 return 0;
}
'''
3. Escreva um código em C que acende os LEDs quando o botão é pressionado.
'''c
#include <msp430g2553.h>
#define LED1 BIT0   //Bit0 é o led vermelhor e foi definido como LED1
#define LED2 BIT6   //bit6 é o led verde e foi definido como led2
#define LEDS (LED1|LED2) //para manipular led1 e led2 igualmente foi utilizado outro define
#define BOT  BIT3

void atraso(volatile unsigned int i) {
  
  while((i--)>0);

}

int main(void) {

  WDTCTL = WDTPW | WDTHOLD; //
  P1OUT |= LEDS; //define os leds como saida digital
  P1DIR |= LEDS; //define apenas os leds como saida e o restante como entrada
  P1DIR &= ~BOT;
  P1OUT |= BOT;
  P1REN |= BOT;
  while(1) //loop infinito
  {
    if((P1IN&BOT)==0)
    {
      while(1)
      {
         P1OUT ^= LEDS;
         atraso(0xffff);
      }
    }
  }
 return 0;
}
'''
4. Escreva um código em C que pisca os LEDs ininterruptamente somente se o botão for pressionado.
'''c
#include <msp430g2553.h>
#define LED1 BIT0   //Bit0 é o led vermelhor e foi definido como LED1
#define LED2 BIT6   //bit6 é o led verde e foi definido como led2
#define LEDS (LED1|LED2) //para manipular led1 e led2 igualmente foi utilizado outro define
#define BOT  BIT3

void atraso(volatile unsigned int i) {
  
  while((i--)>0);

}

int main(void) {

  WDTCTL = WDTPW | WDTHOLD; //
  P1OUT |= LEDS; //define os leds como saida digital
  P1DIR |= LEDS; //define apenas os leds como saida e o restante como entrada
  P1DIR &= ~BOT;
  P1OUT |= BOT;
  P1REN |= BOT;
  while(1) //loop infinito
  {
    if((P1IN&BOT)==0){
    P1OUT ^= LEDS;
    atraso(0xffff);
    }
    else
      P1OUT &= ~LEDS;
  }
 return 0;
}
'''
5. Escreva um código em C que acende os LEDs quando o botão é pressionado. Deixe o MSP430 em modo de baixo consumo, e habilite a interrupção do botão.

