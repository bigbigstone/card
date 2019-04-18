/*
 * File      : app_rtthread.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include "stm32f0xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#define PROPERTY 30
uint8_t cardin_flag = 3;
uint8_t stop_flag2 = 0;

void sense(void)
{
  if((HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin) != 1)&&(HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=1))
  {
      HAL_Delay(50);
      if((HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin) != 1)&&(HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=1))
  {
    cardin_flag = 1;
  }

  }
  if((HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=0)&&(HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin)!=1)&&(cardin_flag ==1))
  
  {
        HAL_Delay(250);
       if((HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=0)&&(HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin)!=1)&&(cardin_flag ==1))
        {
          cardin_flag = 0;
          Usart2SendData_DMA(photo,3); //
          HAL_TIM_Base_Start_IT(&htim3);
        }
  }
  if((HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin) != 0)&&(HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=0))
  {
      HAL_Delay(50);
      if((HAL_GPIO_ReadPin(TOUCH_IN_GPIO_Port,TOUCH_IN_Pin) != 0)&&(HAL_GPIO_ReadPin(TOUCH_OUT_GPIO_Port,TOUCH_OUT_Pin)!=0))
    {
    cardin_flag = 0;
    }

 }
}

void stop(void)
{
  while(1)
  {
    if(stop_flag2 == 1)
    {
      stop_flag2 = 0;
      HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_RESET);
      HAL_Delay(200);
      HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_SET); 
      HAL_Delay(200);
      HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_RESET);
      HAL_Delay(200);
      HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_SET); 
    }
    rt_thread_mdelay(10);
  }
}

void MX_RT_Thread_Init(void)
{
    rt_thread_t thread1;
    rt_thread_t thread2;
    rt_thread_t thread3;
    thread1 = rt_thread_create("sense",sense,RT_NULL,128,PROPERTY,8);
    if(thread1 != RT_NULL)
    {
        rt_thread_startup(thread1);
    }
    thread2 = rt_thread_create("uart2process",usart2process,RT_NULL,256,PROPERTY-1,8);
    if(thread2 != RT_NULL)
    {
        rt_thread_startup(thread2);
    }
    thread3 = rt_thread_create("stop",stop,RT_NULL,128,PROPERTY+1,8);
    if(thread3 != RT_NULL)
    {
        rt_thread_startup(thread3);
    }
}

void MX_RT_Thread_Process(void)
{

}



