#include <msp430.h>


void shoudongDAC(void)
{
    P1DIR|=BIT6;
    P1OUT|=BIT6;
    P2DIR|=BIT7;
    P2OUT|=BIT7;

    P3DIR|=BIT2+BIT3+BIT4;
    P3OUT|=BIT2+BIT3+BIT4;

    P4DIR|=BIT1+BIT2;
    P4OUT|=BIT1+BIT2;

    P6DIR|=BIT6;
    P6OUT|=BIT6;                   //前一个DAC无衰减输出

//    P1DIR|=BIT0;
//    P4DIR|=BIT7;

    P1DIR|=BIT2+BIT5;
    P3DIR|=BIT7;
    P2DIR|=BIT2;
    P7DIR|=BIT4;
    P4DIR|=BIT0+BIT3;
    P8DIR|=BIT2;                   //对后一个DAC的管脚定义

    P2DIR&=~BIT1;
//	_enable_interrupts();
	P2REN|=BIT1;
	P2OUT|=BIT1;
	P2IE |=BIT1;
	P2IES|=BIT1;
    P2IFG&=~BIT1;                  //P2.1按键中断
	_EINT();
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
	unsigned int i;
	static unsigned int a=0;
	unsigned int   PUSHKEY=0;
	for(i=0;i<30000;i++)
		;

	PUSHKEY=P2IFG&(~P2DIR);

  if(PUSHKEY == BIT1)
  {
	  P2IFG &= ~BIT1;                         // Clear P2.1 IFG
	  if(a==1)
	  {

          P1OUT|=BIT2+BIT5;P2OUT|=BIT2;
          P7OUT|=BIT4;
          P3OUT|=BIT7;
          P4OUT|=BIT0+BIT3;
          P8OUT|=BIT2;
          P1OUT&=~BIT0;
          P4OUT&=~BIT7;
          }
	  if(a==2)
	  {//从下往上，从低到高
		            P1OUT&=~(BIT2+BIT5);
		            P7OUT&=~BIT4;
		            P2OUT|=BIT2;
		            P3OUT&=~BIT7;
		            P4OUT&=~(BIT0+BIT3);
		            P8OUT&=~BIT2;

		            P1OUT&=~BIT0;
		            P4OUT|=BIT7;
	  }
	  if(a==3)
	  {
	 		            P1OUT&=~(BIT5);
	 		            P2OUT&=~BIT2;
	 		            P7OUT&=~BIT4;
	 		            P1OUT|=BIT2;
	 		            P3OUT&=~BIT7;
	 		            P4OUT&=~(BIT0+BIT3);
	 		            P8OUT&=~BIT2;
	 		            P1OUT|=BIT0;
	 		            P4OUT&=~BIT7;
	 	  }
	  if(a==4)
	  {
	 		            P1OUT&=~(BIT2+BIT5);
	 		            P3OUT&=~BIT7;
	 		            P2OUT&=~BIT2;
	 		            P7OUT&=~BIT4;
	 		            P4OUT|=BIT0;
	 		            P4OUT&=~BIT3;
	 		            P8OUT&=~BIT2;
	 		            P1OUT|=BIT0;
	 		            P4OUT|=BIT7;
	 	  }
	  if(a==5)
	 	  {
	 		            P1OUT&=~(BIT2+BIT5);
	 		            P2OUT&=~BIT2;
	 		            P7OUT&=~BIT4;
	 		            P3OUT|=BIT7;
	 		            P4OUT&=~(BIT0+BIT3);
	 		            P8OUT&=~BIT2;
	 		            P1OUT&=~BIT0;
	 		            P4OUT&=~BIT7;
	 		            _delay_cycles(1000);
	 		            P1OUT|=BIT0;
	 		            P4OUT|=BIT7;
                        a=0;
	 	  }//从1~5，依次是后一个放大DAC输出的1,4,16,64,128倍
  }

  a++;
}
