/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
<<<<<<< HEAD
=======
#include "app_rtthread.h"
>>>>>>> test

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t cardin_flag = 3;
uint8_t stop_flag2 = 0;
//uint8_t cardout_flag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void sense(void);
void stop(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
<<<<<<< HEAD
=======
  MX_RT_Thread_Init();
>>>>>>> test
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_RESET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(FMQ_GPIO_Port,FMQ_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_CTR_GPIO_Port,LED_CTR_Pin,GPIO_PIN_SET);
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE);//串口2空闲中断打开
	HAL_UART_Receive_DMA(&huart2,Usart2Type.usartDMA_rxBUF,RECEIVELEN);//打开串口2的DMA接收

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

<<<<<<< HEAD
=======
    MX_RT_Thread_Process();
>>>>>>> test
    /* USER CODE BEGIN 3 */
    sense();
    usart2process();
    stop();
<<<<<<< HEAD
=======
    
>>>>>>> test
	}
}
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
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
<<<<<<< HEAD
          Usart2SendData_DMA(photo,3); //发�?�申�?
=======
          Usart2SendData_DMA(photo,3); //发�?�申�??
>>>>>>> test
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t i=0 ;

  if(htim->Instance == TIM3)
  {
    i++;
<<<<<<< HEAD
    if((i>8)||(refuse_flag == 1))
=======
    if((i>10)||(refuse_flag == 1))
>>>>>>> test
    {
      i = 0;
      stop_flag = 0;
      HAL_TIM_Base_Stop_IT(&htim3);
      stop_flag2 = 1;
			refuse_flag = 0;
    }
		if(stop_flag == 1)
		{ 
			i = 0;
      stop_flag = 0;
      HAL_TIM_Base_Stop_IT(&htim3);	
    }
   }
}
void stop(void)
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
<<<<<<< HEAD

}
=======
}

>>>>>>> test
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
