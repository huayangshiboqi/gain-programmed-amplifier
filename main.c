#include <msp430.h> 
unsigned int l=1;
void shoudongDAC(void);
void ADCautomatic(void);
void OLED(void);
void Picture_10();
void Picture_7();
void Picture_8();
void Picture_11();
void main(void)
{
      WDTCTL = WDTPW +WDTHOLD;	            // Stop watchdog timer
      OLED();
      P1DIR&=~BIT1;                         //将P1.1脚设置为输入方式
      _enable_interrupts();                 //使能总中断
      P1REN|=BIT1;                          //使能P1.1上拉、下拉寄存器
      P1OUT |=BIT1;                         //将P1.1设置为上拉输入
      P1IES |=BIT1;                         //将P1.1设置下降沿触发中断
      P1IFG&=~BIT1;                         //清除P1.1中断标志位
      P1IE|=BIT1;                           //使能P1.1中断
}


// 这是我的中断程序
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    unsigned int i,PUSHKEY=0;
    P1DIR|=BIT0;P4DIR|=BIT7;
    for(i=0;i<22000;i++);
    PUSHKEY=P1IFG&(~P1DIR);
    if((PUSHKEY&BIT1) == BIT1)
    {
    	P1IFG &= ~BIT1;                         // Clear P2.1 IFG
    	if(l==1)                                //l=1,进入手动增益模块
    	{
 //   		ADC12IE &= ~ADC12IE12;
    		P1OUT|=BIT0;
            P4OUT&=~BIT7;
            Picture_10();
            Picture_7();
            shoudongDAC();                       //参数为void，则必须有（），但里面不要写东西。否则是错的。

    	}
       if(l==2)                                  //l=2，进入自动增益模块
       {
    	    P2IE&=~BIT1;
        	P1OUT&=~BIT0;
            P4OUT|=BIT7;
            l=0;
            Picture_8();
            Picture_11();
            ADCautomatic();
        }
        l++;
      }
}

