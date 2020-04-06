#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit wei1=P3^0; 
sbit wei2=P3^1; 
sbit wei3=P3^2; 
sbit wei4=P3^3; 
sbit set=P1^0;
sbit add=P1^1;
sbit cut=P1^2;
sbit ok=P1^3;
uchar code duan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
/******************************************************************************
flag = 1秒的设置   flag = 2 分的设置
 fen miao 正常情况   _fen _miao 闪烁时  aa时间的计时   count闪烁的计时
flag1 用来判断此时是否处于按键设定状态
******************************************************************************/ 
uchar aa,miao,fen,flag,cont,_miao,_fen;

bit flag1;	
void delay(uchar t)

{

	uchar i,j;

	for(i=t;i>0;i--)

		for(j=124;j>0;j--);
}
void display(uchar dat,uchar dat1)   //正常状态下的显示

{

	P2=duan[dat/10];
	wei1=1;	
	delay(5);
	wei1=0;
	
	P2=duan[dat%10]+0x80;    //+0x80就是打开了数码管最后一位 即点儿亮
        wei2=1;	
	delay(5);
	wei2=0;	
	
	P2=duan[dat1/10];
        wei3=1;	
	delay(5);
	wei3=0;		
	
	P2=duan[dat1%10];
        wei4=1;	
	delay(5);
	wei4=0;		
	
}
void display1(uchar dat,uchar dat1)   //按键按下的显示
{		 
	if(flag1==1)								  	 
		{			
			if(flag==2)									
				{					
					P2=duan[dat1/10];                 			
                                        wei3=1;										
					delay(5);								
					wei3=0;								
					P2=duan[dat1%10];                				
					wei4=1;							 			
					delay(5);								
					wei4=0;						
			   }	 				
				else if(flag==1)							
					{				
						P2=duan[dat/10];                		
						wei1=1;										
						delay(5);									
						wei1=0;												
						P2=duan[dat%10]+0x80;           				
						wei2=1;										
						delay(5);									
						wei2=0;						
					}		
		} 		
		else 		
			{			
				P2=duan[dat/10];               
 				wei1=1;									
				delay(5);								
				wei1=0;										
				P2=duan[dat%10]+0x80;
				delay(5);								
				wei2=0;							
				P2=duan[dat1/10];                 
				wei3=1;							 			
				delay(5);								
				wei3=0;							
				P2=duan[dat1%10];                 			
                                wei4=1;							 	
            	                delay(5);						 			
                                wei4=0;	
                           }	 

} 
	
void init()                            //定时器0中断
{	      
	TMOD=0X01;   					
	TH0=(65535-50000)/256;   //     定时50ms:   (2^16-50ms/1us)/256
	TL0=(65535-50000)%256;			
	ET0=1;							 
	EA=1;		
	TR0=1;	
}
	
void anjian()
{
	if(set==0)									
        {											 
         delay(2);		
          if(set==0)		 
            {			
               							 	
           	display1(_fen,_miao);			
               if(flag<2) flag++;					 
		else  flag=1;
		while(!set);
	     }	
	 }		
	 if(flag==0) 
         display(fen,miao);					 
	 else display1(_fen,_miao);						
	 if(flag==1)							 		
		{				
			if(add==0)						  				 
			{					
				delay(2);				
				if(add==0)					
             			  {						
               				 while(!add)					
					 display1(_fen,_miao);	  					
					 _miao++;								
					 if(_miao==60) _miao=0;	  						
					 else if(_miao<0) _miao=59;					
				   }			
			}						
			if(cut==0)			
         		 {				
             			delay(2);				
             				if(cut==0)				
					 {					
						 while(!cut)					
							 display1(_fen,_miao);					
						 _miao--;					
						 if(_miao==0) _miao=59;								
					 }			
			  }		
	          } 					
		 if(flag==2)							   			
			 {				
				 delay(2);				 
				 if(add==0)				
                                    {									
					delay(2);				
					if(add==0)				
					{						
						while(!add)					
					       display1(_fen,_miao);					
						_fen++;					
						if(_fen==60) _fen=0;				
					}			
	 	   		}						
		if(cut==0)			
                 {							
                   	delay(2);				
                      if(cut==0)				
			 {					
				 while(!cut)					
				 display1(_fen,_miao);					
				     _fen--;				
					 if(_fen==0)	
					    _fen=59;					
			}			
	           }			
	}					
				 if(ok==0)				
					 {								
						 delay(2);				
						 if(ok==0)				
						 {						
								 		
						    flag=0;					  	
						    fen=_fen;										
                                                    miao=_miao;						
						   display(fen,miao);
                                                   while(!ok);									 
		                                 }			
                 	} 		
}	
	
void main()
{ 		
    init();												
     while(1)	
    {		
        anjian();									   	
       	if(flag==1)									 	
          	{			
                 if(flag1==1) display1(_fen,_miao);		 	 
               	else display(_fen,_miao);			
                } 			
				 else if(flag==2)						  	
                {			
                    if(flag1==1) display1(_fen,_miao);		 	
                    else display(_fen,_miao);		
               	} 		
            else display(fen,miao); 	
     }
}

void T0_int0() interrupt 1
{	
     TH0=(65535-50000)/256;		
   	TL0=(65535-50000)%256;			
      	aa++;							 
    	cont++;	
	    if(cont==10)	
	     {		
		   flag1=!flag1;	
		  cont=0;	
	      }	
	   if(aa==20)	
              {		
		  miao++;								
                  aa=0;						  		
       
                  if(miao==60)				 	
                     {			
                        fen++;		
                       	miao=0;		
			if(fen==60)							
			fen=0;		
                      }	
               }
}	
	
