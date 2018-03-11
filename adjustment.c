#include <msp430f5529.h>
unsigned int g=0x40,k=0x05;


void adjustment1(unsigned int i)
{
	volatile unsigned char c[8],d[8],e,f;
	P1DIR|=BIT6; P2DIR|=BIT7;P3DIR|=BIT2+BIT3+BIT4;P4DIR|=BIT1+BIT2;P6DIR|=BIT6;
	//ǰһ��DAC�ĹܽŶ���
    P1DIR|=BIT2+BIT5;
    P2DIR|=BIT2;
    P7DIR|=BIT4;
    P3DIR|=BIT7;
    P4DIR|=BIT0+BIT3;
    P8DIR|=BIT2;                                // ��һ��DAC�ĹܽŶ���
	if(i==0)
	{
		                P1OUT&=~BIT6;
					    P2OUT|=BIT7;
					    P3OUT&=~(BIT3+BIT4);
					    P3OUT&=~BIT2;
					    P4OUT|=BIT1;
					    P4OUT&=~BIT2;
					    P6OUT&= ~BIT6;                                //״̬2��ǰDAC˥��1/40;


		               P1OUT&=~(BIT2+BIT5);
		               P7OUT&=~BIT4;
			           P2OUT|=BIT2;
			            P3OUT&=~BIT7;
			            P4OUT&=~(BIT0+BIT3);
			            P8OUT&=~BIT2;           //��ʼ�ǷŴ�4��
	}

	if(i==3)
	{
		f=g;
		for(e=0;e<8;e++)
		{
			c[e]=f%2;
			f=f/2;
		}
		if(c[0]==0)
			P8OUT&=~BIT2;
		else
			P8OUT|=BIT2;
		if(c[1]==0)
			P3OUT&=~BIT7;
		else
			P3OUT|=BIT7;
		if(c[2]==0)
			P4OUT&=~BIT0;
		else
			P4OUT|=BIT0;
		if(c[3]==0)
			P4OUT&=~BIT3;
		else
			P4OUT|=BIT3;
		if(c[4]==0)
			P1OUT&=~BIT2;
		else
			P1OUT|=BIT2;
		if(c[5]==0)
			P7OUT&=~BIT4;
		else
			P7OUT|=BIT4;
		if(c[6]==0)
			P2OUT&=~BIT2;
		else
			P2OUT|=BIT2;
		if(c[7]==0)
			P1OUT&=~BIT5;
		else
			P1OUT|=BIT5;

		f=k;
		for(e=0;e<8;e++)
		{
			c[e]=f%2;
			f=f/2;
		}
		if(c[0]==0)
			P4OUT&=~BIT1;
		else
			P4OUT|=BIT1;
		if(c[1]==0)
			P4OUT&=~BIT2;
		else
			P4OUT|=BIT2;
		if(c[2]==0)
			P2OUT&=~BIT7;
		else
			P2OUT|=BIT7;
		if(c[3]==0)
			P3OUT&=~BIT2;
		else
			P3OUT|=BIT2;
		if(c[4]==0)
			P6OUT&=~BIT6;
		else
			P6OUT|=BIT6;
		if(c[5]==0)
			P1OUT&=~BIT6;
		else
			P1OUT|=BIT6;
		if(c[6]==0)
			P3OUT&=~BIT3;
		else
			P3OUT|=BIT3;
		if(c[7]==0)
			P3OUT&=~BIT4;
		else
			P3OUT|=BIT4;
	}
	if(i==1)
	{
		if(g>0x00)
		{
		f=g-0x01;
		g=g-0x01;
		for(e=0;e<8;e++)
		{
			c[e]=f%2;
			f=f/2;
		}
		if(c[0]==0)
			P8OUT&=~BIT2;
		else
			P8OUT|=BIT2;
		if(c[1]==0)
			P3OUT&=~BIT7;
		else
			P3OUT|=BIT7;
		if(c[2]==0)
			P4OUT&=~BIT0;
		else
			P4OUT|=BIT0;
		if(c[3]==0)
			P4OUT&=~BIT3;
		else
			P4OUT|=BIT3;
		if(c[4]==0)
			P1OUT&=~BIT2;
		else
			P1OUT|=BIT2;
		if(c[5]==0)
			P7OUT&=~BIT4;
		else
			P7OUT|=BIT4;
		if(c[6]==0)
			P2OUT&=~BIT2;
		else
			P2OUT|=BIT2;
		if(c[7]==0)
			P1OUT&=~BIT5;
		else
			P1OUT|=BIT5;}
		if(g==0)
		{
			f=g;
					for(e=0;e<8;e++)
					{
						c[e]=f%2;
						f=f/2;
					}
					if(c[0]==0)
						P8OUT&=~BIT2;
					else P8OUT|=BIT2;
					if(c[1]==0)
						P3OUT&=~BIT7;
					else P3OUT|=BIT7;
					if(c[2]==0)
						P4OUT&=~BIT0;
					else P4OUT|=BIT0;
					if(c[3]==0)
						P4OUT&=~BIT3;
					else P4OUT|=BIT3;
					if(c[4]==0)
						P1OUT&=~BIT2;
					else P1OUT|=BIT2;
					if(c[5]==0)
						P7OUT&=~BIT4;
					else P7OUT|=BIT4;
					if(c[6]==0)
						P2OUT&=~BIT2;
					else P2OUT|=BIT2;
					if(c[7]==0)
						P1OUT&=~BIT5;
					else P1OUT|=BIT5;

		}
	}

	if(i==2)
	{
		if(g<0xff)
		{
		f=g+0x01;g=g+0x01;
		for(e=0;e<8;e++)
		{
			c[e]=f%2;
			f=f/2;
		}
		if(c[0]==0)
			P8OUT&=~BIT2;
		else P8OUT|=BIT2;
		if(c[1]==0)
			P3OUT&=~BIT7;
		else P3OUT|=BIT7;
		if(c[2]==0)
			P4OUT&=~BIT0;
		else P4OUT|=BIT0;
		if(c[3]==0)
			P4OUT&=~BIT3;
		else P4OUT|=BIT3;
		if(c[4]==0)
			P1OUT&=~BIT2;
		else P1OUT|=BIT2;
		if(c[5]==0)
		    P7OUT&=~BIT4;
		else P7OUT|=BIT4;
		if(c[6]==0)
			P2OUT&=~BIT2;
		else P2OUT|=BIT2;
		if(c[7]==0)
			P1OUT&=~BIT5;
		else P1OUT|=BIT5;}
		if(g==0xff)
		{
			f=g;
					for(e=0;e<8;e++)
					{
						c[e]=f%2;
						f=f/2;
					}
					if(c[0]==0)
						P8OUT&=~BIT2;
					else P8OUT|=BIT2;
					if(c[1]==0)
						P3OUT&=~BIT7;
					else P3OUT|=BIT7;
					if(c[2]==0)
						P4OUT&=~BIT0;
					else P4OUT|=BIT0;
					if(c[3]==0)
						P4OUT&=~BIT3;
					else P4OUT|=BIT3;
					if(c[4]==0)
						P1OUT&=~BIT2;
					else P1OUT|=BIT2;
					if(c[5]==0)
						P7OUT&=~BIT4;
					else P7OUT|=BIT4;
					if(c[6]==0)
						P2OUT&=~BIT2;
					else P2OUT|=BIT2;
					if(c[7]==0)
						P1OUT&=~BIT5;
					else P1OUT|=BIT5;

		}

	}
	if(i==4)
	{               //ǰ˥��DAC���дֵ�����Ŵ�DAC����ϸ�����ֵ���ʱ��Ͳ�Ҫ��ͼ����ϸ��
		                  //�ȴ��ֵ����ȶ����ٽ���ϸ��������ֵ�����ϸ����ʹ�õ�ȻҲ�����ϵͳ�Ĳ��ȶ�����
		if(k<0xff)        //���ڱ�ϵͳ�����ڣ��������������йأ������ں���ᱶ�Ŵ����Բ��ʺ�ʹ�ã������ϵͳ���źŴ��ʱ��������
		{f=k+0x01;k=k+0x01;
				for(e=0;e<8;e++)
				{
					c[e]=f%2;
					f=f/2;
				}
				if(c[0]==0)
					P4OUT&=~BIT1;
				else P4OUT|=BIT1;
				if(c[1]==0)
					P4OUT&=~BIT2;
				else P4OUT|=BIT2;
				if(c[2]==0)
					P2OUT&=~BIT7;
				else P2OUT|=BIT7;
				if(c[3]==0)
					P3OUT&=~BIT2;
				else P3OUT|=BIT2;
				if(c[4]==0)
					P6OUT&=~BIT6;
				else P6OUT|=BIT6;
				if(c[5]==0)
					P1OUT&=~BIT6;
				else P1OUT|=BIT6;
				if(c[6]==0)
					P3OUT&=~BIT3;
				else P3OUT|=BIT3;
				if(c[7]==0)
					P3OUT&=~BIT4;
				else P3OUT|=BIT4;}
		if(k==0xff)
		{                  f=k;
			              for(e=0;e<8;e++)
							{
								c[e]=f%2;
								f=f/2;
							}
							if(c[0]==0)
								P4OUT&=~BIT1;
							else P4OUT|=BIT1;
							if(c[1]==0)
								P4OUT&=~BIT2;
							else P4OUT|=BIT2;
							if(c[2]==0)
								P2OUT&=~BIT7;
							else P2OUT|=BIT7;
							if(c[3]==0)
								P3OUT&=~BIT2;
							else P3OUT|=BIT2;
							if(c[4]==0)
								P6OUT&=~BIT6;
							else P6OUT|=BIT6;
							if(c[5]==0)
								P1OUT&=~BIT6;
							else P1OUT|=BIT6;
							if(c[6]==0)
								P3OUT&=~BIT3;
							else P3OUT|=BIT3;
							if(c[7]==0)
								P3OUT&=~BIT4;
							else P3OUT|=BIT4;
		}
		_delay_cycles(2000);
	}
	if(i==5)
		{
		         if(k>0x04)
			      {f=k-0x01;k=k-0x01;
					for(e=0;e<8;e++)
					{
						c[e]=f%2;
						f=f/2;
					}
					if(c[0]==0)
						P4OUT&=~BIT1;
					else P4OUT|=BIT1;
					if(c[1]==0)
						P4OUT&=~BIT2;
					else P4OUT|=BIT2;
					if(c[2]==0)
						P2OUT&=~BIT7;
					else P2OUT|=BIT7;
					if(c[3]==0)
						P3OUT&=~BIT2;
					else P3OUT|=BIT2;
					if(c[4]==0)
						P6OUT&=~BIT6;
					else P6OUT|=BIT6;
					if(c[5]==0)
						P1OUT&=~BIT6;
					else P1OUT|=BIT6;
					if(c[6]==0)
						P3OUT&=~BIT3;
					else P3OUT|=BIT3;
					if(c[7]==0)
						P3OUT&=~BIT4;
					else P3OUT|=BIT4;}
		         if(k==0x04)
		         {
		        	 f=k;
		        	 					for(e=0;e<8;e++)
		        	 					{
		        	 						c[e]=f%2;
		        	 						f=f/2;
		        	 					}
		        	 					if(c[0]==0)
		        	 						P4OUT&=~BIT1;
		        	 					else P4OUT|=BIT1;
		        	 					if(c[1]==0)
		        	 						P4OUT&=~BIT2;
		        	 					else P4OUT|=BIT2;
		        	 					if(c[2]==0)
		        	 						P2OUT&=~BIT7;
		        	 					else P2OUT|=BIT7;
		        	 					if(c[3]==0)
		        	 						P3OUT&=~BIT2;
		        	 					else P3OUT|=BIT2;
		        	 					if(c[4]==0)
		        	 						P6OUT&=~BIT6;
		        	 					else P6OUT|=BIT6;
		        	 					if(c[5]==0)
		        	 						P1OUT&=~BIT6;
		        	 					else P1OUT|=BIT6;
		        	 					if(c[6]==0)
		        	 						P3OUT&=~BIT3;
		        	 					else P3OUT|=BIT3;
		        	 					if(c[7]==0)
		        	 						P3OUT&=~BIT4;
		        	 					else P3OUT|=BIT4;
		         }
		         _delay_cycles(2000);
		}
	_delay_cycles(17000);
	}
