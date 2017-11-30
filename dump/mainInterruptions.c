#include "main.h"

#define SWITCH_DELAY 16000000
#define LED1_PIN GPIO_Pin_12
#define LED2_PIN GPIO_Pin_13
#define LED3_PIN GPIO_Pin_14
#define LED4_PIN GPIO_Pin_15
#define PA8 GPIO_Pin_8
#define PA9 GPIO_Pin_9
#define PA10 GPIO_Pin_10
#define PE0 GPIO_Pin_0
#define PE1 GPIO_Pin_1
#define PERIOD 1000000
#define PRESCALER 84

  
int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable peripheral clock for GPIOD port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);
  /* Init leds */
  GPIO_InitStructure.GPIO_Pin = LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

/* Init leds */
  GPIO_InitStructure.GPIO_Pin = PA8|PA9|PA10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = PE0|PE1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  EXTI_InitTypeDef EXTI_InitStruct;
  EXTI_InitStruct.EXTI_Line = EXTI_Line0;
  EXTI_InitStruct.EXTI_LineCmd= ENABLE;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger= EXTI_Trigger_Rising;
  EXTI_Init(&EXTI_InitStruct);

  NVIC_InitTypeDef NVIC_InitStruct;
  NVIC_InitStruct.NVIC_IRQChannel= EXTI0_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0x00;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
  NVIC_Init(&NVIC_InitStruct);

  
  while (1)
  {
      GPIOD->BSRRL = LED2_PIN;

  }
}
int i=0;
  void EXTI0_IRQHandler(void)
  {
   GPIOD->BSRRL = LED1_PIN;

    if(EXTI_GetITStatus(EXTI_Line0)!= RESET)
    {
      if((i=(++i)%3)==0)
              {   
                GPIOA->BSRRL = PA9;
                GPIOA->BSRRH = PA8;
              }
              else if(i==1)
              {
                GPIOA->BSRRL = PA8;
                GPIOA->BSRRH = PA10;
              }
              else if(i==2)
              {
                GPIOA->BSRRL = PA10;
                GPIOA->BSRRH = PA9;
              }
      GPIOD->BSRRL = LED1_PIN;
      EXTI_ClearITPendingBit(EXTI_Line0);
    }
  }
