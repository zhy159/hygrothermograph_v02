 #include"H/OledFont.h"
 #include "H/Function_Init.H"

 #define OLED_CMD  0	//д����
 #define OLED_DATA 1	//д����
 #define SIZE 16		//�ַ��ߴ�
 #define Max_Column	128 //�������

extern void OLED_ShowString(uchar x,uchar y,uchar *chr);
extern void OLED_ShowChar(uchar x,uchar y,uchar chr);



//************��OLEDд��һ���ֽ����ݻ�ָ�� cmd��1��д�����ݣ�0��д������**************************************
void OLED_WR_Byte(uchar dat,uchar cmd)
{
	if(cmd) 
	{
       Write_IIC_Data(dat); //д������
	}
	else
	{
       Write_IIC_Command(dat); //д������
	}
}
//*****************����*****************
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //�������
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //��0~7ҳ����д��
		OLED_WR_Byte (0x00,OLED_CMD);      //�е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //�иߵ�ַ  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); //д�� 0 ����
	}
}
//********************����ԭ��*******************
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);				//д��  ҳ��ַ   B0��B7
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);	//д���и�4λ��ַ
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);  		//д���е�4λ��ַ+1
}
//******************ָ����������ʾ�ַ���************************************************
void OLED_ShowString(uchar x,uchar y,uchar *chr)
{
	uchar j=0; //�������
	while (chr[j]!='\0') //����������һ���ַ�
	{		
		OLED_ShowChar(x,y,chr[j]); 	//��ʾ�ַ�
			x+=8; 					//������8 ��һ���ַ�������ռ8
		if(x>120){x=0;y+=2;} 		//���x����128���л�ҳ���Ӹ�ҳ�ĵ�һ����ʾ
			j++; 					//��һ���ַ�
	}
}

 //******************************���ַ�*************************88
void OLED_ShowChar(uchar x,uchar y,uchar chr)
{      	
		uchar c=0,i=0;	
		c=chr-' ';									//��ȡ�ַ���ƫ����	
		if(x>Max_Column-1){x=0;y=y+2;} 				//������鳬���˷�Χ128���ʹ���2ҳ�ĵ�0�п�ʼ
		if(SIZE ==16) 								//�ַ���С���Ϊ 16 = 8*16
			{
			OLED_Set_Pos(x,y);						//��x y ��ʼ����
			for(i=0;i<8;i++)  						//ѭ��8�� ռ8��
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); 	//�ҳ��ַ� c ������λ�ã����ڵ�һҳ���л���
			OLED_Set_Pos(x,y+1); 					//ҳ����1
			for(i=0;i<8;i++)  //ѭ��8��
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA); //�ѵڶ�ҳ����������
			}

}

  //*/

 void OLED_Init(void)//OLED��ʼ��
{
	OLED_WR_Byte(0xAE,OLED_CMD);//�ر���ʾ	 ��ַAE������0	
	OLED_WR_Byte(0x2e,OLED_CMD);//�رչ���
	OLED_WR_Byte(0x00,OLED_CMD);//���õ��е�ַ
	OLED_WR_Byte(0x10,OLED_CMD);//���ø��е�ַ
	OLED_WR_Byte(0x40,OLED_CMD);//������ʼ�е�ַ  40~7FH
	OLED_WR_Byte(0xB0,OLED_CMD);//����ҳ��ַ

	OLED_WR_Byte(0x81,OLED_CMD); // �Աȶ����ã�����������
	OLED_WR_Byte(0xFF,OLED_CMD);//  1~255  

	OLED_WR_Byte(0xA0,OLED_CMD);//X��(����)�����벻��������,Ϊ0XA0��0XA1
	OLED_WR_Byte(0xA7,OLED_CMD);//��ʾ�����뷴ת���ã�0xa7����Ϊ0��1��   0xa6����Ϊ1��0��

	OLED_WR_Byte(0xA8,OLED_CMD);//��������·��(��һ������)
	OLED_WR_Byte(0x3F,OLED_CMD);//1/64duty	 Y��ĵ���,Ҳ���Ƕ�����
	
	OLED_WR_Byte(0xC0,OLED_CMD);//Ϊ0xC0:��COM0��COM[N-1]ɨ��   Ϊ0xC8:COM[N-1]~COM0ɨ�� �ı�����ɨ�跽ʽ,�ı�ʱ��ʾ���ַ�Ҳ�᾵��,��λ�ò���
															   //��һ��ΪY��(����)�����벻��������
	OLED_WR_Byte(0xD3,OLED_CMD);//������ʾƫ��
	OLED_WR_Byte(0x00,OLED_CMD);//��ƫ��
	
	OLED_WR_Byte(0xD5,OLED_CMD);//����������Ƶ��Ĭ�ϣ�
	OLED_WR_Byte(0xF0,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//���� area color mode off��û�У�
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD6,OLED_CMD);//�Ŵ���ʾ
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//���� Pre-Charge Period��Ĭ�ϣ�
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//���� com pin configuartion��Ĭ�ϣ�
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//���� Vcomh���ɵ������ȣ�Ĭ�ϣ�
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//����OLED��ɱ�
	OLED_WR_Byte(0x14,OLED_CMD);//����ʾ
	
	OLED_WR_Byte(0xA4,OLED_CMD);//����ȫ��ȫ��:0xa4ΪRAM������ʾ   0xa5����ȫ��
	OLED_WR_Byte(0xA6,OLED_CMD);//��ʾ�����뷴ת���ã�0xa7����Ϊ0��1��   0xa6����Ϊ1��0�� 
	
//	OLED_WR_Byte(0x23,OLED_CMD);//������˸
//	OLED_WR_Byte(0x00,OLED_CMD);//

 //**********������ˮƽ����������*****************************
/*	OLED_WR_Byte(0x27,OLED_CMD);//ˮƽ�������	 0X26:�������ҹ��� 0X27: �����������
	OLED_WR_Byte(0x00,OLED_CMD);//�����ֽ�
	OLED_WR_Byte(0x06,OLED_CMD);//��ʼҳ(�к�0~7��8��)	 �п������й�ͬ��һ���ַ�,Ҫע��һ�����,����......
	OLED_WR_Byte(0x00,OLED_CMD);//����ʱ����
	OLED_WR_Byte(0x07,OLED_CMD);//��ֹҳ(�к�0~7��8��
	OLED_WR_Byte(0x00,OLED_CMD);//�����ֽ�
	OLED_WR_Byte(0xFF,OLED_CMD);//�����ֽ� 
	OLED_WR_Byte(0x2F,OLED_CMD);//��������	*/

	OLED_WR_Byte(0xAF,OLED_CMD);//����OLED�����ʾ
	OLED_Clear();        //����
	OLED_Set_Pos(0,0); 	 //����
}


 void OLED_ShowString1(uchar x,uchar y)		//��ʾ�¶�
{	// OLED_ShowChar(x,y,45);				//��ʾ����
	if(fs_temp)								//����¶�Ϊ��
	{OLED_ShowChar(x-8,y,45);}				//��ʾ����
	else								   	
	{OLED_ShowChar(x-8,y,32);}				//������ʾ����
	if(temp_shiwei!=0)						//���ʮλ����,����ʾ
	{OLED_ShowChar(x,y,temp_shiwei+'0');}	//����0,��ʾ�¶ȵ�ʮλ
	else{OLED_ShowChar(x,y,32);}			//Ϊ0����ʾ,�ո��ASCII��ֵ32	  */
	OLED_ShowChar(x+8,y,temp_gewei+'0'); 	//��ʾ�¶ȵĸ�λ
	OLED_ShowChar(x+16,y,14+' '); 			//��ʾС����
	OLED_ShowChar(x+24,y,temp_xiaoshu+'0'); //��ʾ�¶ȵ�С��λ
	OLED_ShowChar(x+32,y,95+' '); 			//��ʾ���϶ȷ��ŵ�ǰ�벿��
	OLED_ShowChar(x+40,y,96+' '); 			//��ʾ���϶ȷ��ŵ�ǰ�󲿷�	
}  //*/

 void OLED_ShowString2(uchar x,uchar y)		//��ʾʪ��
{
	OLED_ShowChar(x,y,humid_shiwei+'0'); 	//��ʾ����������ASCII���ַ�
	OLED_ShowChar(x+8,y,humid_gewei+'0'); 	//��ʾ����������ASCII���ַ�
	OLED_ShowChar(x+16,y,5+' '); 	        //��ʾ%

}  //*/