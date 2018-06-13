/*******************************************
*
*
*  注    意：使用前请读 README.TXT
*
*
*******************************************/
#include "sys.h"
#include "GY-85_1.h"
#include "delay.h"
#include "led.h"     
#include "oled.h"
#include "ws2812.h"
#include "dht11.h" 
#define WS_BLACK 0x000000
#define WS_WRITE 0xffffff
#define WS_GREEN 0xff0000
#define WS_RED 	 0x00ff00
#define WS_BLUE  0x0000ff
void Init(void)
{
	delay_init();
	//uart_init();
  RCC_Configuration();
	LED_Init();
	OLED_Init();
  I2C_GPIO_Config_1();
	Init_HMC5883L();
	WS2812_init();
	//Light_Ring_deg(0);
	
}
int main(void)
{
	u16 degree=0,t=0,Flag=1;;
//	u8 temperature;  	    
//	u8 humidity;  	
	Init(); 
	degree = (u16)read_hmc5883l();
	
	OLED_ShowNum(0,2,degree,3,16);
	//delay_ms(200);
	Light_Ring_deg(degree);
//	while(DHT11_Init())	//DHT11初始化	
//	{
//		OLED_ShowString(0,0,"DHT11 Error");
//		delay_ms(200);
//	} 	
//	OLED_ShowString(0,0,"Deg :      ");	
//	OLED_ShowString(0,2,"Temp:   C");	 
// 	OLED_ShowString(0,4,"Humi:   %");	
	while(1)
	{
		degree = (u16)read_hmc5883l();
		OLED_ShowNum(40,0,degree,3,16);
		Light_Ring_deg(degree);
		delay_ms(50);
//		DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值					    
//		OLED_ShowNum(40,2,temperature,2,16);	//显示温度
//		OLED_ShowNum(40,4,humidity,2,16);		//显示湿度
	//	if(Flag){
			
			//OLED_ShowString(0,6,"DEG MODE");
			//delay_ms(50);
//		}
//		else{
//			Light_Ring_RT(&temperature,&humidity);
//						OLED_ShowString(0,6,"RT MODE");
//		}
//		if(t%150==1)			Flag = !Flag;
//		t++;

//		LED0 = 1;
//		delay_ms(500);
//		LED0 = 0;
//		delay_ms(500);
	}
}

//显示温度，湿度程序








//串口通讯模块





//渐变色程序
//		ColorToColor(0x4876FF,0xEE2C2C);
//		ColorToColor(0xEE2C2C,0x4876FF);
//int main(void)
//{
//	//WS2812_init();
//	LED_Init();
//	delay_init();
//	while(1)
//	{
//		LED1 = 0;
//		//LED0 = 0;
//		delay_us(1);
//		LED1 = 1;
//		//LED0 = 1;
//		delay_us(1);
//	}
//}









