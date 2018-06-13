#include "led.h"
void LED_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PB,PE端口时钟

//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;//端口
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
//  GPIO_SetBits(GPIOB,GPIO_Pin_12);
//	
//	RCC->APB2ENR|=1<<3;    //PORTB	   	   
//	GPIOB->CRL&=0XFFFFFFF0;
//	GPIOB->CRL|=0X00000003;    
//  GPIO_InitTypeDef GPIO_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* GPIOA Configuration: TIM3 Channel 1 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	  
}
