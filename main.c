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
int head;
int tail;
int jest;
int bonus;
}sqr;

sqr tab[81][35];
int punkty=1234;
TM_LIS302DL_LIS3DSH_t Axes;

int abs(int x)
{
	if(x<0)return -x;
	if(x>=0)return x;
}
void spawnsnake(){
	int i=0,j=0;
	for(;i<81;i=i+1)
	{
		for(;j<35;j=j+1)
		{
		tab[i][j].jest=0;
		tab[i][j].head=0;
		tab[i][j].tail=0;
		}
	}
	tab[40][17].jest=1;
	tab[40][17].tail=1;
	tab[41][17].jest=1;
	tab[42][17].jest=1;
	tab[42][17].head=1;
	tab[50][22].bonus==1;

}
void gameover(){
	 	 	 int tysiace, setki, dziesiatki, jednosci,points=punkty;
           	 tysiace=points/1000;
           	 points=points-tysiace*1000;
           	 setki=points/100;
           	 points=points-setki*100;
           	 dziesiatki=points/10;
           	 points=points-dziesiatki*10;
           	 jednosci=points;
           	 PCD8544_Clear();
           	 PCD8544_GotoXY(34,36);
           	 PCD8544_Putc(tysiace+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
           	 PCD8544_GotoXY(39,36);
           	 PCD8544_Putc(setki+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
           	 PCD8544_GotoXY(44,36);
           	 PCD8544_Putc(dziesiatki+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
           	 PCD8544_GotoXY(49,36);
           	 PCD8544_Putc(jednosci+0x30,PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
           	 PCD8544_Puts("Game over",PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
           	 PCD8544_Refresh();
}
 void movesnake(int i)
{
	int tailx, taily, headx, heady;
	int k,j;
	for(k=0;k<81;k=k+1)
		{
			for(j=0;j<35;j=j+1)
			{
				if(tab[k][j].jest==1&&tab[k][j].tail==1)
				{
				tailx=k;
				taily=j;
				}
				if(tab[k][j].jest==1&&tab[k][j].head==1)
				{
				headx=k;
				heady=j;
				}
			}
		}
	switch(i)
	{
		case 0:
		{
		if(heady==0)gameover();
		if(tab[headx][heady-1].bonus==1)
			{
			tab[headx][heady-1].jest=1;
			tab[headx][heady-1].head=1;
			tab[headx][heady-1].bonus=0;
			tab[TIM3->PSC%80][TIM3->CNT%34].bonus=1;
			break;
			}else{
				 if(tab[tailx][taily-1].jest==1)tab[tailx][taily-1].tail=1;
				 if(tab[tailx-1][taily].jest==1)tab[tailx-1][taily].tail=1;
				 if(tab[tailx+1][taily].jest==1)tab[tailx+1][taily].tail=1;
				 if(tab[tailx][taily+1].jest==1)tab[tailx][taily+1].tail=1;
				 tab[tailx][taily].jest=0;
				 tab[headx][heady].head=0;
				 if(tab[headx][heady-1].jest==1)gameover();
				 tab[headx][heady-1].jest=1;
				 tab[headx][heady-1].head=1;
				 break;
				 }
		}
		case 1:
		{
		if(headx==80)gameover();
		if(tab[headx+1][heady].bonus==1){
			tab[headx+1][heady].jest=1;
			tab[headx+1][heady].head=1;
			tab[headx+1][heady].bonus=0;
			tab[TIM3->PSC%80][TIM3->CNT%34].bonus=1;
			break;
			}else{
				if(tab[tailx][taily-1].jest==1)tab[tailx][taily-1].tail=1;
				if(tab[tailx-1][taily].jest==1)tab[tailx-1][taily].tail=1;
				if(tab[tailx+1][taily].jest==1)tab[tailx+1][taily].tail=1;
				if(tab[tailx][taily+1].jest==1)tab[tailx][taily+1].tail=1;
				tab[tailx][taily].jest=0;
				tab[headx][heady].head=0;
				if(tab[headx+1][heady].jest==1)gameover();
				tab[headx+1][heady].jest=1;
				tab[headx+1][heady].head=1;
				break;
				 }
		}
		case 2:
		{
		if(headx==0)gameover();
		if(tab[headx][heady+1].bonus==1){
			tab[headx][heady+1].jest=1;
			tab[headx][heady+1].head=1;
			tab[headx][heady+1].bonus=0;
			tab[TIM3->PSC%80][TIM3->CNT%34].bonus=1;
			break;
			}else{
				if(tab[tailx][taily-1].jest==1)tab[tailx][taily-1].tail=1;
				if(tab[tailx-1][taily].jest==1)tab[tailx-1][taily].tail=1;
				if(tab[tailx+1][taily].jest==1)tab[tailx+1][taily].tail=1;
				if(tab[tailx][taily+1].jest==1)tab[tailx][taily+1].tail=1;
				tab[tailx][taily].jest=0;
				tab[headx][heady].head=0;
				if(tab[headx][heady+1].jest==1)gameover();
				tab[headx][heady+1].jest=1;
				tab[headx][heady+1].head=1;
				break;
				}
		}
		case 3:
		{
		if(heady==34)gameover();
		if(tab[headx-1][heady].bonus==1)
			{
			tab[headx-1][heady].jest=1;
			tab[headx-1][heady].head=1;
			tab[headx-1][heady].bonus=0;
			tab[TIM3->PSC%80][TIM3->CNT%34].bonus=1;
			break;
			}else{
				 if(tab[tailx][taily-1].jest==1)tab[tailx][taily-1].tail=1;
				 if(tab[tailx-1][taily].jest==1)tab[tailx-1][taily].tail=1;
				 if(tab[tailx+1][taily].jest==1)tab[tailx+1][taily].tail=1;
				 if(tab[tailx][taily+1].jest==1)tab[tailx][taily+1].tail=1;
				 tab[tailx][taily].jest=0;
			     tab[headx][heady].head=0;
			     if(tab[headx-1][heady].jest==1)gameover();
				 tab[headx-1][heady].jest=1;
				 tab[headx-1][heady].head=1;
				 break;
				 }
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
    		    	if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_15);
    		    	movesnake(0);
    	    	}else{
    	    		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    	    	}
    		   if(Axes.X>200&&abs(Axes.X)>abs(Axes.Y))
    		    {
    			    if(abs(Axes.X)>abs(Axes.Y))GPIO_SetBits(GPIOD, GPIO_Pin_13);
    			    movesnake(1);
    		    }else
    		    {
    	    		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    	    	}
    		   if(Axes.Y<-200&&abs(Axes.Y)>abs(Axes.X))
    		   {

    			   if(abs(Axes.Y)>abs(Axes.X))GPIO_SetBits(GPIOD, GPIO_Pin_12);
    			   movesnake(2);
    		   }
    		   else
    		   {
    		       GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    		   }
    		   if(Axes.Y>200&&abs(Axes.Y)>abs(Axes.X))
    		   {
    				if(abs(Axes.Y)>abs(Axes.X))GPIO_SetBits(GPIOD, GPIO_Pin_14);
    				   movesnake(3);
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
            	 int i,j;
            	 for(i=0;i<81;i=i+1)
            	 {
            		 for(j=0;j<35;j=j+1)
            		 {
            		 if(tab[i][j].jest==1)PCD8544_DrawPixel(i+1,j+10,PCD8544_Pixel_Set);
            		 if(tab[i][j].bonus==1)PCD8544_DrawPixel(i+1,j+10,PCD8544_Pixel_Set);
            		 PCD8544_Refresh();
            		 }
            	 }




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
		spawnsnake();
		PCD8544_Init(0x38);
		while(1){}
}
