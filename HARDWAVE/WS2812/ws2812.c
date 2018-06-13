#include "ws2812.h"
/* Buffer that holds one complete DMA transmission
 * 
 * Ensure that this buffer is big enough to hold
 * all data bytes that need to be sent
 * 
 * The buffer size can be calculated as follows:
 * number of LEDs * 24 bytes + 42 bytes
 * 
 * This leaves us with a maximum string length of
 * (2^16 bytes per DMA stream - 42 bytes)/24 bytes per LED = 2728 LEDs
 */
#define TIM3_CCR3_Address 0x4000043c 	// physical memory address of Timer 3 CCR1 register
//#define TIM3_CCR1_Address 0x40000434	// physical memory address of Timer 3 CCR1 register
	
#define TIMING_ONE  50
#define TIMING_ZERO 25
#define FORWARD 					0
#define FORWARD_RIGNT     1
#define RIGHT							2
#define BACKWARD_RIGHT		3
#define BACKWARD					4
#define BACKWARD_LEFT			5
#define LEFT							7
#define FORWARD_LEFT			8
 uint16_t LED_BYTE_Buffer[300];
//---------------------------------------------------------------//

void WS2812_init(void)
{ 
	uint8_t co1[16][3]={0};
	DMA_InitTypeDef DMA_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* GPIOA Configuration: TIM3 Channel 1 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* Compute the prescaler value */
	//PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 90-1; // 800kHz 
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
		
	/* configure DMA */
	/* DMA clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/* DMA1 Channel6 Config */
	DMA_DeInit(DMA1_Channel3);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)TIM3_CCR3_Address;	// physical address of Timer 3 CCR1
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)LED_BYTE_Buffer;		// this is the buffer memory 
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;						// data shifted from memory to peripheral
	DMA_InitStructure.DMA_BufferSize = 42;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// automatically increase buffer index
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							// stop DMA feed after buffer size is reached
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

		/* TIM3 CC1 DMA Request enable */
	TIM_DMACmd(TIM3, TIM_DMA_Update, ENABLE);
	
	WS2812_send(co1,16);
}

/* This function sends data bytes out to a string of WS2812s
 * The first argument is a pointer to the first RGB triplet to be sent
 * The seconds argument is the number of LEDs in the chain
 * 
 * This will result in the RGB triplet passed by argument 1 being sent to 
 * the LED that is the furthest away from the controller (the point where
 * data is injected into the chain)
 */
void WS2812_send(uint8_t (*color)[3],uint16_t len)
	//uint8_t (*color)[3], uint16_t len
{
	
	uint8_t i,j;
	uint16_t memaddr;
	uint16_t buffersize;
	buffersize = (len*24)+43;	// number of bytes needed is #LEDs * 24 bytes + 42 trailing bytes
	memaddr = 0;				// reset buffer memory index

	for(j=0;j<len;j++)
	{	
			for(i=0; i<8; i++) // GREEN data
			{
					LED_BYTE_Buffer[memaddr] = ((color[j][1]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
					memaddr++;
			}
			for(i=0; i<8; i++) // RED
			{
					LED_BYTE_Buffer[memaddr] = ((color[j][0]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
					memaddr++;
			}
			for(i=0; i<8; i++) // BLUE
			{
					LED_BYTE_Buffer[memaddr] = ((color[j][2]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
					memaddr++;
			}
			
//		  len--;
	}
//		{	
//			for(i=0; i<8; i++) // GREEN data
//			{
//					LED_BYTE_Buffer[memaddr] = (210 & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//					memaddr++;
//			}
//			for(i=0; i<8; i++) // RED
//			{
//					LED_BYTE_Buffer[memaddr] = (0 & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//					memaddr++;
//			}
//			for(i=0; i<8; i++) // BLUE
//			{
//					LED_BYTE_Buffer[memaddr] = (0 & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//					memaddr++;
//			}
//			
//		  len--;
//	}
//===================================================================//	
//bug:最后一个周期都是高电平，增加一个周期
		LED_BYTE_Buffer[memaddr] = ((color[len-1][2]<<8) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//===================================================================//	
//	//===================================================================//	
////bug:最后一个周期都是高电平，增加一个周期
//  	LED_BYTE_Buffer[memaddr] = (0 & 0x0080) ? TIMING_ONE:TIMING_ZERO;
////===================================================================//	
	  memaddr++;	
		while(memaddr < buffersize)
		{
			LED_BYTE_Buffer[memaddr] = 0;
			memaddr++;
		}
		DMA_SetCurrDataCounter(DMA1_Channel3, buffersize); 	// load number of bytes to be transferred
		DMA_Cmd(DMA1_Channel3, ENABLE); 			// enable DMA channel 6
		TIM_Cmd(TIM3, ENABLE); 						// enable Timer 3
		while(!DMA_GetFlagStatus(DMA1_FLAG_TC3)) ; 	// wait until transfer complete
		TIM_Cmd(TIM3, DISABLE); 	// disable Timer 3
		DMA_Cmd(DMA1_Channel3, DISABLE); 			// disable DMA channel 6
		DMA_ClearFlag(DMA1_FLAG_TC3); 				// clear DMA1 Channel 6 transfer complete flag
		/*--------------------------------------------------------------*/
}


/***********************************************************************************
* 颜色渐变算法
* 误差 <= 2
************************************************************************************/
u32 ColorToColor(unsigned long color0, unsigned long color1)
{
	uint8_t co[1][3];
	unsigned char Red0, Green0, Blue0;  // 起始三原色
	unsigned char Red1, Green1, Blue1;  // 结果三原色
	int			  RedMinus, GreenMinus, BlueMinus;	// 颜色差（color1 - color0）
	unsigned char NStep; 							// 需要几步
	float		  RedStep, GreenStep, BlueStep;		// 各色步进值
	unsigned long color;							// 结果色
	unsigned char i;
//	static uint32_t WsDatTemp;
	// 绿 红 蓝 三原色分解
	Red0   = color0>>8;
	Green0 = color0>>16;
	Blue0  = color0;
	
	Red1   = color1>>8;
	Green1 = color1>>16;
	Blue1  = color1;
	
	// 计算需要多少步（取差值的最大值）
	RedMinus   = (Red1 - Red0); 
	GreenMinus = (Green1 - Green0); 
	BlueMinus  = (Blue1 - Blue0);
	
//	NStep = ( abs0(RedMinus) > abs0(GreenMinus) ) ? abs0(RedMinus):abs0(GreenMinus);
//	NStep = ( NStep > abs0(BlueMinus) ) ? NStep:abs0(BlueMinus);
	
	NStep = ( abs(RedMinus) > abs(GreenMinus) ) ? abs(RedMinus):abs(GreenMinus);
	NStep = ( NStep > abs(BlueMinus) ) ? NStep:abs(BlueMinus);
	// 计算出各色步进值
	RedStep   = (float)RedMinus   / NStep;
	GreenStep = (float)GreenMinus / NStep;
	BlueStep  = (float)BlueMinus  / NStep;

	// 渐变开始
	for(i=0; i<NStep; i++)
	{
		Red1   = Red0   + (int)(RedStep   * i);
		Green1 = Green0 + (int)(GreenStep * i);
		Blue1  = Blue0  + (int)(BlueStep  * i);
		co[0][0] = Green1;
		co[0][1] = Red1;
		co[0][2] = Blue1;
		WS2812_send(co,1);
		//color  = Green1<<16 | Red1<<8 | Blue1; 	// 合成  绿红蓝
//		WsDatTemp = color;
//		for(j=0; j<nWs; j++)
//		{
//			WS_Set1(WsDatTemp);  // j / 0
//		}
//	  WS_Reset();
		delay_ms(6);						// 渐变速度
	}
	// 渐变结束
	
	return color;
}


/**************************************************************************
	点亮灯环,角度显示
	总共16个灯，每个灯之间间隔360°/16=22.5°
	每次点亮三个灯表示角度
	入口参数为 x轴 与地磁北极 沿顺时针方向的夹角
**************************************************************************/
void Light_Ring_deg(float degree)
{
	static u8 te=0;
	u8 situ=0,i=0,j=0,k=0;
	u16 deg=0;
	uint8_t co[16][3]={0};
	
	//角度对次序映射
	degree *=2;
	degree += 22.5;
	deg = (u16)degree % 720;
	situ = deg / 45;
	
	j = situ;							//第二个灯
	
	if(j!=0) i = j - 1; 	//第一个灯
	else i = 15;
								
	if(j!=15) k = j + 1;	//第三个灯
	else k = 0;

	co[i][0] = 4;			//gr9een
	co[i][1] = 40;		//re
	co[i][2] = 20;		//blue
	
	co[j][0] = 8;			//green
	co[j][1] = 24;		//re
	co[j][2] = 80;		//blue
	
	co[k][0] = 4;			//green
	co[k][1] = 40;		//re
	co[k][2] = 20;		//blue
	
//	if(te%6){
//		co[15][0] = 30;			//green
//		co[15][1] = 10;		//re
//		co[15][2] = 6;		//blue
//	}
	te += 1;
	
	//点灯
	WS2812_send(co,16);
}
/**************************************************************************
	点亮灯环,方位显示
	总共16个灯，每个灯之间间隔360°/16=22.5°
	每次点亮四个灯表示方位
	入口参数为 x轴 与地磁北极 沿顺时针方向的夹角
**************************************************************************/
void Light_Ring_dirc(u8 direction)
{
	u8 i=0,j=0;
	uint8_t co[16][3]={0};

	//方位对次序映射
	switch(direction){
		case FORWARD: 				i=14;break;
		case FORWARD_RIGNT: 	i=0;break;
		case RIGHT: 					i=2;break;
		case BACKWARD_RIGHT: 	i=4;break;		
		case BACKWARD: 				i=6;break;
		case BACKWARD_LEFT: 	i=8;break;
		case LEFT: 						i=10;break;
		case FORWARD_LEFT: 		i=12;break;
	}

	for(j=0;j<4;i++){
		i += j;
		i %= 16;
		co[i][0] = 2;			//green
		co[i][1] = 10;		//re
		co[i][2] = 100;		//blue
}
	//点灯
	WS2812_send(co,16);
}


/**************************************************************************
	点亮灯环,温湿度显示
	总共16个灯，0~6表示温度    8~14表示湿度
	分辨率为：温度每格表示5°C  湿度每格表示10% 
	表示起点：0°
**************************************************************************/
void Light_Ring_RT(u8 *temp,u8 *humi)
{
	u8 temp_h=0,temp_t=0,j=0;
	uint8_t co[16][3]={0};

	//数值对次序映射
	for(j=0;j<6;j++){
		temp_h = *humi / 10 - 1;
		temp_t = *temp / 10 - 1;
		if(j<=temp_h){
			co[8+j][0] = 2;			//green
			co[8+j][1] = 5;		//re
			co[8+j][2] = 80;		//blue
		}
		if(j<=temp_t){
			co[6-j][0] = 2;			//green
			co[6-j][1] = 80;		//re
			co[6-j][2] = 5;		//blue
		}
	}
	//最下面那个灯
	co[7][0] = 80;			//green
	co[7][1] = 6;		//re
	co[7][2] = 20;		//blue
	//点灯
	WS2812_send(co,16);
}
























