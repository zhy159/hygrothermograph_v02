#ifndef _Function_Init_H_
#define _Function_Init_H_

#include "SC95F761x_C.H"
#include "intrins.H"
#define uchar unsigned char
#define uint unsigned int
extern uchar Uart_data;			//���ڽ�����ʱ����
extern uchar temp_H;			//�¶�ֵ��8λ
extern uchar temp_L;			//�¶�ֵ��8λ
extern uchar humid_z;			//ʪ��ֵ
extern uchar sd_ztxh;    		//�����յ���״̬��ű���   

extern bit test_bit; 			//�����ⲿ���崫���������־λ
extern uint Delay_jg;  			//�����ⲿ�����ȡ�ļ��
extern uint Delay_S;


extern bit UartSendFlag; 		//�����жϱ�־λ
extern bit UartReceiveFlag;		//�����жϱ�־λ
extern bit fs_temp;				//Ϊ�����ı���

extern void IO_Init(void);

extern	void tuya_sjcl(void);				//Ϳѻ���ݴ���

extern void Timer_Test(void);
extern void Uart_Init(uint Freq,unsigned long int baud);		//��ʼ�����ڲ��趨 ʱ��Ƶ�� �� ������
extern void Uart_Temp(void);									//�����ϱ���ʪ��
extern uchar jszl_qf(void);										//�յ��������жϺ���
//extern void SSI0_Test(void);
//extern void SSI1_Test(void);

extern void SSI2_Test(void);									//I2C��SHT30ͨ�Ų���ʪ����
extern void SSI2_R(void);
extern void TWI2_Init(void);																
extern void Uart_temp_up(void);		//�ϴ��¶�	
extern void Uart_humid_up(void);	//�ϴ�ʪ��	

extern char temp_shiwei;		//�¶�ʮλ
extern char temp_gewei; 		//�¶�ʮλ��λ
extern char temp_xiaoshu; 		//�¶�ʮλС��λ

extern char humid_shiwei;		//ʪ��ʮλ
extern char humid_gewei;		//ʪ�ȸ�λ

extern void Delay(uint time);  

extern uchar tuya_DataTab[15];	//����һ���յ�ģ������ݱ���
extern void Uart_sxt(void);		//�յ��������ظ� 
extern void Uart_hxt(void);		//�յ�һ�����������ظ�
extern void Uart_xtxx(void);	//MCU�ϱ�ID MCU�汾 ������ʽ	,ϵͳ��Ϣ
extern void Uart_xtmk(void);	//�ظ�ΪMCU�ϱ���ģ����ϴ���
extern void Uart_wififf(void);	//ģ�鱨��WiFi ����״̬�յ���MCU�ظ�

extern void OLED_Init(void);	//OLED��ʼ��
extern void OLED_WR_Byte(uchar dat,uchar cmd);	//��OLEDд��һ���ֽ����ݻ�ָ�� cmd��1��д�����ݣ�0��д������
extern void Write_IIC_Data(uchar IIC_Data);	  			//д����
extern void  Write_IIC_Command(uchar IIC_Command);	  	//д��ָ��
extern void OLED_ShowString(uchar x,uchar y,uchar *chr);
//extern void OLED_ShowChar(uchar x,uchar y,uchar chr);


extern void OLED_ShowString1(uchar x,uchar y);//��ʾ�¶Ⱥ���
extern void OLED_ShowString2(uchar x,uchar y);//��ʾʪ�Ⱥ���
extern void OLED_ShowChar(uchar x,uchar y,uchar chr);





#endif