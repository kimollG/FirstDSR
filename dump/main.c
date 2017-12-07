#include "main.h"

#define PA8 GPIO_Pin_8
#define PA9 GPIO_Pin_9
#define PA10 GPIO_Pin_10
#define PE0 GPIO_Pin_0
#define PE1 GPIO_Pin_1
#define PERIOD 100000
#define PRESCALER 1600

int main(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable peripheral clock for GPIOD port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);
  /* Init leds */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = PA9|PA10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = PE0|PE1;
  GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);


  TIM_TimeBaseInitTypeDef tim_struct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  tim_struct.TIM_Period = PERIOD/60 -1 ;
  tim_struct.TIM_Prescaler = PRESCALER ;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &tim_struct);
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
  TIM_Cmd(TIM1,ENABLE);

  TIM_OCInitTypeDef PWM_struct;
  PWM_struct.TIM_OCMode=TIM_OCMode_PWM1;
  PWM_struct.TIM_Pulse=150;
  TIM_OC1Init(TIM1,&PWM_struct);
  TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
  int x=0;
  GPIOA->BSRRL=PA9|PA10;

  while (1)
  {
      if(TIM_GetCounter(TIM1)==0)
      {
        if(GPIO_ReadInputDataBit(GPIOE,PE0)=0)
        {
          x=(++x)%16;
          TIM_SetCompare2(
        }
      }
  }
}
