#include<reg51.h>   
#define GPIO_KEY P1
#define uint unsigned int
#define uchar unsigned char
uchar KeyState;
uchar KeyValue;
void Delay(uint i)   
{
   while(i--);
}
void KeyDown();	
void KeyDown(void)
{
	uint a=0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
  {
		Delay(1000);
		if(GPIO_KEY!=0x0f)
		{
			KeyState=1;//?????
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			GPIO_KEY=0XF0;
			Delay(1000);
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<500)&&(GPIO_KEY!=0xf0))	 //??????
			{
				 Delay(1000);
				a++;
			}
			a=0;
		}
	}
}
