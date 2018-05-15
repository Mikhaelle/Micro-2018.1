1) Defina a função void Atraso(volatile unsigned int x); que fornece um atraso de x milissegundos. Utilize o Timer_A para a contagem de tempo, e assuma que o SMCLK já foi configurado para funcionar a 1 MHz. Esta função poderá ser utilizada diretamente nas outras questões desta prova.
```c
#include <msp430g2553.h>
#include <intrinsics.h>

void Atraso(volatile unsigned int x)
{
    TACCR0 = 1000-1; //capture mode ativo para pegar o timer em 999
    TACTL |= TACLR; // limpar o timer A
    TACTL = TASSEL_2 + ID_0 + MC_1; //TASSEL_2 escolhe SMCLK como o clock do TAR
                                    //ID_0 significa que o clock sera dividido por 1
                                    //MC_1 significa que o timer segue o modo UP e vai contar até o valor setado em TACCR0
    while(x>0)
    {
      x--;
      while((TACTL&TAIFG)==0);
              TACTL &= ~TAIFG;
    }
    TACTL = MC_0; //timer no modo stop

}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
	return 0;
}
```
2.Pisque os LEDs da Launchpad numa frequência de 100 Hz.
```c
#include <msp430g2553.h>
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~(LED1+LED2);
    P1DIR |= LED1 + LED2;
    TA0CCR0 = 5000-1;
    TA0CTL = TASSEL_2 + ID_1 + MC_1 + TAIE;
    _BIS_SR(LPM0_bits+GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
    P1OUT ^= LED1 + LED2;
    TA0CTL &= ~TAIFG;
}
```

3.Pisque os LEDs da Launchpad numa frequência de 20 Hz.
```c
#include <msp430g2553.h>
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~(LED1+LED2);
    P1DIR |= LED1 + LED2;
    TA0CCR0 = 25000-1;
    TA0CTL = TASSEL_2 + ID_1 + MC_1 + TAIE;
    _BIS_SR(LPM0_bits+GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
    P1OUT ^= LED1 + LED2;
    TA0CTL &= ~TAIFG;
}
```
4. Pisque os LEDs da Launchpad numa frequência de 1 Hz.
```c
#include <msp430g2553.h>
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~(LED1+LED2);
    P1DIR |= LED1 + LED2;
    TA0CCR0 = 62500-1; //10000-1;
    TA0CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;
    _BIS_SR(LPM0_bits+GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
    P1OUT ^= LED1 + LED2;
    TA0CTL &= ~TAIFG;
}
```
5. Pisque os LEDs da Launchpad numa frequência de 0,5 Hz.
```c
#include <msp430g2553.h>
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~(LED1+LED2);
    P1DIR |= LED1 + LED2;
    TA0CCR0 = 62500-1; //10000-1;
    TA0CTL = TASSEL_2 + ID_3 + MC_3 + TAIE;
    _BIS_SR(LPM0_bits+GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
    P1OUT ^= LED1 + LED2;
    TA0CTL &= ~TAIFG;
}
```
