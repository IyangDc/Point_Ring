#ifndef _gy_85_
#define _gy_85_

#include "sys.h"

#define   uchar unsigned char
#define   uint unsigned int

//定义ITG3205内部地址********************
#define WHO	  0x00
#define	SMPL	0x15
#define DLPF	0x16
#define INT_C	0x17
#define INT_S	0x1A
#define	TMP_H	0x1B
#define	TMP_L	0x1C
#define	GX_H	0x1D
#define	GX_L	0x1E
#define	GY_H	0x1F
#define	GY_L	0x20
#define GZ_H	0x21
#define GZ_L	0x22
#define PWR_M	0x3E

//定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改
#define	HMC5883L_Addr   0x3C	//磁场传感器器件地址
#define	ADXL345_Addr    0xA6	//加速度传感器器件地址
#define	ITG3205_Addr   0xD0	 


///*模拟IIC端口输出输入定义*/
//#define SCL_H         GPIOB->BSRR = GPIO_Pin_6
//#define SCL_L         GPIOB->BRR  = GPIO_Pin_6 
//   
//#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
//#define SDA_L         GPIOB->BRR  = GPIO_Pin_7

//#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
//#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

void RCC_Configuration(void);
//void GPIO_Configuration(void);
//void USART1_Config(void);


//void Delay(u32 nTime);
//void Delayms(vu32 m);  
//void conversion(long temp_data);
//void adxl345_angle(void);

//void delay5ms(void);


//void I2C_GPIO_Config(void);
void I2C_delay(void);
//int I2C_WaitAck(void); 	 //返回为:=1有ACK,=0无ACK
//void I2C_NoAck(void);
//int I2C_Start(void);
//void I2C_Stop(void);
//void I2C_Ack(void);

//void I2C_SendByte(u8 SendByte); //数据从高位到低位//
//unsigned char I2C_RadeByte(void);
//int Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		 
//unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);

//void USART1_SendData(uchar SendData);
//void DATA_printf(uchar *s,short temp_data);

//void Init_ITG3205(void);
//void Init_ADXL345(void);
//void Init_HMC5883L(void);


//void READ_ITG3205(void);
//void Send_data(void);

//void Send_ITG3205(void);
//void Send_ADXL345_data(int dis_data);

//void Send_HMC5883L(void);
//void Send_ADXL345(void);

//void read_hmc5883l(void);
//void read_ADXL345(void);

//void adxl345_angle(void);

//void send_all(void);


//void read_original_HMC5883L(u8 n);
//void read_original_ADXL345(u8 n);
//void read_original_ITG33205(u8 n);
//void read_original_data(u8 n);








#endif

