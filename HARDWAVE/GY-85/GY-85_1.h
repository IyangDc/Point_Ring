#ifndef _gy_85_1_
#define _gy_85_1_

#include "sys.h"

/*模拟IIC端口输出输入定义*/
#define SCL_H_1         GPIOB->BSRR = GPIO_Pin_6
#define SCL_L_1         GPIOB->BRR  = GPIO_Pin_6
   
#define SDA_H_1         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L_1         GPIOB->BRR  = GPIO_Pin_7

#define SCL_read_1      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read_1      GPIOB->IDR  & GPIO_Pin_7

void Init_HMC5883L(void);
void RCC_Configuration(void);
float read_hmc5883l(void);
void I2C_GPIO_Config_1(void);
////void I2C_delay_1(void);
//int I2C_WaitAck_1(void); 	 //返回为:=1有ACK,=0无ACK
//void I2C_NoAck_1(void);
//int I2C_Start_1(void);
//void I2C_Stop_1(void);
//void I2C_Ack_1(void);
//void I2C_SendByte_1(u8 SendByte); //数据从高位到低位//
//unsigned char I2C_ReadByte_1(void);
//int Single_Write_1(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		 
//unsigned char Single_Read_1(unsigned char SlaveAddress,unsigned char REG_Address);

//void Init_ITG3205_1(void);
//void Init_ADXL345_1(void);

//void read_original_ADXL345_1(u8 n);
//void read_original_ITG3205_1(u8 n);
//void read_original_data_1(u8 n);


#endif

