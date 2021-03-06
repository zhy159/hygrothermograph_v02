#include "H/Function_Init.H"

void Timer_Init(void);
uint Delay_S;	//定义传感器的读取时间,防止没读完就取数
uint Delay_jg;  //定义读取的间隔
/*****************************************************
*函数名称：void Timer_Test(void);
*函数功能：T0/T1/T2测试
*入口参数：void
*出口参数：void
*****************************************************/
void Timer_Test(void)
{
	Timer_Init();


}
/*****************************************************
*函数名称：void Timer_Init(void)
*函数功能：T0/T1/T2初始化
*入口参数：void
*出口参数：void
*****************************************************/
void Timer_Init(void)
{ 
	TMCON |= 0X01;    //Timer0选择时钟Fsys
	
	//T0设置
	TMOD |= 0x01;                 //0000 0001;Timer0设置工作方式1
	TL0 = (65536 - 16000)%256;    //溢出时间：时钟为Fsys(16M)，则16000*（1/Fsys）=1ms;
	TH0 = (65536 - 16000)/256;
	TR0 = 0;
	ET0 = 1;//定时器0允许
	TR0 = 1;//打开定时器0    
	EA = 1;	
}

/**************************************************
*函数名称：void timer0/1/2/3/4() interrupt 1/3/5/13/14
*函数功能：定时器中断产生方波
*入口参数：void
*出口参数：void
**************************************************/
void timer0() interrupt 1
{
    TL0 = (65536 - 16000)%256;
	TH0 = (65536 - 16000)/256;
	Delay_jg++;
	if(Delay_S<100)  //等待多少时间读取温湿度
	{
		Delay_S++; 	
	}
	else
	{
	Delay_S=0;
	test_bit=1;
	}

	
}
