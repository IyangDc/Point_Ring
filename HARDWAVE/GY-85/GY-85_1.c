#include "GY-85.h"
#include "GY-85_1.h"
#include <math.h>
#include "delay.h"

u8 a[512];

/********************************************************************************
** 函数名称 ： RCC_Configuration(void)
** 函数功能 ： 时钟初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
	
	
	//DHT11_Init_GPIO
//	RCC->APB2ENR|=1<<3;    //使能PORTG口时钟 
//	GPIOB->CRL&=0XFFFFFF0F;//PORTG.11 推挽输出
//	GPIOB->CRL|=0X00000030;
//	GPIOB->ODR|=1<<1;      //输出1		
}


void I2C_GPIO_Config_1(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void I2C_delay(void)
{
		
   u8 i=6; //这里可以优化速度	，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   }  
}

int I2C_WaitAck_1(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L_1;
  I2C_delay();
	SDA_H_1;			
	I2C_delay();
	SCL_H_1;
	I2C_delay();
	if(SDA_read_1)
	{
      SCL_L_1;
	    I2C_delay();
      return 0;
	}
	SCL_L_1;
	I2C_delay();
	return 1;
}

void I2C_NoAck_1(void)
{	
	SCL_L_1;
	I2C_delay();
	SDA_H_1;
	I2C_delay();
	SCL_H_1;
	I2C_delay();
	SCL_L_1;
	I2C_delay();
} 
void I2C_Ack_1(void)
{	
	SCL_L_1;
	I2C_delay();
	SDA_L_1;
	I2C_delay();
	SCL_H_1;
	I2C_delay();
	SCL_L_1;
	I2C_delay();
}   

void I2C_Stop_1(void)
{
	SCL_L_1;
	I2C_delay();
	SDA_L_1;
	I2C_delay();
	SCL_H_1;
	I2C_delay();
	SDA_H_1;
	I2C_delay();
}

int I2C_Start_1(void)
{
	SDA_H_1;
	SCL_H_1;
	I2C_delay();
	if(!SDA_read_1)
		return 0;	//SDA线为低电平则总线忙,退出
	SDA_L_1;
	I2C_delay();
	if(SDA_read_1)
		return 0;	//SDA线为高电平则总线出错,退出
	SDA_L_1;
	I2C_delay();
	return 1;
}

void I2C_SendByte_1(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L_1;
        I2C_delay();
        if(SendByte&0x80)
          SDA_H_1;  
        else 
          SDA_L_1;   
        SendByte<<=1;
        I2C_delay();
		    SCL_H_1;
        I2C_delay();
    }
    SCL_L_1;
} 

unsigned char I2C_ReadByte_1(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H_1;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L_1;
      I2C_delay();
	    SCL_H_1;
      I2C_delay();	
      if(SDA_read_1)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L_1;
    return ReceiveByte;
} 

int Single_Write_1(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start_1())
			return 0;
    I2C_SendByte_1(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck_1())
		{
			I2C_Stop_1();
			return 0;
		}
    I2C_SendByte_1(REG_Address );   //设置低起始地址      
    I2C_WaitAck_1();	
    I2C_SendByte_1(REG_data);
    I2C_WaitAck_1();   
    I2C_Stop_1(); 
//    delay5ms();
    return 1;
}

unsigned char Single_Read_1(unsigned char SlaveAddress,unsigned char REG_Address)
{  
  	unsigned char REG_data;  
	
	  if(!I2C_Start_1())
			return 0;
    I2C_SendByte_1(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck_1())
		{
			I2C_Stop_1();
//			test=1; 
			return 0;
		}
    I2C_SendByte_1((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck_1();
    I2C_Start_1();
    I2C_SendByte_1(SlaveAddress+1);
    I2C_WaitAck_1();

	  REG_data= I2C_ReadByte_1();
    I2C_NoAck_1();
    I2C_Stop_1();
  
	  return REG_data;

}			


//初始化ITG3205，根据需要请参考pdf进行修改************************
void Init_ITG3205_1(void)
{
   Single_Write_1(ITG3205_Addr,PWR_M, 0x80);   //
   Single_Write_1(ITG3205_Addr,SMPL, 0x07);    //
   Single_Write_1(ITG3205_Addr,DLPF, 0x1E);    //±2000°
   Single_Write_1(ITG3205_Addr,INT_C, 0x00 );  //
   Single_Write_1(ITG3205_Addr,PWR_M, 0x00);   //
}

void Init_ADXL345_1(void)
{
   Single_Write_1(ADXL345_Addr,0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_1(ADXL345_Addr,0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_1(ADXL345_Addr,0x2E,0x80);   //使能 DATA_READY 中断
}
void Init_HMC5883L(void)
{
	Single_Write_1(HMC5883L_Addr,0x00,0x70);
	Single_Write_1(HMC5883L_Addr,0x01,0xA0);
  Single_Write_1(HMC5883L_Addr,0x02,0x00);
}
float read_hmc5883l(void)
{
	u8 BUF[6]={0};	//数据存放
	int x=0,y=0;		//数据暂存
	float angle=0;	//角度
	BUF[0] = Single_Read_1(HMC5883L_Addr,0x03);//OUT_X_L_A
	BUF[1] = Single_Read_1(HMC5883L_Addr,0x04);//OUT_X_H_A
	BUF[2] = Single_Read_1(HMC5883L_Addr,0x07);//OUT_Y_L_A
	BUF[3] = Single_Read_1(HMC5883L_Addr,0x08);//OUT_Y_H_A
	BUF[4] = Single_Read_1(HMC5883L_Addr,0x05);//OUT_z_L_A
	BUF[5] = Single_Read_1(HMC5883L_Addr,0x06);//OUT_z_H_A
	
	x = (BUF[0] << 8) | BUF[1]; //Combine MSB and LSB of X Data output register
	y = (BUF[2] << 8) | BUF[3]; //Combine MSB and LSB of Z Data output register

	if(x>0x7fff)x-=0xffff;
	if(y>0x7fff)y-=0xffff;

	//angle = atan2((float)x,(float)y) * (180 / 3.14159265) + 180; // angle in degrees
	angle = atan2(x,y) * (180 / 3.14159265) + 180;
	return angle;
}


void read_original_ADXL345_1(u8 n)
{
	  a[0+12*n]=Single_Read_1(ADXL345_Addr,0x32);//OUT_X_L_A
    a[1+12*n]=Single_Read_1(ADXL345_Addr,0x33);//OUT_X_H_A
		a[2+12*n]=Single_Read_1(ADXL345_Addr,0x34);//OUT_Y_L_A
    a[3+12*n]=Single_Read_1(ADXL345_Addr,0x35);//OUT_Y_H_A
		a[4+12*n]=Single_Read_1(ADXL345_Addr,0x36);//OUT_Z_L_A
    a[5+12*n]=Single_Read_1(ADXL345_Addr,0x37);//OUT_Z_H_A
}
void read_original_ITG3205_1(u8 n)
{
	  a[6+12*n]=Single_Read_1(ITG3205_Addr,GX_L); 
    a[7+12*n]=Single_Read_1(ITG3205_Addr,GX_H);
    a[8+12*n]=Single_Read_1(ITG3205_Addr,GY_L);
    a[9+12*n]=Single_Read_1(ITG3205_Addr,GY_H);
    a[10+12*n]=Single_Read_1(ITG3205_Addr,GZ_L);
    a[11+12*n]=Single_Read_1(ITG3205_Addr,GZ_H);
}
void read_original_data_1(u8 n)
{	
		read_original_ADXL345_1(n);
		read_original_ITG3205_1(n);
}




