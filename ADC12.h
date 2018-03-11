#ifndef __ADC12_H__
#define __ADC12_H__
#include<msp430f5529.h>

//=================���Ͷ���====================
#ifndef __UNSIGNED_TYPES__
#define __UNSIGNED_TYPES__

typedef unsigned char uchar;
typedef unsigned int uint;

#endif
//==========================================

//==============ADC12����ͨ��==================
#ifndef __ADC12_INCH__
#define __ADC12_INCH__

#define ADC12_INCH0			(1)
#define ADC12_INCH1			(2)
#define ADC12_INCH2			(3)
#define ADC12_INCH3			(4)
#define ADC12_INCH4			(5)
#define ADC12_INCH5			(6)
#define ADC12_INCH6			(7)
#define ADC12_INCH7			(8)
#define ADC12_INCH8			(9)
#define ADC12_INCH9			(10)
#define ADC12_INCH10		(11)
#define ADC12_INCH11		(12)
#define ADC12_INCH12		(13)
#define ADC12_INCH13		(14)
#define ADC12_INCH14		(15)
#define ADC12_INCH15		(16)

#endif
//==========================================

/*****************���ܺ���*********************/
//��ͨ����β���
//ͨ������ inch
//�ο���ѹ AVCC AVSS
//����ʱ�� ADC12OSC
//�����ź� ADC12SC
//������ʱʱ�� 64*ADC12CLK
//�������ݼĴ���ADC12MEM(inch)
//Notes:
//	�����������ã� IO�˿�
//			  ADC12�ж������� ADC12IV ADC12MEMx
void ADC12_SET_SINGLE_REPEATED(uchar inch);

//��ͨ����β���(2ͨ��)
//ͨ������ inch1 inch2
//�ο���ѹ AVCC AVSS
//����ʱ�� SMCLK
//�����ź� ADC12SC
//������ʱʱ�� 16*ADC12CLK
//�������ݼĴ��� ADC12MEM(inch1)  ADC12MEM(inch2)
//Notes:
//	�����������ã� IO�˿�
//			  ADC12�ж������� ADC12IV ADC12MEMxs
void ADC12_SET_SEQUENCE_REPEATED(uchar inch1,uchar inch2);

#endif
