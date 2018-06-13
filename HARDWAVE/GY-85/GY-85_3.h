#ifndef _gy_85_3_
#define _gy_85_3_

#include "sys.h"

/*ģ��IIC�˿�������붨��*/
#define SCL_H_3        GPIOB->BSRR = GPIO_Pin_13
#define SCL_L_3         GPIOB->BRR  = GPIO_Pin_13 
   
#define SDA_H_3         GPIOB->BSRR = GPIO_Pin_14
#define SDA_L_3         GPIOB->BRR  = GPIO_Pin_14

#define SCL_read_3      GPIOB->IDR  & GPIO_Pin_13
#define SDA_read_3      GPIOB->IDR  & GPIO_Pin_14


void I2C_GPIO_Config_3(void);
//void I2C_delay_2(void);
int I2C_WaitAck_3(void); 	 //����Ϊ:=1��ACK,=0��ACK
void I2C_NoAck_3(void);
int I2C_Start_3(void);
void I2C_Stop_3(void);
void I2C_Ack_3(void);
void I2C_SendByte_3(u8 SendByte); //���ݴӸ�λ����λ//
unsigned char I2C_ReadByte_3(void);
int Single_Write_3(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		 
unsigned char Single_Read_3(unsigned char SlaveAddress,unsigned char REG_Address);

void Init_ITG3205_3(void);
void Init_ADXL345_3(void);


void read_original_ADXL345_3(u8 n);
void read_original_ITG3205_3(u8 n);
void read_original_data_3(u8 n);


#endif

