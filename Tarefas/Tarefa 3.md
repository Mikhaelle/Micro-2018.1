1. Dada uma vari�vel 'a' do tipo 'char' (um byte), escreva os trechos de c�digo em C para:
	(a) Somente setar o bit menos significativo de 'a'.
```c
	#include<msp430g2553.h>
	#define A BIT0
	void main (void)
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A |= BIT 0;
		return 0;
	}
```
	(b) Somente setar dois bits de 'a': o menos significativo e o segundo menos significativo.
```c
	#include<msp430g2553.h>
	#define A BIT0
	void main (void)
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A |= BIT1 + BIT0;
		return 0;
	}
```
	(c) Somente zerar o terceiro bit menos significativo de 'a'.
```c
	#include<msp430g2553.h>
	#define A BIT0
	void main (void)
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A &= ~BIT2;
		return 0;
	}
```
	(d) Somente zerar o terceiro e o quarto bits menos significativo de 'a'.
```c
	#include<msp430g2553.h>
	#define A BIT0
	Void main(void)
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A &= ~(BIT2 + BIT3);
		return 0;
	}
```
	(e) Somente inverter o bit mais significativo de 'a'.
```c
	#include<msp430g2553.h>
	#define A BIT0
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A ^= BIT7;
		return 0;
	}
```
	(f) Inverter o nibble mais significativo de 'a', e setar o nibble menos significativo de 'a'.
```c
	#include<msp430g2553.h>
	{
		WDTCTI = WDTPW + WDTHOLD
		P1IN |= A;
		while(1)
		A ^= BIT7 + BIT6 + BIT5 + BIT4; /*Fazendo uma opera��o de XOR com 1111 0000*/
		A |= BIT3 + BIT2 + BIT1 + BIT0; /*Fazendo uma opera��o de OU com 0000 1111*/		
		return 0;
	}
```
2. Considerando a placa Launchpad do MSP430, escreva o c�digo em C para piscar os dois LEDs ininterruptamente.
```c
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)

void atraso(volatile unsigned int i)
{
  while((i--)>0);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  while(1)
  {
    atraso(0xffff);
    P1OUT ^= LEDS;
  }
  return 0;
}
```
3. Considerando a placa Launchpad do MSP430, escreva o c�digo em C para piscar duas vezes os dois LEDs sempre que o usu�rio pressionar o bot�o.
```c
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

void atraso(volatile unsigned int i)
{
  while ((i--)>0);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  while(1)
  {
    if((P1IN&BTN)==0)
    {
      P1OUT ^= LEDS;
      atraso(0xffff);
      P1OUT &= ~LEDS;
      atraso(0xffff);
      P1OUT ^= LEDS;
      atraso(0xffff);
    }
    else
      P1OUT &= ~LEDS;
  }
  return 0;
}
```
4. Considerando a placa Launchpad do MSP430, fa�a uma fun��o em C que pisca os dois LEDs uma vez.
```c
int pisca(void)
{
      P1OUT ^= LEDS;
      atraso(0xffff);

}
```
5. Reescreva o c�digo da quest�o 2 usando a fun��o da quest�o 4.
```c
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)

void atraso(volatile unsigned int i)
{
  while ((i--)>0);
}

int pisca(void)
{
      P1OUT ^= LEDS;
      atraso(0xffff);

}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  while(1)
  {
    pisca();
  }
  return 0;
}
```
6. Reescreva o c�digo da quest�o 3 usando a fun��o da quest�o 4.
```c
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

void atraso(volatile unsigned int i)
{
  while ((i--)>0);
}

int pisca (void)
{
    if((P1IN&BTN)==0)
    {
      P1OUT ^= LEDS;
      atraso(0xffff);
      P1OUT &= ~LEDS;
      atraso(0xffff);
      P1OUT ^= LEDS;
      atraso(0xffff);
    }
     else
      P1OUT &= ~LEDS;
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  while(1)
  {
   pisca();
  }
  return 0;
}
```
