#include <msp430g2553.h>
#define TRAVA BIT7
#define BTN  BIT3

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= TRAVA;
  P1DIR &= ~TRAVA;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  while(1)
  {
    if((P1IN&BTN)==0)
      P1OUT &= ~TRAVA+BTN;
    else
      P1OUT |= TRAVA;
  }
  return 0;
