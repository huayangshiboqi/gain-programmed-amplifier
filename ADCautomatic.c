#include <msp430f5529.h>
#include "ADC12.h"

//==============��������===================
#define Num_of_Results 250
volatile unsigned int a[Num_of_Results];
volatile unsigned int A3results[Num_of_Results];    //˫ͨ��A3 A4ȡ����ֵ������
volatile unsigned int A4results[Num_of_Results];
                                                   //A3 P6.3��˥����A4 P6.4�ӷŴ�
float temp1=0.0,temp2=0.0;

void ADC12_IO_Init();                              //����ADC�����ܽ�
void adjustment1(unsigned int i);
unsigned int i=0;

//==============������====================
void ADCautomatic()
{
    adjustment1(0);
	WDTCTL = WDTPW+WDTHOLD;						   // Stop watchdog timer

	ADC12_IO_Init();
	ADC12_SET_SEQUENCE_REPEATED(ADC12_INCH3,ADC12_INCH4);//��ͨ��ѭ�����

	_EINT();									// Enable interrupt
	_NOP();										// For debugger

	while(1)
	{
		if(temp1<0.1)                    //�������DACͬʱ��codeֵ�����ֵĲ��ȶ���
			                             //�취���ȵ���һ��DAC���õ�һ·����ﵽԤ��ֵ��֮���ٵ����ڶ���DAC���������ֵ
		{
			adjustment1(4);              //�ʵ����ӳٿ��Ի������ֵ�·��ģ���·�ٶȲ�ƥ����������������ܴ�����

		}
		if(((temp1>0.1)||(temp1==0.1))&&((temp1<0.2)||(temp1==0.2)))
		{                               //temp1ǰһ��DAC�ĵ��ڶԺ�һ��DAC��Ӱ�죺
			 if(temp2<0.23)             //���ǰһ��DAC���ȣ��Ҵ��ڼ���Ե����ô���ͻ��ں�һ��DAC���ڵ�ͬʱ��ǰһ��DACҲ����ּӻ��������������ں�һ��DACȷ����ĳһ�Ŵ���ʱ��ǰһ��DAC�ļӼ��ͻ�������������������ϣ����ͻȻ�����߻򽵵͡�
		     {
			    adjustment1(1);
		     }
			 if(((temp2>0.23)||(temp2==0.23))&&((temp2<0.26)||(temp2==0.26)))
			     adjustment1(3);
			  if(temp2>0.26)
			  {  adjustment1(2);}
		}
		if(temp1>0.2)
			adjustment1(5);
		ADC12CTL0 |=0x0003;
		//ADC12SC,ADC12ENC������ADC���п��ơ�
		_delay_cycles(1000);
	}


}


//=============��������===================
/**********ADC12 IO�˿�����***************/
void ADC12_IO_Init()
{
	P6SEL |= 0x18;								// Enable A/D channel
}


//=============�ж�����====================
/**************ADC12�ж�*****************/
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{

	static unsigned char index = 0;
	//ע�⣺�������͵�ѡ������Ʊ�����ȡֵ��Χ���ڴ�index�ķ�Χ0~255����������ĸ������ܳ���255��������Ҫ��ȫ��Щ����ʱ�ᷢ�����㲻��Ҫ�Ľ��
	switch(__even_in_range(ADC12IV,36))
	{
	case  0: break;                           	// Vector  0:  No interrupt
  	case  2: break;                           	// Vector  2:  ADC overflow
  	case  4: break;                           	// Vector  4:  ADC timing overflow
  	case  6: break;                           	// Vector  6:  ADC12IFG0
  	case  8: break;                           	// Vector  8:  ADC12IFG1
  	case 10: break;                           	// Vector 10:  ADC12IFG2
  	case 12:break;                            	// Vector 12:  ADC12IFG3
  	case 14:                            	// Vector 14:  ADC12IFG4
  	{
  		A3results[index] = ADC12MEM3;   A4results[index] = ADC12MEM4;       	// Move results
		if(index==0)                           //ע�⣺index,��������ȡֵ��Χ��ȷ��
		{
			a[1]=A3results[index];
			a[2]=A4results[index];
		}
		if((index>0)&&(index<250))             //ע�⣺�������ж���䣬һ��Ҫ��֤��������Ҫ�Ľ��
		{
			if(A3results[index]>a[1])
  	  				a[1]=A3results[index];
			if(A4results[index]>a[2])
				a[2]=A4results[index];
		}
		if(index==249)                          //ע�⣺��Χ��ȷ������Ȼ��Զ���������
		{
			temp1=(long)(a[1])*3.3/4095.0;
			temp2=(long)(a[2])*3.3/4095.0;
		}		                             	// Increment results index, modulo; Set Breakpoint1 here
		break;
  	}
  	case 16: break;                           	// Vector 16:  ADC12IFG5
 	case 18: break;                           	// Vector 18:  ADC12IFG6
 	case 20: break;                           	// Vector 20:  ADC12IFG7
 	case 22: break;                           	// Vector 22:  ADC12IFG8
 	case 24: break;                           	// Vector 24:  ADC12IFG9
 	case 26: break;                           	// Vector 26:  ADC12IFG10
 	case 28: break;                           	// Vector 28:  ADC12IFG11
 	case 30:
 /*	{	results[index] = ADC12MEM12;          	// Move results
  		if(index==0)
  			a[0]=results[index];
  		if((index>0)&&(index<250))
  			if(results[index]>a[0])
  				a[0]=results[index];
  		if(index==249)                          //ע�⣺��Χ��ȷ������Ȼ��Զ���������
  		{	temp=(long)(a[0])*3.3/4095.0;
  			final=temp;}
  		index++;                              	// Increment results index, modulo; Set Breakpoint1 here
  		if (index == 250)                       //ע�⣺����ĸ�����������250.����index��ȡֵ��ΧΪ0~499��������ʵ���㷶Χʱһ��Ҫע�⡣
  		{
  			index = 0;
  		}
 		break;   } */
 		break;                                  // Vector 30:  ADC12IFG12
 	case 32: break;                           	// Vector 32:  ADC12IFG13
 	case 34:break;                           	// Vector 34:  ADC12IFG14

 	 case 36:  break;                            // Vector 36:  ADC12IFG15
 	 default: break;}

	   index=index+1;                              	// Increment results index, modulo; Set Breakpoint1 here
  	  		if (index == 250)                       //ע�⣺����ĸ�����������250.����index��ȡֵ��ΧΪ0~499��������ʵ���㷶Χʱһ��Ҫע�⡣
  	  		{
  	  			index = 0;
  	  		}
  	  		if(index==0)
  	  		ADC12CTL0 &=~ 0x0003;
     _delay_cycles(2);
}
