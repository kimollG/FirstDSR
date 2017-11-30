#include "main.h"

#define SWITCH_DELAY 4000000
#define LED1_PIN GPIO_Pin_12
#define LED2_PIN GPIO_Pin_13
#define LED3_PIN GPIO_Pin_14
#define LED4_PIN GPIO_Pin_15
#define PA8 GPIO_Pin_8
#define PA9 GPIO_Pin_9
#define PA10 GPIO_Pin_10



int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable peripheral clock for GPIOD port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

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
  int i;
  while (1)
  {
	  /* Switch LED on */
          GPIOA->BSRRL = PA9;
          GPIOA->BSRRH = PA8;

	  GPIOD->BSRRL = LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;
	  for (i=0; i < SWITCH_DELAY; i++)
	  {

	    /* empty cycle */
	  }
          GPIOA->BSRRL = PA8;
          GPIOA->BSRRH = PA10;
          for (i=0; i < SWITCH_DELAY; i++)
	  {

	    /* empty cycle */
	  }
	  /* Switch LED off */
	  GPIOD->BSRRH = LED1_PIN|LED2_PIN|LED3_PIN|LED4_PIN;
	  
          GPIOA->BSRRL = PA10;
          GPIOA->BSRRH = PA9;
          for (i=0; i < SWITCH_DELAY; i++)
	  {
	    /* empty cycle */
	  }
  }
}
