#include<stm32f4xx_rcc.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_syscfg.h>
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "tm_stm32f4_pcd8544.h"
#include "tm_stm32f4_spi.h"
#include <misc.h>

#define WIDTH 30
#define LENGTH 20

typedef struct
{
int jest;
}bloczek;

bloczek tab[WIDTH/4][LENGTH/4];

int punkty=0;
TM_LIS302DL_LIS3DSH_t Axes;
int abs(int x){

	if(x<0)return -x;
	if(x>=0)return x;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TIM3_IRQHandler()//TIMER odpowiedzialny za prêdkoœæ snake'a
{


    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {

    TM_LIS302DL_LIS3DSH_ReadAxes(&Axes);

    int i;
    for(i=0;i<0xFFF;i++){}
	    if(Axes.X<-200&&abs(Axes.X)>abs(Axes.Y))
	    {
	    	if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_15);
    	}else{
    		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    	}
	   if(Axes.X>200&&abs(Axes.X)>abs(Axes.Y))
	    {
		    if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_13);
	    }else{
    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    	}

	   if(Axes.Y<-200&&abs(Axes.Y)>abs(Axes.X))
		    {

		    GPIO_SetBits(GPIOD, GPIO_Pin_12);
	    	}else{
	    		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	    	}
		   if(Axes.Y>200&&abs(Axes.Y)>abs(Axes.X))
		    {
			   if(abs(Axes.Y)>abs(Axes.X))GPIO_SetBits(GPIOD, GPIO_Pin_14);
		    }else{
	    		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	    	}

    }



PCD8544_Clear();
TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler()//Odpowiedzialny za wyswietlanie i update wyswietlacza (f= 100 Hz)
{
             if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
             {

            	 int i,j;
            	 	for(j=0;j<LENGTH;j++)
            	 	{
            	 		 for(i=0;i<WIDTH;i++)
            	 	 	{
            	 		 PCD8544_GotoXY(i,j);
							if(tab[i][j].jest==1)
							{
            	 			//Funkcja do rysowania, nie zdecydowa³em jaka "gruboœæ" wê¿a, i nie mam pojêcia jak animowaæ g³owê. Do pracy mam piksele, a ¿eby g³owa by³a animowana to trzeba ich trochê zu¿yæ, co wp³ynie na "wielkoœæ" samego snake'a.
            	 			PCD8544_Refresh();
            	 			}
            	 	    }
            	 	}


            	 	PCD8544_Refresh();
                    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
             }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 209;
	TIM_TimeBaseStructure.TIM_Prescaler = 249;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	TIM_TimeBaseStructure2.TIM_Period = 839;
	TIM_TimeBaseStructure2.TIM_Prescaler = 499;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure2);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TM_LIS302DL_LIS3DSH_Init(TM_LIS302DL_Sensitivity_2_3G, TM_LIS302DL_Filter_2Hz);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitDef;
	//Apply settings just to GPIO_Pin_13:
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12;
	//This will apply same settings to all pins for one GPIO
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
	//Without pull resistors
	GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//50MHz pin speed
	GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;

	//Initialize pins on GPIOG port
	GPIO_Init(GPIOD, &GPIO_InitDef);

    PCD8544_Init(0x38);

	while(1){}












}
