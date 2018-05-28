#include<stm32f4xx_rcc.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_syscfg.h>
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "tm_stm32f4_pcd8544.h"
#include "tm_stm32f4_spi.h"
#include <misc.h>
#include "defines.h"
#include "stm32f4xx.h"
#define X1 1
#define X2 82
#define Y1 11
#define Y2 46

typedef struct
{
int jest;
}sqr;

sqr tab[81][35];
int punkty=1234;
TM_LIS302DL_LIS3DSH_t Axes;

int abs(int x)
{
	if(x<0)return -x;
	if(x>=0)return x;
}
movesnake(int i)
{
	switch(i)
	{
		case '0':
		{

		}
		case '1':
		{

		}
		case '2':
		{

		}
		case '3':
		{

		}
	}
}
void TIM3_IRQHandler()//TIMER odpowiedzialny za predkosc snake'a
{


    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
    	 TM_LIS302DL_LIS3DSH_ReadAxes(&Axes);

    	    int i;
    	    for(i=0;i<0xFFF;i++){}
    		    if(Axes.X<-200&&abs(Axes.X)>abs(Axes.Y))
    		    {
    		    	if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_15);//movesnake(0);
    	    	}else{
    	    		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    	    	}
    		   if(Axes.X>200&&abs(Axes.X)>abs(Axes.Y))
    		    {
    			    if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_13);//movesnake(0);
    		    }else{
    	    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    	    	}

    		   if(Axes.Y<-200&&abs(Axes.Y)>abs(Axes.X))
    		   {

    			   if(abs(Axes.Y)>abs(Axes.X))GPIO_SetBits(GPIOD, GPIO_Pin_12);//movesnake(0);
    		   }
    		   else
    		   {
    		    		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    		   }
    			   if(Axes.Y>200&&abs(Axes.Y)>abs(Axes.X))
    			    {
    				   if(abs(Axes.Y)>abs(Axes.X))GPIO_SetBits(GPIOD, GPIO_Pin_14);//movesnake(0);
    			    }else{
    		    		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    		    	}

    }



TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void TIM2_IRQHandler()//Odpowiedzialny za wyswietlanie i update wyswietlacza (f= 100 Hz)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

            	 PCD8544_DrawRectangle(X1-1,Y1-1,X2+1,Y2+1,PCD8544_Pixel_Set);
            	 /* tab[40][20].jest=1;
            	 tab[40][21].jest=1;
            	 int tysiace, setki, dziesiatki, jednosci,points=punkty;
            	 tysiace=points/1000;
            	 points=points-tysiace*1000;
            	 setki=points/100;
            	 points=points-setki*100;
            	 dziesiatki=points/10;
            	 points=points-dziesiatki*10;
            	 jednosci=points;
            	 PCD8544_GotoXY(1,1);
            	 PCD8544_Putc(tysiace+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            	 PCD8544_GotoXY(6,1);
            	 PCD8544_Putc(setki+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            	 PCD8544_GotoXY(11,1);
            	 PCD8544_Putc(dziesiatki+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            	 PCD8544_GotoXY(16,1);
            	 PCD8544_Putc(jednosci+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            	 PCD8544_Home();
            	 /* int i=0,j=0;
            	 for(i;i<X2;i=i+1)
            	 {
            		 for(j;j<Y2;j=j+1)
            		 {
            		 if(tab[i][j].jest==1)PCD8544_DrawPixel(i+1,j+11,PCD8544_Pixel_Set);
            		 PCD8544_Refresh();
            		 }
            	 }


*/
	}
PCD8544_Refresh();
TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}


int main(void)
{
		SystemInit();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 839;
		TIM_TimeBaseStructure.TIM_Prescaler = 99;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
		TIM_TimeBaseStructure2.TIM_Period = 8399;
		TIM_TimeBaseStructure2.TIM_Prescaler = 2499;
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
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12;
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_All;
		GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
		GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitDef);

    PCD8544_Init(0x38);
    PCD8544_SetContrast(0x00);



	while(1){}

}
