#include "GY-85.h"
#include <math.h>
#include "delay.h"

u8 a[512];



//u8 num;//��¼����������16������Ϊһ�飬32��Ϊһ����

//unsigned char TX_DATA[4];  	 //��ʾ�ݻ�����
//unsigned char BUF[8];                         //�������ݻ�����
//char  test=0; 
//int   x,y;
//float angle;
//unsigned char ge,shi,bai,qian,wan,shiwan;           //��ʾ����
//int A_X,A_Y,A_Z;
//short T_X,T_Y,T_Z;

//short data_xyz[3];
//float Roll,Pitch,Q,T,K;


//void delay5ms(void)
//{
//		
//   int i=5000;  
//   while(i) 
//   { 
//     i--; 
//   }  
//}



//void conversion(long temp_data)  
//{     
//    shiwan=temp_data/100000+0x30 ;
//    temp_data=temp_data%100000;   //ȡ������ 
//    wan=temp_data/10000+0x30 ;
//    temp_data=temp_data%10000;   //ȡ������
//	  qian=temp_data/1000+0x30 ;
//    temp_data=temp_data%1000;    //ȡ������
//    bai=temp_data/100+0x30   ;
//    temp_data=temp_data%100;     //ȡ������
//    shi=temp_data/10+0x30    ;
//    temp_data=temp_data%10;      //ȡ������
//    ge=temp_data+0x30; 	
//}


//void I2C_GPIO_Config(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure; 
// 
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
//  GPIO_Init(GPIOB, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

void I2C_delay(void)
{
		
   u8 i=6; //��������Ż��ٶ�	����������͵�5����д��
   while(i) 
   { 
     i--; 
   }  
}

//int I2C_WaitAck(void) 	 //����Ϊ:=1��ACK,=0��ACK
//{
//	SCL_L;
//	I2C_delay();
//	SDA_H;			
//	I2C_delay();
//	SCL_H;
//	I2C_delay();
//	if(SDA_read)
//	{
//      SCL_L;
//	    I2C_delay();
//      return 0;
//	}
//	SCL_L;
//	I2C_delay();
//	return 1;
//}

//void I2C_NoAck(void)
//{	
//	SCL_L;
//	I2C_delay();
//	SDA_H;
//	I2C_delay();
//	SCL_H;
//	I2C_delay();
//	SCL_L;
//	I2C_delay();
//} 
//void I2C_Ack(void)
//{	
//	SCL_L;
//	I2C_delay();
//	SDA_L;
//	I2C_delay();
//	SCL_H;
//	I2C_delay();
//	SCL_L;
//	I2C_delay();
//}   

//void I2C_Stop(void)
//{
//	SCL_L;
//	I2C_delay();
//	SDA_L;
//	I2C_delay();
//	SCL_H;
//	I2C_delay();
//	SDA_H;
//	I2C_delay();
//}

//int I2C_Start(void)
//{
//	SDA_H;
//	SCL_H;
//	I2C_delay();
//	if(!SDA_read)
//		return 0;	//SDA��Ϊ�͵�ƽ������æ,�˳�
//	SDA_L;
//	I2C_delay();
//	if(SDA_read)
//		return 0;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
//	SDA_L;
//	I2C_delay();
//	return 1;
//}

//void I2C_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
//{
//    u8 i=8;
//    while(i--)
//    {
//        SCL_L;
//        I2C_delay();
//        if(SendByte&0x80)
//          SDA_H;  
//        else 
//          SDA_L;   
//        SendByte<<=1;
//        I2C_delay();
//		    SCL_H;
//        I2C_delay();
//    }
//    SCL_L;
//} 

//unsigned char I2C_RadeByte(void)  //���ݴӸ�λ����λ//
//{ 
//    u8 i=8;
//    u8 ReceiveByte=0;

//    SDA_H;				
//    while(i--)
//    {
//      ReceiveByte<<=1;      
//      SCL_L;
//      I2C_delay();
//	    SCL_H;
//      I2C_delay();	
//      if(SDA_read)
//      {
//        ReceiveByte|=0x01;
//      }
//    }
//    SCL_L;
//    return ReceiveByte;
//} 

//int Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
//{
//  	if(!I2C_Start())
//			return 0;
//    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
//    if(!I2C_WaitAck())
//		{
//			I2C_Stop();
//			return 0;
//		}
//    I2C_SendByte(REG_Address );   //���õ���ʼ��ַ      
//    I2C_WaitAck();	
//    I2C_SendByte(REG_data);
//    I2C_WaitAck();   
//    I2C_Stop(); 
////    delay5ms();
//    return 1;
//}

//unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
//{  
//  	unsigned char REG_data;  
//	
//	  if(!I2C_Start())
//			return 0;
//    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
//    if(!I2C_WaitAck())
//		{
//			I2C_Stop();
//			test=1; 
//			return 0;
//		}
//    I2C_SendByte((u8) REG_Address);   //���õ���ʼ��ַ      
//    I2C_WaitAck();
//    I2C_Start();
//    I2C_SendByte(SlaveAddress+1);
//    I2C_WaitAck();

//	  REG_data= I2C_RadeByte();
//    I2C_NoAck();
//    I2C_Stop();
//  
//	  return REG_data;

//}			

/*
********************************************************************************
** �������� �� RCC_Configuration(void)
** �������� �� ʱ�ӳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void RCC_Configuration(void)
{  

  ErrorStatus HSEStartUpStatus;	
	
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  } 
   /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO  , ENABLE);  
}


//void USART1_Config(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//		USART_InitTypeDef USART_InitStructure;
//	  NVIC_InitTypeDef NVIC_InitStruct;
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );
//  
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //	ѡ�йܽ�9
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
//    
//  
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //ѡ�йܽ�10
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);				  //ѡ��A�˿�


//	
//	
//		NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
//	  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;	//IRQͨ��ʹ��
//	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
//	  NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
//	  NVIC_Init(&NVIC_InitStruct);
//	
//	
//	
//	
//	
//		USART_InitStructure.USART_BaudRate = 115200;						  // ������Ϊ��115200
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
//		USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
//		/* Configure USART1 basic and asynchronous paramters */
//		USART_Init(USART1, &USART_InitStructure);
//    
//		/* Enable USART1 */
//		USART_ClearFlag(USART1, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
//		USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//ʹ��USART1�ж�Դ
//		USART_Cmd(USART1, ENABLE);							//USART1�ܿ��أ����� 
//}



//void  USART1_SendData(uchar SendData)
//{
//    USART_SendData(USART1, SendData);
//    delay_ms(1);
//}

//void DATA_printf(uchar *s,short temp_data)
//{
//	if(temp_data<0)
//	{
//	  temp_data=-temp_data;
//    *s='-';
//	}
//	else 
//		*s=' ';
//	
//  *++s =temp_data/100+0x30;
//  temp_data=temp_data%100;     //ȡ������
//  *++s =temp_data/10+0x30;
//  temp_data=temp_data%10;      //ȡ������
//  *++s =temp_data+0x30; 	
//}


////��ʼ��ITG3205��������Ҫ��ο�pdf�����޸�************************
//void Init_ITG3205(void)
//{
//   Single_Write(ITG3205_Addr,PWR_M, 0x80);   //
//   Single_Write(ITG3205_Addr,SMPL, 0x07);    //
//   Single_Write(ITG3205_Addr,DLPF, 0x1E);    //��2000��
//   Single_Write(ITG3205_Addr,INT_C, 0x00 );  //
//   Single_Write(ITG3205_Addr,PWR_M, 0x00);   //
//}

////******��ȡITG3205����****************************************
//void READ_ITG3205(void)
//{
//   BUF[0]=Single_Read(ITG3205_Addr,GX_L); 
//   BUF[1]=Single_Read(ITG3205_Addr,GX_H);
//   T_X=	(BUF[1]<<8)|BUF[0];
//   T_X/=14.375; 						   //��ȡ����X������

//   BUF[2]=Single_Read(ITG3205_Addr,GY_L);
//   BUF[3]=Single_Read(ITG3205_Addr,GY_H);
//   T_Y=	(BUF[3]<<8)|BUF[2];
//   T_Y/=14.375; 						   //��ȡ����Y������
//   BUF[4]=Single_Read(ITG3205_Addr,GZ_L);
//   BUF[5]=Single_Read(ITG3205_Addr,GZ_H);
//   T_Z=	(BUF[5]<<8)|BUF[4];
//   T_Z/=14.375; 					       //��ȡ����Z������

////   BUF[6]=Single_Read(ITG3205_Addr,TMP_L); 
////   BUF[7]=Single_Read(ITG3205_Addr,TMP_H); 
////   T_T=(BUF[7]<<8)|BUF[6];
////   T_T = 35+ ((double) (T_T + 13200)) / 280;// ��ȡ������¶�
//}

// //********���ڷ�������***************************************
// void Send_data(void)
// { 
//	 uchar i;

//	 
//   for(i=0;i<4;i++)
//			USART1_SendData(TX_DATA[i]);
//   USART1_SendData(' ');
//   USART1_SendData(' ');
// }

//void Send_ITG3205()
//{
//	
//		DATA_printf(TX_DATA,T_X);//ת��X�����ݵ�����
//	  Send_data();			 //����X����
//	  DATA_printf(TX_DATA,T_Y);//ת��Y�����ݵ�����
//	  Send_data();			 //����Y����
//	  DATA_printf(TX_DATA,T_Z);//ת��Z�����ݵ�����
//    Send_data();			 //����Z����
//}

//void Send_ADXL345_data(int dis_data)
//{ 
//		float temp ;
//		if(dis_data>0x7fff)
//		{
//				dis_data-=0xffff;
//		}
//		if(dis_data<0)
//		{
//  	    dis_data=-dis_data;
//				USART_SendData(USART1,'-');
////				delay_ms(2);
//		}
//		else
//	  { 
//				USART_SendData(USART1,'+');
////				delay_ms(2);
//	  }
//    temp=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
//    conversion(temp);          //ת������ʾ��Ҫ������	 
//	  USART1_SendData(qian);
//		USART1_SendData('.');
//	  USART1_SendData(bai); 
//	  USART1_SendData(shi); 
//	  USART1_SendData(ge); 
////		USART1_SendData('g'); 
//		USART1_SendData(' '); 
//		
//}

//void Send_HMC5883L()
//{
//		USART1_SendData('H');
//		USART1_SendData('M');
//		USART1_SendData('C');
//		USART1_SendData('5');
//		USART1_SendData('8');
//		USART1_SendData('8');
//		USART1_SendData('3');
//		USART1_SendData('L');
//		USART1_SendData(':');
//	
//		conversion(angle);
//		USART1_SendData(bai); 
//		USART1_SendData(shi); 
//		USART1_SendData(ge); 
//		USART1_SendData('`');  
//		USART1_SendData(0x0d);
//		USART1_SendData(0x0a);
//}

//void  Send_ADXL345()
//{
//		USART1_SendData('A');
//		USART1_SendData('D');
//		USART1_SendData('X');
//		USART1_SendData('L');
//		USART1_SendData('3');
//		USART1_SendData('4');
//		USART1_SendData('5');
//		USART1_SendData(':');
//	  USART1_SendData(' ');
//	  USART1_SendData('X');
//	  USART1_SendData('=');
//	  Send_ADXL345_data(A_X);

//	  USART1_SendData(' ');
//	  USART1_SendData('Y');
//	  USART1_SendData('=');
//	  Send_ADXL345_data(A_Y);

//	  USART1_SendData(' ');
//	  USART1_SendData('Z');
//	  USART1_SendData('=');
//	  Send_ADXL345_data(A_Z);

//	  adxl345_angle();


//		USART1_SendData(0x0d);
//		USART1_SendData(0x0a);
//}

//void read_hmc5883l(void)
//{
//       Single_Write(HMC5883L_Addr,0x00,0x14);   //
//       Single_Write(HMC5883L_Addr,0x02,0x00);   //
////  	   delay_ms(10);

//       BUF[1]=Single_Read(HMC5883L_Addr,0x03);//OUT_X_L_A
//       BUF[2]=Single_Read(HMC5883L_Addr,0x04);//OUT_X_H_A

//	     BUF[3]=Single_Read(HMC5883L_Addr,0x07);//OUT_Y_L_A
//       BUF[4]=Single_Read(HMC5883L_Addr,0x08);//OUT_Y_H_A

//       x=(BUF[1] << 8) | BUF[2]; //Combine MSB and LSB of X Data output register
//       y=(BUF[3] << 8) | BUF[4]; //Combine MSB and LSB of Z Data output register

//       if(x>0x7fff)
//				 x-=0xffff;	  
//       if(y>0x7fff)
//				 y-=0xffff;	
//  
//       angle= atan2(y,x) * (180 / 3.14159265) + 180; // angle in degrees
//}
//void read_ADXL345(void)
//{
//     BUF[0]=Single_Read(ADXL345_Addr,0x32);//OUT_X_L_A
//     BUF[1]=Single_Read(ADXL345_Addr,0x33);//OUT_X_H_A
//		 BUF[2]=Single_Read(ADXL345_Addr,0x34);//OUT_Y_L_A
//     BUF[3]=Single_Read(ADXL345_Addr,0x35);//OUT_Y_H_A
//		 BUF[4]=Single_Read(ADXL345_Addr,0x36);//OUT_Z_L_A
//     BUF[5]=Single_Read(ADXL345_Addr,0x37);//OUT_Z_H_A

//	   A_X=(BUF[1]<<8)+BUF[0];  //�ϳ�����  
//	   A_Y=(BUF[3]<<8)+BUF[2];  //�ϳ�����
//	   A_Z=(BUF[5]<<8)+BUF[4];  //�ϳ�����
//}

//void  Init_ADXL345(void)
//{
//   Single_Write(ADXL345_Addr,0x31,0x0B);   //������Χ,����16g��13λģʽ
//  // Single_Write(ADXL345_Addr,0x2C,0x0e);   //�����趨Ϊ100hz �ο�pdf13ҳ
//   Single_Write(ADXL345_Addr,0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
//   Single_Write(ADXL345_Addr,0x2E,0x80);   //ʹ�� DATA_READY �ж�
//  // Single_Write(ADXL345_Addr,0x1E,0x00);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
//  // Single_Write(ADXL345_Addr,0x1F,0x00);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
//  // Single_Write(ADXL345_Addr,0x20,0x05);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
//}

// void  Init_HMC5883L()
//{
//   Single_Write(HMC5883L_Addr,0x00,0x14);   //
//   Single_Write(HMC5883L_Addr,0x02,0x00);   //
//}


// //******************ADXL345������б�Ƕ�************
//void adxl345_angle(void)
//{

//    data_xyz[0]=A_X;  //�ϳ�����   
//		data_xyz[1]=A_Y;  //�ϳ�����   
//		data_xyz[2]=A_Z;  //�ϳ�����   

//		//�ֱ��Ǽ��ٶ�X,Y,Z��ԭʼ���ݣ�10λ��
//		Q=(float)data_xyz[0]*3.9;
//		T=(float)data_xyz[1]*3.9;
//		K=(float)data_xyz[2]*3.9;
//		Q=-Q;

//		Roll=(float)(((atan2(K,Q)*180)/3.14159265)+180);    //X��Ƕ�ֵ
//		Pitch=(float)(((atan2(K,T)*180)/3.14159265)+180);  //Y��Ƕ�ֵ
//		conversion(Pitch);								   //��Ҫ��ʾʱ�������
//	  
//	  USART1_SendData(' '); 
//		USART1_SendData(' '); 
//	
//  	USART1_SendData(bai); 
//	  USART1_SendData(shi); 
//	  USART1_SendData(ge);	
//	
//	  conversion(Roll);
//		
//    USART1_SendData(' '); 
//		USART1_SendData(' '); 
//	
//  	USART1_SendData(bai); 
//	  USART1_SendData(shi); 
//	  USART1_SendData(ge);
//}


//void send_all()
//{
//	  read_hmc5883l();
//	  conversion(angle);//ת��
//		USART1_SendData(bai); 
//		USART1_SendData(shi); 
//		USART1_SendData(ge); 
//	  USART1_SendData(' ');//��1������

//		read_ADXL345();
//	  adxl345_angle();
//	  USART1_SendData(0x0d);
//	  USART1_SendData(0x0a);//��2��3������
//	
//	  Send_ADXL345_data(A_X);
//		Send_ADXL345_data(A_Y);
//		Send_ADXL345_data(A_Z);//��4��5��6������
//	  USART1_SendData(0x0d);
//		USART1_SendData(0x0a);

//		READ_ITG3205();
//	  Send_ITG3205();//��7��8��9������
//	
//	 
//	  USART1_SendData(0x0d);
//		USART1_SendData(0x0a);
//		
//		USART1_SendData(0x0d);
//		USART1_SendData(0x0a);
//}

//void read_original_HMC5883L(u8 n)
//{
//    a[0+16*n]=Single_Read(HMC5883L_Addr,0x03);//OUT_X_L_A
//    a[1+16*n]=Single_Read(HMC5883L_Addr,0x04);//OUT_X_H_A
//	  a[2+16*n]=Single_Read(HMC5883L_Addr,0x07);//OUT_Y_L_A
//    a[3+16*n]=Single_Read(HMC5883L_Addr,0x08);//OUT_Y_H_A
//}
//void read_original_ADXL345(u8 n)
//{
//	  a[4+16*n]=Single_Read(ADXL345_Addr,0x32);//OUT_X_L_A
//    a[5+16*n]=Single_Read(ADXL345_Addr,0x33);//OUT_X_H_A
//		a[6+16*n]=Single_Read(ADXL345_Addr,0x34);//OUT_Y_L_A
//    a[7+16*n]=Single_Read(ADXL345_Addr,0x35);//OUT_Y_H_A
//		a[8+16*n]=Single_Read(ADXL345_Addr,0x36);//OUT_Z_L_A
//    a[9+16*n]=Single_Read(ADXL345_Addr,0x37);//OUT_Z_H_A
//}
//void read_original_ITG33205(u8 n)
//{
//	  a[10+16*n]=Single_Read(ITG3205_Addr,GX_L); 
//    a[11+16*n]=Single_Read(ITG3205_Addr,GX_H);
//    a[12+16*n]=Single_Read(ITG3205_Addr,GY_L);
//    a[13+16*n]=Single_Read(ITG3205_Addr,GY_H);
//    a[14+16*n]=Single_Read(ITG3205_Addr,GZ_L);
//    a[15+16*n]=Single_Read(ITG3205_Addr,GZ_H);
//}

//void read_original_ADXL345(u8 n)
//{
//	  a[0+12*n]=Single_Read(ADXL345_Addr,0x32);//OUT_X_L_A
//    a[1+12*n]=Single_Read(ADXL345_Addr,0x33);//OUT_X_H_A
//		a[2+12*n]=Single_Read(ADXL345_Addr,0x34);//OUT_Y_L_A
//    a[3+12*n]=Single_Read(ADXL345_Addr,0x35);//OUT_Y_H_A
//		a[4+12*n]=Single_Read(ADXL345_Addr,0x36);//OUT_Z_L_A
//    a[5+12*n]=Single_Read(ADXL345_Addr,0x37);//OUT_Z_H_A
//}
//void read_original_ITG33205(u8 n)
//{
//	  a[6+12*n]=Single_Read(ITG3205_Addr,GX_L); 
//    a[7+12*n]=Single_Read(ITG3205_Addr,GX_H);
//    a[8+12*n]=Single_Read(ITG3205_Addr,GY_L);
//    a[9+12*n]=Single_Read(ITG3205_Addr,GY_H);
//    a[10+12*n]=Single_Read(ITG3205_Addr,GZ_L);
//    a[11+12*n]=Single_Read(ITG3205_Addr,GZ_H);
//}
//void read_original_data(u8 n)
//{	
////		read_original_HMC5883L(n);
//		read_original_ADXL345(n);
//		read_original_ITG33205(n);
//}




