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


  TIM_TimeBaseInitTypeDef tim_struct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  tim_struct.TIM_Period = PERIOD -1;
  tim_struct.TIM_Prescaler = PRESCALER - 1;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &tim_struct);
  //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
  TIM_Cmd(TIM2,ENABLE);

  int i=0;
  int current=0;
  int flag=0;
  while (1)
  {
      /*if(GPIO_ReadInputDataBit(GPIOE,PE1)==0)
        GPIOD->BSRRL = LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;*/
//flag=1;

      if(GPIO_ReadInputDataBit(GPIOE,PE0)==0)
        flag=0;
      if(GPIO_ReadInputDataBit(GPIOE,PE1)==0)
        flag=1;
      
      if(flag)
        GPIOD->BSRRL = LED1_PIN|LED2_PIN|LED3_PIN/*|LED4_PIN*/;
      else
        GPIOD->BSRRH = LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;

	  if(TIM_GetCounter(TIM2)==0)
          {
            if(flag)
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
            }
            else
            {
             if((i=(++i)%3)==0)
              {   
                GPIOA->BSRRL = PA9;
                GPIOA->BSRRH = PA10;
              }
              else if(i==1)
              {
                GPIOA->BSRRL = PA10;
                GPIOA->BSRRH = PA8;
              }
              else if(i==2)
              {
                GPIOA->BSRRL = PA8;
                GPIOA->BSRRH = PA9;
              } 
            }
          }
          //else if(TIM_GetCounter(TIM2)==500000)
          /*GPIOA->BSRRL = PA8;
          GPIOA->BSRRH = PA10;
	  Switch LED off
          GPIOA->BSRRL = PA10;
          GPIOA->BSRRH = PA9;*/
  }
}
