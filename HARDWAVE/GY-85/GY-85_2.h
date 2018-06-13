#ifndef _gy_85_2_
#define _gy_85_2_

#include "sys.h"

/*模拟IIC端口输出输入定义*/
#define SCL_H_2         GPIOB->BSRR = GPIO_Pin_0
#define SCL_L_2         GPIOB->BRR  = GPIO_Pin_0 
   
#define SDA_H_2         GPIOB->BSRR = GPIO_Pin_1
#define SDA_L_2         GPIOB->BRR  = GPIO_Pin_1

#define SCL_read_2      GPIOB->IDR  & GPIO_Pin_0
#define SDA_read_2      GPIOB->IDR  & GPIO_Pin_1


void I2C_GPIO_Config_2(void);
//void I2C_delay_2(void);
int I2C_WaitAck_2(void); 	 //返回为:=1有ACK,=0无ACK
void I2C_NoAck_2(void);
int I2C_Start_2(void);
void I2C_Stop_2(void);
void I2C_Ack_2(void);
void I2C_SendByte_2(u8 SendByte); //数据从高位到低位//
unsigned char I2C_ReadByte_2(void);
int Single_Write_2(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		 
unsigned char Single_Read_2(unsigned char SlaveAddress,unsigned char REG_Address);

void Init_ITG3205_2(void);
void Init_ADXL345_2(void);


void read_original_ADXL345_2(u8 n);
void read_original_ITG3205_2(u8 n);
void read_original_data_2(u8 n);


#endif

