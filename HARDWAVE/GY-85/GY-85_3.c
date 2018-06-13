#include "GY-85.h"
#include "GY-85_3.h"
#include <math.h>
#include "delay.h"

extern u8 a[512];

void I2C_GPIO_Config_3(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//void I2C_delay(void)
//{
//		
//   u8 i=6; //��������Ż��ٶ�	����������͵�5����д��
//   while(i) 
//   { 
//     i--; 
//   }  
//}


int I2C_WaitAck_3(void) 	 //����Ϊ:=1��ACK,=0��ACK
{
	SCL_L_3;
	I2C_delay();
	SDA_H_3;			
	I2C_delay();
	SCL_H_3;
	I2C_delay();
	if(SDA_read_3)
	{
      SCL_L_3;
	    I2C_delay();
      return 0;
	}
	SCL_L_3;
	I2C_delay();
	return 1;
}

void I2C_NoAck_3(void)
{	
	SCL_L_3;
	I2C_delay();
	SDA_H_3;
	I2C_delay();
	SCL_H_3;
	I2C_delay();
	SCL_L_3;
	I2C_delay();
} 
void I2C_Ack_3(void)
{	
	SCL_L_3;
	I2C_delay();
	SDA_L_3;
	I2C_delay();
	SCL_H_3;
	I2C_delay();
	SCL_L_3;
	I2C_delay();
}   

void I2C_Stop_3(void)
{
	SCL_L_3;
	I2C_delay();
	SDA_L_3;
	I2C_delay();
	SCL_H_3;
	I2C_delay();
	SDA_H_3;
	I2C_delay();
}

int I2C_Start_3(void)
{
	SDA_H_3;
	SCL_H_3;
	I2C_delay();
	if(!SDA_read_3)
		return 0;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L_3;
	I2C_delay();
	if(SDA_read_3)
		return 0;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L_3;
	I2C_delay();
	return 1;
}

void I2C_SendByte_3(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
    while(i--)
    {
        SCL_L_3;
        I2C_delay();
        if(SendByte&0x80)
          SDA_H_3;  
        else 
          SDA_L_3;   
        SendByte<<=1;
        I2C_delay();
		    SCL_H_3;
        I2C_delay();
    }
    SCL_L_3;
} 

unsigned char I2C_ReadByte_3(void)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H_3;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L_3;
      I2C_delay();
	    SCL_H_3;
      I2C_delay();	
      if(SDA_read_3)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L_3;
    return ReceiveByte;
} 

int Single_Write_3(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start_3())
			return 0;
    I2C_SendByte_3(SlaveAddress);   //�����豸��ַ+д�ź�//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck_3())
		{
			I2C_Stop_3();
			return 0;
		}
    I2C_SendByte_3(REG_Address );   //���õ���ʼ��ַ      
    I2C_WaitAck_3();	
    I2C_SendByte_3(REG_data);
    I2C_WaitAck_3();   
    I2C_Stop_3(); 
//    delay5ms();
    return 1;
}

unsigned char Single_Read_3(unsigned char SlaveAddress,unsigned char REG_Address)
{  
  	unsigned char REG_data;  
	
	  if(!I2C_Start_3())
			return 0;
    I2C_SendByte_3(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck_3())
		{
			I2C_Stop_3();
//			test=1; 
			return 0;
		}
    I2C_SendByte_3((u8) REG_Address);   //���õ���ʼ��ַ      
    I2C_WaitAck_3();
    I2C_Start_3();
    I2C_SendByte_3(SlaveAddress+1);
    I2C_WaitAck_3();

	  REG_data= I2C_ReadByte_3();
    I2C_NoAck_3();
    I2C_Stop_3();
  
	  return REG_data;

}			


//��ʼ��ITG3205��������Ҫ��ο�pdf�����޸�************************
void Init_ITG3205_3(void)
{
   Single_Write_3(ITG3205_Addr,PWR_M, 0x80);   //
   Single_Write_3(ITG3205_Addr,SMPL, 0x07);    //
   Single_Write_3(ITG3205_Addr,DLPF, 0x1E);    //��2000��
   Single_Write_3(ITG3205_Addr,INT_C, 0x00 );  //
   Single_Write_3(ITG3205_Addr,PWR_M, 0x00);   //
}

void  Init_ADXL345_3(void)
{
   Single_Write_3(ADXL345_Addr,0x31,0x0B);   //������Χ,����16g��13λģʽ
 
   Single_Write_3(ADXL345_Addr,0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
   Single_Write_3(ADXL345_Addr,0x2E,0x80);   //ʹ�� DATA_READY �ж�
  
}


void read_original_ADXL345_3(u8 n)
{
	  a[0+12*n]=Single_Read_3(ADXL345_Addr,0x32);//OUT_X_L_A
    a[1+12*n]=Single_Read_3(ADXL345_Addr,0x33);//OUT_X_H_A
		a[2+12*n]=Single_Read_3(ADXL345_Addr,0x34);//OUT_Y_L_A
    a[3+12*n]=Single_Read_3(ADXL345_Addr,0x35);//OUT_Y_H_A
		a[4+12*n]=Single_Read_3(ADXL345_Addr,0x36);//OUT_Z_L_A
    a[5+12*n]=Single_Read_3(ADXL345_Addr,0x37);//OUT_Z_H_A
}
void read_original_ITG3205_3(u8 n)
{
	  a[6+12*n]=Single_Read_3(ITG3205_Addr,GX_L); 
    a[7+12*n]=Single_Read_3(ITG3205_Addr,GX_H);
    a[8+12*n]=Single_Read_3(ITG3205_Addr,GY_L);
    a[9+12*n]=Single_Read_3(ITG3205_Addr,GY_H);
    a[10+12*n]=Single_Read_3(ITG3205_Addr,GZ_L);
    a[11+12*n]=Single_Read_3(ITG3205_Addr,GZ_H);
}
void read_original_data_3(u8 n)
{	
		read_original_ADXL345_3(n);
		read_original_ITG3205_3(n);
}




