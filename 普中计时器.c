#include<reg51.h>
#define GPIO_DIG P0
#define uint unsigned int
#define uchar unsigned char
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit set=P1^0;
sbit add=P1^1;
sbit cut=P1^2;
sbit ok=P1^3;

uchar code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,};//0x77,0x7c,0x39,0x5e,0x79,0x71
uchar shi=0;
uchar fen=0;
uchar miao=0;
uchar aa,flag,cont,_shi,_fen,_miao;

bit flag1;	

uchar DisplayData[8];       //用来存位
void Tdisplay(uchar dat,uchar dat1,uchar dat2);
void Tdisplay1(uchar dat,uchar dat1,uchar dat2);
void anjian();
void Delay(uint i)           //延迟
{
   while(i--);
}
void DigDisplay();       //38译码器实现动态显示数码管
void time0Init()			//定时器0中断 中断方式一
{
	TMOD|=0x01;
	TH0=0xFC;				//1ms
	TL0=0x18;
	ET0=1;
	EA=1;
	TR0=1;
	
}

void main(void)
{
	time0Init();				
	while(1)
	{
		 anjian();									   	
       	if(flag==1)									 	
          	{			
                 if(flag1==1) Tdisplay1(_shi,_fen,_miao);		 	 
               	else Tdisplay(_shi,_fen,_miao);			
             } 			
				 else if(flag==2)						  	
                {			
                    if(flag1==1) Tdisplay1(_shi,_fen,_miao);		 	
                    else Tdisplay(_shi,_fen,_miao);		
               	}
				else if(flag==3)						  	
                {			
                    if(flag1==1) Tdisplay1(_shi,_fen,_miao);		 	
                    else Tdisplay(_shi,_fen,_miao);		
               	} 		
            else Tdisplay(shi,fen,miao); 
		DigDisplay();
	}	
}

void Tdisplay(uchar dat,uchar dat1,uchar dat2)
{
	DisplayData[1]=DIG_CODE[dat%10]+0x80;
	DisplayData[0]=DIG_CODE[dat/10];
	DisplayData[4]=DIG_CODE[dat1%10]+0x80;
	DisplayData[3]=DIG_CODE[dat1/10];
	DisplayData[7]=DIG_CODE[dat2%10];
	DisplayData[6]=DIG_CODE[dat2/10];

}
			
void Tdisplay1(uchar dat,uchar dat1,uchar dat2)
{
  	 
	if(flag1==1)								  	 
		{			
			if(flag==3)									
				{					
					DisplayData[1]=DIG_CODE[dat%10];  //时的个位
              	DisplayData[0]=DIG_CODE[dat/10];//		 	
			   }	 				
				else if(flag==2)							
					{				
						DisplayData[4]=DIG_CODE[dat1%10];  //·ÖµÄ¸öÎ»
	               DisplayData[3]=DIG_CODE[dat1/10];	//·ÖµÄÊ®Î»		
					}	
            else if(flag==1)							
					{				
						DisplayData[7]=DIG_CODE[dat2%10];   //ÃëµÄ¸öÎ»
	               DisplayData[6]=DIG_CODE[dat2/10];   //ÃëµÄÊ®Î»
					}						
		} 	 	
		else 		
			{			
					DisplayData[1]=DIG_CODE[dat%10]+0x80;
					DisplayData[0]=DIG_CODE[dat/10];
					DisplayData[4]=DIG_CODE[dat1%10]+0x80;
					DisplayData[3]=DIG_CODE[dat1/10];
					DisplayData[7]=DIG_CODE[dat2%10];
					DisplayData[6]=DIG_CODE[dat2/10];
          }	 


}

void anjian()
{
	if(set==0)									
    {											 
         Delay(200);		
          if(set==0)		 
            {			
               							 	
           		Tdisplay1(_shi,_fen,_miao);			
               if(flag<3) flag++;					 
					else  flag=1;
						while(!set);
				}	
	 }		
	 if(flag==0) 
		 Tdisplay(_shi,fen,miao);					 
	 else  Tdisplay1(_shi,_fen,_miao);						
	    if(flag==1)							 		
		 {				
			if(add==0)						  				 
			  {					
			  	Delay(200);				
				if(add==0)					
          {						
                while(!add)					
					Tdisplay1(_shi,_fen,_miao);	  					
					 _miao++;								
					 if(_miao==60) _miao=0;	  						
					 else if(_miao<0) _miao=59;					
					}			
			}						
			if(cut==0)			
          {				
             Delay(2);				
             if(cut==0)				
					 {					
						 while(!cut)					
							 Tdisplay1(_shi,_fen,_miao);					
						 _miao--;					
						 if(_miao==0) _miao=59;								
					 }			
			  }		
	    } 					
		 if(flag==2)							   			
			 {				
				 Delay(200);				 
				 if(add==0)				
              {									
              	Delay(200);				
               	if(add==0)				
							{						
								while(!add)					
									Tdisplay1(_shi,_fen,_miao);					
   								_fen++;					
   								if(_fen==60) _fen=0;				
								}			
	 	   		}						
					if(cut==0)			
                 {							
                   	Delay(200);				
                      if(cut==0)				
								 {					
									 while(!cut)					
										 Tdisplay1(_shi,_fen,_miao);					
									     _fen--;				
          									 if(_fen==0)	
													 _fen=59;					
									}			
						}			
				}
           if(flag==3)							   			
			 {				
				 Delay(200);				 
				 if(add==0)				
              {									
              	Delay(200);				
               	if(add==0)				
							{						
								while(!add)					
									Tdisplay1(_shi,_fen,_miao);					
   								_shi++;					
   								if(_shi==24) _shi=0;				
								}			
	 	   		}						
					if(cut==0)			
                 {							
                   	Delay(200);				
                      if(cut==0)				
								 {					
									 while(!cut)					
										 Tdisplay1(_shi,_fen,_miao);					
									     _shi--;				
          									 if(_shi==0)	
													 _shi=24;					
									}			
						}			
				}									
				 if(ok==0)				
					 {								
						 Delay(200);				
						 if(ok==0)				
							 {						
								 		
								 flag=0;
								shi=_shi;
								 fen=_fen;										
                          miao=_miao;						
								 Tdisplay(_shi,_fen,_miao);
                         while(!ok);									 
		                 }			
                 } 		
}	

void DigDisplay()
{
	uchar i;
		for(i=0;i<8;i++)
	{
		switch(i)	 		
{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//µÚÒ»Î»
			case(1):
				LSA=1;LSB=0;LSC=0; break;//µÚ¶þÎ»
			case(2):
				LSA=0;LSB=1;LSC=0; break;//µÚÈýÎ»
			case(3):
				LSA=1;LSB=1;LSC=0; break;//µÚËÄÎ»
			case(4):
				LSA=0;LSB=0;LSC=1; break;//µÚÎåÎ»
			case(5):
				LSA=1;LSB=0;LSC=1; break;//µÚÁùÎ»
			case(6):
				LSA=0;LSB=1;LSC=1; break;//µÚÆßÎ»
			case(7):
				LSA=1;LSB=1;LSC=1; break;//µÚ°ËÎ»	
		}
		GPIO_DIG=DisplayData[i];   
		Delay(100);              
		                       
         GPIO_DIG=0x00;       //ÏûÒþ
	}
}




void timer0() interrupt 1     //¶¨Ê±Æ÷ÖÐ¶Ï0·þÎñº¯Êý
{
	static uint i;
		
		TH0=0xFC;
	   TL0=0x18;
		i++;
	   cont++;	
	   if(cont==1000)	
			  {		
				   flag1=~flag1;	
				  cont=0;	
				}	
		if(i==1000)    //Ò»Ãë
		{
			i=0;
			miao++;
			if(miao==60)
			{
				miao=0;
				fen++;
				if(fen==60)
				{
					fen=0;
					shi++;
					if(shi==24)
					{
						shi=0;
					}
				}
			}
			
		}
      
}
