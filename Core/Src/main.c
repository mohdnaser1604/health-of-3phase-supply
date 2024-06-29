/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "modbus_crc.h"
#include <stdio.h>
#include "stm32f1xx_ll_usart.h"

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
UART_HandleTypeDef huart1;// Handle for UART1 peripheral
UART_HandleTypeDef huart2;// Handle for UART2 peripheral

/* USER CODE BEGIN PV */
uint8_t RxData[100];// Buffer to store received data
uint8_t RxData_temp[100];// Temporary buffer for received data processing
uint8_t TxData[8]; // Buffer to store data to be transmitted
uint8_t i=0; // Index for received data buffer


void RxFuncData(void); // Function prototype for receiving data

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void sendData(uint8_t *data);// Function prototype to send data
void toggle_debug_led(void);// Function prototype to toggle debug LED
//float extractFloatMidLittleEndian(uint8_t *data);
int __io_putchar(int ch);// Function prototype for printf redirection



/* USER CODE END PFP */
union FloatBytes {         // Union to convert between float and byte array
    uint8_t bytes[4];
    float value;
}floatVAr;



void RxFuncData(void) {
	 RxData[i] = LL_USART_ReceiveData8(USART1);// Receive data from USART1

	 i++;// Increment index
}



void sendData (uint8_t *data)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET); // Set PA8 high to enable transmission
	    HAL_UART_Transmit(&huart1, data, 8, 1000);// Transmit data
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);// Set PA8 low to disable transmission

}
void toggle_debug_led(void)
{
    // Toggle the LED for debugging purposes
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Adjust pin as needed
}
/* USER CODE END 0 */

//float extractFloatMidLittleEndian(uint8_t *data) {
 //   uint32_t temp = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
   // return *((float*)&temp);
//}
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

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
	 // Variables to store various electrical parameters such as voltages, currents, and power
	float voltagev1, voltagev2, voltagev3,AverageVoltageLN,VoltageV12,Voltagev23,voltagev31,averagevoltageLL,currentl1,currentl2,currentl3,averagecurrent,
		kW1,kW2,kW3,kVA1,kVA2,kVA3,kVAr1,kVAr2,kVAr3,TotalKW;

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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, RxData, 32);//// Start UART reception with interrupt

   TxData[0] = 0x01;  // slave address
 //  TxData[1] = 0x03;  // Function code for Read Holding Registers
   TxData[1] = 0x04;  // Function code for Read Input Registers

   /*
    * The function code 0x03 means we are reading Holding Registers
    * The Register address ranges from 40001 - 50000
    * The register address we input can range from 0-9999 (0x00-0x270F)
    * Here 0 corresponds to the Address 40001 and 9999 corresponds to 50000
    * Although we can only read 125 registers sequentially at once
    */
 //  TxData[2] = 0;
 //  TxData[3] = 0x04;
 //  //The Register address will be 00000000 00000100 = 4 + 40001 = 40005

   TxData[2] = 0; // Starting address high byte
   TxData[3] = 0x00; // Starting address low byte
   //The Register address will be 00000000 00000001 = 1 +30001 = 30002

   TxData[4] = 0;// Number of registers high byte
   TxData[5] = 0x2A;// Number of registers low byte (42 registers)
   // no of registers to read will be 00000000 00000101 = 42 Registers = 84Bytes

   uint16_t crc = crc16(TxData, 6);// Calculate CRC
   TxData[6] = crc&0xFF;   // CRC LOW
   TxData[7] = (crc>>8)&0xFF;  // CRC HIGH




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  HAL_Delay(1000);// Wait for 1 second
		  sendData(TxData);// Send Modbus request
		  toggle_debug_led(); // Toggle debug LED
		  HAL_Delay(1000);// Wait for 1 second

		  // Check if enough data is received
		  if (i >86 )
		  {
			RxData_temp[0] = RxData[0];// Process received data
			i=0;// Reset index
		    }


  // Extract and store voltage and current values from received data
		  int index = 3; // Starting index of RxData array for voltage values
		  for (int i = 0; i < 22; i++) {
		      floatVAr.bytes[1] = RxData[index++];
		      floatVAr.bytes[0] = RxData[index++];
		      floatVAr.bytes[3] = RxData[index++];
		      floatVAr.bytes[2] = RxData[index++];
		      switch (i) {
		          case 0:
		              voltagev1 = floatVAr.value;
		              break;
		          case 1:
		              voltagev2 = floatVAr.value;
		              break;
		          case 2:
		              voltagev3 = floatVAr.value;
		              break;
		          case 3:
		              AverageVoltageLN = floatVAr.value;
		              break;
		          case 4:
		              VoltageV12 = floatVAr.value;
		              break;
		          case 5:
		                 Voltagev23 = floatVAr.value;
		                 break;
		          case 6:
		                 voltagev31 = floatVAr.value;
		                 break;
		          case 7:
		                 averagevoltageLL = floatVAr.value;
		                 break;
		          case 8:
		                 currentl1 = floatVAr.value;
		                 break;
		          case 9:
		                 currentl2 = floatVAr.value;
		                 break;
		          case 10:
		                 currentl3 = floatVAr.value;
		                 break;
		          case 11:
		                 averagecurrent = floatVAr.value;
		                 break;
		          case 12:
		                  kW1 = floatVAr.value;
		                  break;
		          case 13:
		                  kW2 = floatVAr.value;
		                  break;
		          case 14:
		                  kW3 = floatVAr.value;
		                  break;
		          case 15:
		                  kVA1 = floatVAr.value;
		                  break;
		          case 16:
		                  kVA2 = floatVAr.value;
		                  break;
		          case 17:
		                  kVA3 = floatVAr.value;
		                  break;
		          case 18:
		                  kVAr1 = floatVAr.value;
		                  break;
		          case 19:
		                  kVAr2 = floatVAr.value;
		                  break;
		          case 20:
		                  kVAr3 = floatVAr.value;
		                  break;
		          case 21:
		                  TotalKW = floatVAr.value;
		                  break;






		      }

		  }
		  // Print extracted values
		         printf("Voltage V1: %.2f\r\n", voltagev1);
		         printf("Voltage V2: %.2f\r\n", voltagev2);
		         printf("Voltage V3: %.2f\r\n", voltagev3);
		         printf("Average Voltage LN: %.2f\r\n", AverageVoltageLN);
		         printf("Voltage V12: %.2f\r\n", VoltageV12);
		         printf("Voltage V23: %.2f\r\n", Voltagev23);
		         printf("Voltage V31: %.2f\r\n", voltagev31);
		         printf("Average Voltage LL: %.2f\r\n", averagevoltageLL);
		         printf("Current L1: %.2f\r\n", currentl1);
		         printf("Current L2: %.2f\r\n", currentl2);
		         printf("Current L3: %.2f\r\n", currentl3);
		         printf("Average Current: %.2f\r\n", averagecurrent);
		         printf("kW1: %.2f\r\n", kW1);
		         printf("kW2: %.2f\r\n", kW2);
		         printf("kW3: %.2f\r\n", kW3);
		         printf("kVA1: %.2f\r\n", kVA1);
		         printf("kVA2: %.2f\r\n", kVA2);
		         printf("kVA3: %.2f\r\n", kVA3);
		         printf("kVAr1: %.2f\r\n", kVAr1);
		         printf("kVAr2: %.2f\r\n", kVAr2);
		         printf("kVAr3: %.2f\r\n", kVAr3);
		         printf("Total KW: %.2f\r\n", TotalKW);





    /* USER CODE BEGIN 3 */

   }
  /* USER CODE END 3 */
 }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|TX_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin TX_EN_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|TX_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
