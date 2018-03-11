#include <msp430f5529.h>
#include "ADC12.h"

//==============变量定义===================
#define Num_of_Results 250
volatile unsigned int a[Num_of_Results];
volatile unsigned int A3results[Num_of_Results];    //双通道A3 A4取采样值得数组
volatile unsigned int A4results[Num_of_Results];
                                                   //A3 P6.3接衰减，A4 P6.4接放大。
float temp1=0.0,temp2=0.0;

void ADC12_IO_Init();                              //定义ADC采样管脚
void adjustment1(unsigned int i);
unsigned int i=0;

//==============主函数====================
void ADCautomatic()
{
    adjustment1(0);
	WDTCTL = WDTPW+WDTHOLD;						   // Stop watchdog timer

	ADC12_IO_Init();
	ADC12_SET_SEQUENCE_REPEATED(ADC12_INCH3,ADC12_INCH4);//多通道循环检测

	_EINT();									// Enable interrupt
	_NOP();										// For debugger

	while(1)
	{
		if(temp1<0.1)                    //解决两个DAC同时调code值，出现的不稳定，
			                             //办法：先调整一个DAC，让第一路输出达到预想值，之后再调整第二个DAC，输出最终值
		{
			adjustment1(4);              //适当的延迟可以缓解数字电路与模拟电路速度不匹配的情况，缓解跳变很大的情况

		}
		if(((temp1>0.1)||(temp1==0.1))&&((temp1<0.2)||(temp1==0.2)))
		{                               //temp1前一个DAC的调节对后一个DAC的影响：
			 if(temp2<0.23)             //如果前一个DAC不稳，且处在检测边缘，那么，就会在后一个DAC调节的同时，前一个DAC也会出现加或减的情况，这样在后一个DAC确定了某一放大倍数时，前一个DAC的加减就会作用在最后的输出波形上，造成突然地升高或降低。
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
		//ADC12SC,ADC12ENC两个对ADC进行控制。
		_delay_cycles(1000);
	}


}


//=============函数定义===================
/**********ADC12 IO端口设置***************/
void ADC12_IO_Init()
{
	P6SEL |= 0x18;								// Enable A/D channel
}


//=============中断向量====================
/**************ADC12中断*****************/
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{

	static unsigned char index = 0;
	//注意：变量类型的选择会限制变量的取值范围，在此index的范围0~255，所以数组的个数不能超过255！否则当你要用全这些数组时会发生有你不想要的结果
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
		if(index==0)                           //注意：index,数据类型取值范围的确定
		{
			a[1]=A3results[index];
			a[2]=A4results[index];
		}
		if((index>0)&&(index<250))             //注意：条件的判定语句，一定要保证符合你想要的结果
		{
			if(A3results[index]>a[1])
  	  				a[1]=A3results[index];
			if(A4results[index]>a[2])
				a[2]=A4results[index];
		}
		if(index==249)                          //注意：范围的确定，不然永远进不了语句
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
  		if(index==249)                          //注意：范围的确定，不然永远进不了语句
  		{	temp=(long)(a[0])*3.3/4095.0;
  			final=temp;}
  		index++;                              	// Increment results index, modulo; Set Breakpoint1 here
  		if (index == 250)                       //注意：数组的个数有了限制250.所以index的取值范围为0~499！并且在实际算范围时一定要注意。
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
  	  		if (index == 250)                       //注意：数组的个数有了限制250.所以index的取值范围为0~499！并且在实际算范围时一定要注意。
  	  		{
  	  			index = 0;
  	  		}
  	  		if(index==0)
  	  		ADC12CTL0 &=~ 0x0003;
     _delay_cycles(2);
}
