#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
 

static GPIO_InitTypeDef PORTC3;
static GPIO_InitTypeDef PORTE3;

int main(void) 
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE,ENABLE);
	
		GPIO_StructInit(&PORTE3);
		PORTE3.GPIO_Pin = GPIO_Pin_3; 
		PORTE3.GPIO_Mode = GPIO_Mode_IN;   
		GPIO_Init(GPIOC, &PORTE3);  
	
		GPIO_StructInit(&PORTC3);
		PORTC3.GPIO_Pin = GPIO_Pin_3; 
		PORTC3.GPIO_Mode = GPIO_Mode_OUT;   
		GPIO_Init(GPIOE, &PORTC3); 
		
		
		while (1) 
		{
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) == 0)
				{
						GPIO_SetBits(GPIOE,GPIO_Pin_3);
				}
				else
				{
						GPIO_ResetBits(GPIOE,GPIO_Pin_3);
				}
		}
}
