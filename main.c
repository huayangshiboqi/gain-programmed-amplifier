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
      P1DIR&=~BIT1;                         //��P1.1������Ϊ���뷽ʽ
      _enable_interrupts();                 //ʹ�����ж�
      P1REN|=BIT1;                          //ʹ��P1.1�����������Ĵ���
      P1OUT |=BIT1;                         //��P1.1����Ϊ��������
      P1IES |=BIT1;                         //��P1.1�����½��ش����ж�
      P1IFG&=~BIT1;                         //���P1.1�жϱ�־λ
      P1IE|=BIT1;                           //ʹ��P1.1�ж�
}


// �����ҵ��жϳ���
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
    	if(l==1)                                //l=1,�����ֶ�����ģ��
    	{
 //   		ADC12IE &= ~ADC12IE12;
    		P1OUT|=BIT0;
            P4OUT&=~BIT7;
            Picture_10();
            Picture_7();
            shoudongDAC();                       //����Ϊvoid��������У����������治Ҫд�����������Ǵ�ġ�

    	}
       if(l==2)                                  //l=2�������Զ�����ģ��
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

