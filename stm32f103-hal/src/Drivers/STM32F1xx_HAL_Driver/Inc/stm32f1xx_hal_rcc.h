/**
  ******************************************************************************
  * @file    stm32f1xx_hal_rcc.h
  * @author  MCD Application Team
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_HAL_RCC_H
#define __STM32F1xx_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
	#endif

	#include "stm32f1xx_hal_def.h"

	/// <summary>
	///		管理 PLL 的配置的结构体
	///		例如：
	///			开启状态
	///			时钟源
	///			倍频系数
	/// </summary>
	typedef struct
	{
		/// <summary>
		///		PLL 的状态。可选值为 RCC_PLL_Config 中的一个。
		///		RCC_PLL_Config 是一组宏定义。
		/// </summary>
		uint32_t PLLState;

		/// <summary>
		///		PLL 的时钟源选择。
		///		可选值为 RCC_PLL_Clock_Source 中的一个。RCC_PLL_Clock_Source 为一组宏。
		/// 
		///		可选值：
		///			RCC_PLLSOURCE_HSE - 外部高速时钟
		///			RCC_PLLSOURCE_HSI_DIV2 - 内部高速时钟经过 2 分频。
		/// 
		///		其中，RCC_PLLSOURCE_HSI_DIV2 的二分频是强制的，它是一个直接连接的硬件分频器，
		///		无法通过寄存器位来选择是否连接。这么做可能是因为内部高速时钟的信号不干净，必须经过
		///		二分频后才能让 PLL 稳定工作。
		/// </summary>
		uint32_t PLLSource;

		/// <summary>
		///		PLL 的倍频系数。
		///		可选值为 RCCEx_PLL_Multiplication_Factor 中的一个。
		/// </summary>
		uint32_t PLLMUL;
	} RCC_PLLInitTypeDef;


	/// <summary>
	///		RCC System, AHB and APB busses clock configuration structure definition。
	/// 
	///		简单来说就是用来初始化时钟信号的。（注意区分时钟源与时钟信号）
	///		时钟信号有：SYSCLK, AHB, APB1, APB2。
	/// 
	///		时钟信号就是来自时钟源的方波经过分频器后再输出。
	/// </summary>
	typedef struct
	{
		/// <summary>
		///		选择要设置的时钟类型。
		/// 
		///		可选值为 RCC_System_Clock_Type 中的一个。
		///		RCC_System_Clock_Type 中的值可以按位或运算，也就是可以通过这种方式同时选中多个时钟类型。
		/// </summary>
		uint32_t ClockType;

		/// <summary>
		///		选择系统时钟的时钟源。可选值为 RCC_System_Clock_Source 中的一个。
		/// </summary>
		uint32_t SYSCLKSource;

		/// <summary>
		///		AHB 时钟（也叫做 HCLK）的分频系数。
		///		AHB 时钟信号来自一个分频器。该分频器输入端直接连接着 SYSCLK 的输出端。
		/// 
		///		可选值为 RCC_AHB_Clock_Source 中的一个。
		/// </summary>
		uint32_t AHBCLKDivider;

		/// <summary>
		///		APB1 时钟（也叫 PCLK1）的分频系数。
		///		这个时钟是给低速外设用的。APB1 时钟信号来自一个分频器。该分频器的输入端连接着 AHB 的输出端。
		/// 
		///		可选值为 RCC_APB1_APB2_Clock_Source 中的一个。
		/// </summary>
		uint32_t APB1CLKDivider;

		/// <summary>
		///		APB2 时钟（也叫 PCLK2）的分频系数。
		///		APB2 是给高速外设用的。APB2 时钟信号来自一个分频器。该分频器的输入端连接着 AHB 的输出端。
		/// 
		///		可选值为 RCC_APB1_APB2_Clock_Source 中的一个。
		/// </summary>
		uint32_t APB2CLKDivider;
	} RCC_ClkInitTypeDef;

	/* Exported constants --------------------------------------------------------*/
	/** @defgroup RCC_Exported_Constants RCC Exported Constants
	  * @{
	  */

	#pragma region RCC_PLL_Clock_Source
	#define RCC_PLLSOURCE_HSI_DIV2      0x00000000U     /*!< HSI clock divided by 2 selected as PLL entry clock source */
	#define RCC_PLLSOURCE_HSE           RCC_CFGR_PLLSRC            /*!< HSE clock selected as PLL entry clock source */
	#pragma endregion


	#pragma region RCC_Oscillator_Type
	#define RCC_OSCILLATORTYPE_NONE            0x00000000U
	#define RCC_OSCILLATORTYPE_HSE             0x00000001U
	#define RCC_OSCILLATORTYPE_HSI             0x00000002U
	#define RCC_OSCILLATORTYPE_LSE             0x00000004U
	#define RCC_OSCILLATORTYPE_LSI             0x00000008U
	#pragma endregion


	#pragma region RCC_HSE_Config
	#define RCC_HSE_OFF                      0x00000000U                                /*!< HSE clock deactivation */
	#define RCC_HSE_ON                       RCC_CR_HSEON                               /*!< HSE clock activation */
	#define RCC_HSE_BYPASS                   ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON)) /*!< External clock source for HSE clock */
	#pragma endregion


	#pragma region RCC_LSE_Config
	#define RCC_LSE_OFF                      0x00000000U                                    /*!< LSE clock deactivation */
	#define RCC_LSE_ON                       RCC_BDCR_LSEON                                 /*!< LSE clock activation */
	#define RCC_LSE_BYPASS                   ((uint32_t)(RCC_BDCR_LSEBYP | RCC_BDCR_LSEON)) /*!< External clock source for LSE clock */
	#pragma endregion


	#pragma region RCC_HSI_Config
	#define RCC_HSI_OFF                      0x00000000U                      /*!< HSI clock deactivation */
	#define RCC_HSI_ON                       RCC_CR_HSION                     /*!< HSI clock activation */

	#define RCC_HSICALIBRATION_DEFAULT       0x10U         /* Default HSI calibration trimming value */
	#pragma endregion


	#pragma region RCC_LSI_Config
	#define RCC_LSI_OFF                      0x00000000U              /*!< LSI clock deactivation */
	#define RCC_LSI_ON                       RCC_CSR_LSION            /*!< LSI clock activation */
	#pragma endregion


	#pragma region RCC_PLL_Config
	#define RCC_PLL_NONE                      0x00000000U  /*!< PLL is not configured */
	#define RCC_PLL_OFF                       0x00000001U  /*!< PLL deactivation */
	#define RCC_PLL_ON                        0x00000002U  /*!< PLL activation */
	#pragma endregion


	#pragma region RCC_System_Clock_Type
	#define RCC_CLOCKTYPE_SYSCLK             0x00000001U /*!< SYSCLK to configure */
	#define RCC_CLOCKTYPE_HCLK               0x00000002U /*!< HCLK to configure */
	#define RCC_CLOCKTYPE_PCLK1              0x00000004U /*!< PCLK1 to configure */
	#define RCC_CLOCKTYPE_PCLK2              0x00000008U /*!< PCLK2 to configure */
	#pragma endregion


	#pragma region RCC_System_Clock_Source System Clock Source
	#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI /*!< HSI selected as system clock */
	#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE /*!< HSE selected as system clock */
	#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL /*!< PLL selected as system clock */
	#pragma endregion


	#pragma region RCC_System_Clock_Source_Status
	#define RCC_SYSCLKSOURCE_STATUS_HSI      RCC_CFGR_SWS_HSI            /*!< HSI used as system clock */
	#define RCC_SYSCLKSOURCE_STATUS_HSE      RCC_CFGR_SWS_HSE            /*!< HSE used as system clock */
	#define RCC_SYSCLKSOURCE_STATUS_PLLCLK   RCC_CFGR_SWS_PLL            /*!< PLL used as system clock */
	#pragma endregion



	#pragma region RCC_AHB_Clock_Source AHB Clock Source
	#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1   /*!< SYSCLK not divided */
	#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2   /*!< SYSCLK divided by 2 */
	#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4   /*!< SYSCLK divided by 4 */
	#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8   /*!< SYSCLK divided by 8 */
	#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16  /*!< SYSCLK divided by 16 */
	#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64  /*!< SYSCLK divided by 64 */
	#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128 /*!< SYSCLK divided by 128 */
	#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256 /*!< SYSCLK divided by 256 */
	#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512 /*!< SYSCLK divided by 512 */
	#pragma endregion



	#pragma region RCC_APB1_APB2_Clock_Source APB1 APB2 Clock Source
	#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1	/*!< HCLK not divided */
	#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2	/*!< HCLK divided by 2 */
	#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4	/*!< HCLK divided by 4 */
	#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8	/*!< HCLK divided by 8 */
	#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16	/*!< HCLK divided by 16 */
	#pragma endregion



	#pragma region RCC_RTC_Clock_Source RTC Clock Source
	#define RCC_RTCCLKSOURCE_NO_CLK          0x00000000U                 /*!< No clock */
	#define RCC_RTCCLKSOURCE_LSE             RCC_BDCR_RTCSEL_LSE         /*!< LSE oscillator clock used as RTC clock */
	#define RCC_RTCCLKSOURCE_LSI             RCC_BDCR_RTCSEL_LSI         /*!< LSI oscillator clock used as RTC clock */
	#define RCC_RTCCLKSOURCE_HSE_DIV128      RCC_BDCR_RTCSEL_HSE         /*!< HSE oscillator clock divided by 128 used as RTC clock */
	#pragma endregion



	#pragma region RCC_MCO_Index
	#define RCC_MCO1                         0x00000000U
	#define RCC_MCO                          RCC_MCO1               /*!< MCO1 to be compliant with other families with 2 MCOs*/
	#pragma endregion


	#pragma region RCC_MCOx_Clock_Prescaler
	#define RCC_MCODIV_1                    0x00000000U
	#pragma endregion


	#pragma region RCC_Interrupt
	#define RCC_IT_LSIRDY                    ((uint8_t)RCC_CIR_LSIRDYF)   /*!< LSI Ready Interrupt flag */
	#define RCC_IT_LSERDY                    ((uint8_t)RCC_CIR_LSERDYF)   /*!< LSE Ready Interrupt flag */
	#define RCC_IT_HSIRDY                    ((uint8_t)RCC_CIR_HSIRDYF)   /*!< HSI Ready Interrupt flag */
	#define RCC_IT_HSERDY                    ((uint8_t)RCC_CIR_HSERDYF)   /*!< HSE Ready Interrupt flag */
	#define RCC_IT_PLLRDY                    ((uint8_t)RCC_CIR_PLLRDYF)   /*!< PLL Ready Interrupt flag */
	#define RCC_IT_CSS                       ((uint8_t)RCC_CIR_CSSF)      /*!< Clock Security System Interrupt flag */
	#pragma endregion


	  /** @defgroup RCC_Flag Flags
		*        Elements values convention: XXXYYYYYb
		*           - YYYYY  : Flag position in the register
		*           - XXX  : Register index
		*                 - 001: CR register
		*                 - 010: BDCR register
		*                 - 011: CSR register
		* @{
		*/
		/* Flags in the CR register */
	#define RCC_FLAG_HSIRDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_HSIRDY_Pos)) /*!< Internal High Speed clock ready flag */
	#define RCC_FLAG_HSERDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_HSERDY_Pos)) /*!< External High Speed clock ready flag */
	#define RCC_FLAG_PLLRDY                  ((uint8_t)((CR_REG_INDEX << 5U) | RCC_CR_PLLRDY_Pos)) /*!< PLL clock ready flag */

	/* Flags in the CSR register */
	#define RCC_FLAG_LSIRDY                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_LSIRDY_Pos))   /*!< Internal Low Speed oscillator Ready */
	#define RCC_FLAG_PINRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PINRSTF_Pos))  /*!< PIN reset flag */
	#define RCC_FLAG_PORRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_PORRSTF_Pos))  /*!< POR/PDR reset flag */
	#define RCC_FLAG_SFTRST                  ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_SFTRSTF_Pos))  /*!< Software Reset flag */
	#define RCC_FLAG_IWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_IWDGRSTF_Pos)) /*!< Independent Watchdog reset flag */
	#define RCC_FLAG_WWDGRST                 ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_WWDGRSTF_Pos)) /*!< Window watchdog reset flag */
	#define RCC_FLAG_LPWRRST                 ((uint8_t)((CSR_REG_INDEX << 5U) | RCC_CSR_LPWRRSTF_Pos)) /*!< Low-Power reset flag */

	/* Flags in the BDCR register */
	#define RCC_FLAG_LSERDY                  ((uint8_t)((BDCR_REG_INDEX << 5U) | RCC_BDCR_LSERDY_Pos)) /*!< External Low Speed oscillator Ready */



	#pragma region 使能，禁用外设时钟
	#define __HAL_RCC_DMA1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_DMA1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_SRAM_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_SRAMEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_FLITF_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_FLITFEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_FLITFEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_CRC_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->AHBENR, RCC_AHBENR_CRCEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_DMA1_CLK_DISABLE()      (RCC->AHBENR &= ~(RCC_AHBENR_DMA1EN))
	#define __HAL_RCC_SRAM_CLK_DISABLE()      (RCC->AHBENR &= ~(RCC_AHBENR_SRAMEN))
	#define __HAL_RCC_FLITF_CLK_DISABLE()     (RCC->AHBENR &= ~(RCC_AHBENR_FLITFEN))
	#define __HAL_RCC_CRC_CLK_DISABLE()       (RCC->AHBENR &= ~(RCC_AHBENR_CRCEN))


		  /** @defgroup RCC_APB1_Clock_Enable_Disable APB1 Clock Enable Disable
		  * @brief  Enable or disable the Low Speed APB (APB1) peripheral clock.
		  * @note   After reset, the peripheral clock (used for registers read/write access)
		  *         is disabled and the application software has to enable this clock before
		  *         using it.
		  * @{
		  */
	#define __HAL_RCC_TIM2_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_TIM3_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_WWDG_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_WWDGEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_USART2_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_I2C1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_BKP_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_BKPEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_BKPEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_PWR_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_TIM2_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN))
	#define __HAL_RCC_TIM3_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN))
	#define __HAL_RCC_WWDG_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_WWDGEN))
	#define __HAL_RCC_USART2_CLK_DISABLE()    (RCC->APB1ENR &= ~(RCC_APB1ENR_USART2EN))
	#define __HAL_RCC_I2C1_CLK_DISABLE()      (RCC->APB1ENR &= ~(RCC_APB1ENR_I2C1EN))

	#define __HAL_RCC_BKP_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_BKPEN))
	#define __HAL_RCC_PWR_CLK_DISABLE()       (RCC->APB1ENR &= ~(RCC_APB1ENR_PWREN))

		  /**
		  * @}
		  */

		  /** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable_Status APB1 Peripheral Clock Enable Disable Status
		  * @brief  Get the enable or disable status of the APB1 peripheral clock.
		  * @note   After reset, the peripheral clock (used for registers read/write access)
		  *         is disabled and the application software has to enable this clock before
		  *         using it.
		  * @{
		  */

	#define __HAL_RCC_TIM2_IS_CLK_ENABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) != RESET)
	#define __HAL_RCC_TIM2_IS_CLK_DISABLED()      ((RCC->APB1ENR & (RCC_APB1ENR_TIM2EN)) == RESET)
	#define __HAL_RCC_TIM3_IS_CLK_ENABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) != RESET)
	#define __HAL_RCC_TIM3_IS_CLK_DISABLED()      ((RCC->APB1ENR & (RCC_APB1ENR_TIM3EN)) == RESET)
	#define __HAL_RCC_WWDG_IS_CLK_ENABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) != RESET)
	#define __HAL_RCC_WWDG_IS_CLK_DISABLED()      ((RCC->APB1ENR & (RCC_APB1ENR_WWDGEN)) == RESET)
	#define __HAL_RCC_USART2_IS_CLK_ENABLED()     ((RCC->APB1ENR & (RCC_APB1ENR_USART2EN)) != RESET)
	#define __HAL_RCC_USART2_IS_CLK_DISABLED()    ((RCC->APB1ENR & (RCC_APB1ENR_USART2EN)) == RESET)
	#define __HAL_RCC_I2C1_IS_CLK_ENABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_I2C1EN)) != RESET)
	#define __HAL_RCC_I2C1_IS_CLK_DISABLED()      ((RCC->APB1ENR & (RCC_APB1ENR_I2C1EN)) == RESET)
	#define __HAL_RCC_BKP_IS_CLK_ENABLED()        ((RCC->APB1ENR & (RCC_APB1ENR_BKPEN)) != RESET)
	#define __HAL_RCC_BKP_IS_CLK_DISABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_BKPEN)) == RESET)
	#define __HAL_RCC_PWR_IS_CLK_ENABLED()        ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) != RESET)
	#define __HAL_RCC_PWR_IS_CLK_DISABLED()       ((RCC->APB1ENR & (RCC_APB1ENR_PWREN)) == RESET)

		  /**
		  * @}
		  */

		  /** @defgroup RCC_APB2_Clock_Enable_Disable APB2 Clock Enable Disable
		  * @brief  Enable or disable the High Speed APB (APB2) peripheral clock.
		  * @note   After reset, the peripheral clock (used for registers read/write access)
		  *         is disabled and the application software has to enable this clock before
		  *         using it.
		  * @{
		  */
	#define __HAL_RCC_AFIO_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_GPIOA_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_GPIOB_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_GPIOC_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_GPIOD_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPDEN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_ADC1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_TIM1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_SPI1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_USART1_CLK_ENABLE()   do { \
										__IO uint32_t tmpreg; \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);\
										/* Delay after an RCC peripheral clock enabling */\
										tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);\
										UNUSED(tmpreg); \
									  } while(0U)

	#define __HAL_RCC_AFIO_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_AFIOEN))
	#define __HAL_RCC_GPIOA_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPAEN))
	#define __HAL_RCC_GPIOB_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPBEN))
	#define __HAL_RCC_GPIOC_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPCEN))
	#define __HAL_RCC_GPIOD_CLK_DISABLE()     (RCC->APB2ENR &= ~(RCC_APB2ENR_IOPDEN))
	#define __HAL_RCC_ADC1_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_ADC1EN))

	#define __HAL_RCC_TIM1_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN))
	#define __HAL_RCC_SPI1_CLK_DISABLE()      (RCC->APB2ENR &= ~(RCC_APB2ENR_SPI1EN))
	#define __HAL_RCC_USART1_CLK_DISABLE()    (RCC->APB2ENR &= ~(RCC_APB2ENR_USART1EN))
	#pragma endregion

		  /**
			* @}
			*/

	#pragma region 检查外设时钟是否使能
	#define __HAL_RCC_AFIO_IS_CLK_ENABLED()       ((RCC->APB2ENR & (RCC_APB2ENR_AFIOEN)) != RESET)
	#define __HAL_RCC_AFIO_IS_CLK_DISABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_AFIOEN)) == RESET)

	#define __HAL_RCC_GPIOA_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_IOPAEN)) != RESET)
	#define __HAL_RCC_GPIOA_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_IOPAEN)) == RESET)
	#define __HAL_RCC_GPIOB_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_IOPBEN)) != RESET)
	#define __HAL_RCC_GPIOB_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_IOPBEN)) == RESET)
	#define __HAL_RCC_GPIOC_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_IOPCEN)) != RESET)
	#define __HAL_RCC_GPIOC_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_IOPCEN)) == RESET)
	#define __HAL_RCC_GPIOD_IS_CLK_ENABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_IOPDEN)) != RESET)
	#define __HAL_RCC_GPIOD_IS_CLK_DISABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_IOPDEN)) == RESET)

	#define __HAL_RCC_ADC1_IS_CLK_ENABLED()       ((RCC->APB2ENR & (RCC_APB2ENR_ADC1EN)) != RESET)
	#define __HAL_RCC_ADC1_IS_CLK_DISABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_ADC1EN)) == RESET)

	#define __HAL_RCC_TIM1_IS_CLK_ENABLED()       ((RCC->APB2ENR & (RCC_APB2ENR_TIM1EN)) != RESET)
	#define __HAL_RCC_TIM1_IS_CLK_DISABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_TIM1EN)) == RESET)

	#define __HAL_RCC_SPI1_IS_CLK_ENABLED()       ((RCC->APB2ENR & (RCC_APB2ENR_SPI1EN)) != RESET)
	#define __HAL_RCC_SPI1_IS_CLK_DISABLED()      ((RCC->APB2ENR & (RCC_APB2ENR_SPI1EN)) == RESET)

	#define __HAL_RCC_USART1_IS_CLK_ENABLED()     ((RCC->APB2ENR & (RCC_APB2ENR_USART1EN)) != RESET)
	#define __HAL_RCC_USART1_IS_CLK_DISABLED()    ((RCC->APB2ENR & (RCC_APB2ENR_USART1EN)) == RESET)

	#define __HAL_RCC_DMA1_IS_CLK_ENABLED()       ((RCC->AHBENR & (RCC_AHBENR_DMA1EN)) != RESET)
	#define __HAL_RCC_DMA1_IS_CLK_DISABLED()      ((RCC->AHBENR & (RCC_AHBENR_DMA1EN)) == RESET)

	#define __HAL_RCC_SRAM_IS_CLK_ENABLED()       ((RCC->AHBENR & (RCC_AHBENR_SRAMEN)) != RESET)
	#define __HAL_RCC_SRAM_IS_CLK_DISABLED()      ((RCC->AHBENR & (RCC_AHBENR_SRAMEN)) == RESET)

	#define __HAL_RCC_FLITF_IS_CLK_ENABLED()       ((RCC->AHBENR & (RCC_AHBENR_FLITFEN)) != RESET)
	#define __HAL_RCC_FLITF_IS_CLK_DISABLED()      ((RCC->AHBENR & (RCC_AHBENR_FLITFEN)) == RESET)

	#define __HAL_RCC_CRC_IS_CLK_ENABLED()       ((RCC->AHBENR & (RCC_AHBENR_CRCEN)) != RESET)
	#define __HAL_RCC_CRC_IS_CLK_DISABLED()      ((RCC->AHBENR & (RCC_AHBENR_CRCEN)) == RESET)
	#pragma endregion


			/** @defgroup RCC_APB1_Force_Release_Reset APB1 Force Release Reset
			  * @brief  Force or release APB1 peripheral reset.
			  * @{
			  */

	#pragma region 强制复位，解除复位
	#define __HAL_RCC_APB1_FORCE_RESET()       (RCC->APB2RSTR = 0xFFFFFFFFU)
	#define __HAL_RCC_TIM2_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST))
	#define __HAL_RCC_TIM3_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_TIM3RST))
	#define __HAL_RCC_WWDG_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_WWDGRST))
	#define __HAL_RCC_USART2_FORCE_RESET()     (RCC->APB1RSTR |= (RCC_APB1RSTR_USART2RST))
	#define __HAL_RCC_I2C1_FORCE_RESET()       (RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST))

	#define __HAL_RCC_BKP_FORCE_RESET()        (RCC->APB1RSTR |= (RCC_APB1RSTR_BKPRST))
	#define __HAL_RCC_PWR_FORCE_RESET()        (RCC->APB1RSTR |= (RCC_APB1RSTR_PWRRST))

	#define __HAL_RCC_APB1_RELEASE_RESET()      (RCC->APB1RSTR = 0x00)
	#define __HAL_RCC_TIM2_RELEASE_RESET()       (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST))
	#define __HAL_RCC_TIM3_RELEASE_RESET()       (RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM3RST))
	#define __HAL_RCC_WWDG_RELEASE_RESET()       (RCC->APB1RSTR &= ~(RCC_APB1RSTR_WWDGRST))
	#define __HAL_RCC_USART2_RELEASE_RESET()     (RCC->APB1RSTR &= ~(RCC_APB1RSTR_USART2RST))
	#define __HAL_RCC_I2C1_RELEASE_RESET()       (RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST))

	#define __HAL_RCC_BKP_RELEASE_RESET()        (RCC->APB1RSTR &= ~(RCC_APB1RSTR_BKPRST))
	#define __HAL_RCC_PWR_RELEASE_RESET()        (RCC->APB1RSTR &= ~(RCC_APB1RSTR_PWRRST))

	#define __HAL_RCC_APB2_FORCE_RESET()       (RCC->APB2RSTR = 0xFFFFFFFFU)
	#define __HAL_RCC_AFIO_FORCE_RESET()       (RCC->APB2RSTR |= (RCC_APB2RSTR_AFIORST))
	#define __HAL_RCC_GPIOA_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_IOPARST))
	#define __HAL_RCC_GPIOB_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_IOPBRST))
	#define __HAL_RCC_GPIOC_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_IOPCRST))
	#define __HAL_RCC_GPIOD_FORCE_RESET()      (RCC->APB2RSTR |= (RCC_APB2RSTR_IOPDRST))
	#define __HAL_RCC_ADC1_FORCE_RESET()       (RCC->APB2RSTR |= (RCC_APB2RSTR_ADC1RST))

	#define __HAL_RCC_TIM1_FORCE_RESET()       (RCC->APB2RSTR |= (RCC_APB2RSTR_TIM1RST))
	#define __HAL_RCC_SPI1_FORCE_RESET()       (RCC->APB2RSTR |= (RCC_APB2RSTR_SPI1RST))
	#define __HAL_RCC_USART1_FORCE_RESET()     (RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST))

	#define __HAL_RCC_APB2_RELEASE_RESET()      (RCC->APB2RSTR = 0x00)
	#define __HAL_RCC_AFIO_RELEASE_RESET()       (RCC->APB2RSTR &= ~(RCC_APB2RSTR_AFIORST))
	#define __HAL_RCC_GPIOA_RELEASE_RESET()      (RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPARST))
	#define __HAL_RCC_GPIOB_RELEASE_RESET()      (RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPBRST))
	#define __HAL_RCC_GPIOC_RELEASE_RESET()      (RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPCRST))
	#define __HAL_RCC_GPIOD_RELEASE_RESET()      (RCC->APB2RSTR &= ~(RCC_APB2RSTR_IOPDRST))
	#define __HAL_RCC_ADC1_RELEASE_RESET()       (RCC->APB2RSTR &= ~(RCC_APB2RSTR_ADC1RST))

	#define __HAL_RCC_TIM1_RELEASE_RESET()       (RCC->APB2RSTR &= ~(RCC_APB2RSTR_TIM1RST))
	#define __HAL_RCC_SPI1_RELEASE_RESET()       (RCC->APB2RSTR &= ~(RCC_APB2RSTR_SPI1RST))
	#define __HAL_RCC_USART1_RELEASE_RESET()     (RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST))
	#pragma endregion


			  /** @defgroup RCC_HSI_Configuration HSI Configuration
				* @{
				*/

				/** @brief  Macros to enable or disable the Internal High Speed oscillator (HSI).
				  * @note   The HSI is stopped by hardware when entering STOP and STANDBY modes.
				  * @note   HSI can not be stopped if it is used as system clock source. In this case,
				  *         you have to select another source of the system clock then stop the HSI.
				  * @note   After enabling the HSI, the application software should wait on HSIRDY
				  *         flag to be set indicating that HSI clock is stable and can be used as
				  *         system clock source.
				  * @note   When the HSI is stopped, HSIRDY flag goes low after 6 HSI oscillator
				  *         clock cycles.
				  */
	#define __HAL_RCC_HSI_ENABLE()  (*(__IO uint32_t *) RCC_CR_HSION_BB = ENABLE)
	#define __HAL_RCC_HSI_DISABLE() (*(__IO uint32_t *) RCC_CR_HSION_BB = DISABLE)

				  /** @brief  Macro to adjust the Internal High Speed oscillator (HSI) calibration value.
					* @note   The calibration is used to compensate for the variations in voltage
					*         and temperature that influence the frequency of the internal HSI RC.
					* @param  _HSICALIBRATIONVALUE_ specifies the calibration trimming value.
					*         (default is RCC_HSICALIBRATION_DEFAULT).
					*         This parameter must be a number between 0 and 0x1F.
					*/
	#define __HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(_HSICALIBRATIONVALUE_) \
		  (MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, (uint32_t)(_HSICALIBRATIONVALUE_) << RCC_CR_HSITRIM_Pos))

					/**
					  * @}
					  */

					  /** @defgroup RCC_LSI_Configuration  LSI Configuration
						* @{
						*/

						/** @brief Macro to enable the Internal Low Speed oscillator (LSI).
						  * @note   After enabling the LSI, the application software should wait on
						  *         LSIRDY flag to be set indicating that LSI clock is stable and can
						  *         be used to clock the IWDG and/or the RTC.
						  */
	#define __HAL_RCC_LSI_ENABLE()  (*(__IO uint32_t *) RCC_CSR_LSION_BB = ENABLE)

						  /** @brief Macro to disable the Internal Low Speed oscillator (LSI).
							* @note   LSI can not be disabled if the IWDG is running.
							* @note   When the LSI is stopped, LSIRDY flag goes low after 6 LSI oscillator
							*         clock cycles.
							*/
	#define __HAL_RCC_LSI_DISABLE() (*(__IO uint32_t *) RCC_CSR_LSION_BB = DISABLE)

							/**
							  * @}
							  */

							  /** @defgroup RCC_HSE_Configuration HSE Configuration
								* @{
								*/

								/**
								  * @brief  Macro to configure the External High Speed oscillator (HSE).
								  * @note   Transition HSE Bypass to HSE On and HSE On to HSE Bypass are not
								  *         supported by this macro. User should request a transition to HSE Off
								  *         first and then HSE On or HSE Bypass.
								  * @note   After enabling the HSE (RCC_HSE_ON or RCC_HSE_Bypass), the application
								  *         software should wait on HSERDY flag to be set indicating that HSE clock
								  *         is stable and can be used to clock the PLL and/or system clock.
								  * @note   HSE state can not be changed if it is used directly or through the
								  *         PLL as system clock. In this case, you have to select another source
								  *         of the system clock then change the HSE state (ex. disable it).
								  * @note   The HSE is stopped by hardware when entering STOP and STANDBY modes.
								  * @note   This function reset the CSSON bit, so if the clock security system(CSS)
								  *         was previously enabled you have to enable it again after calling this
								  *         function.
								  * @param  __STATE__ specifies the new state of the HSE.
								  *          This parameter can be one of the following values:
								  *            @arg @ref RCC_HSE_OFF turn OFF the HSE oscillator, HSERDY flag goes low after
								  *                              6 HSE oscillator clock cycles.
								  *            @arg @ref RCC_HSE_ON turn ON the HSE oscillator
								  *            @arg @ref RCC_HSE_BYPASS HSE oscillator bypassed with external clock
								  */
	#define __HAL_RCC_HSE_CONFIG(__STATE__)                                     \
					do{                                                     \
					  if ((__STATE__) == RCC_HSE_ON)                        \
					  {                                                     \
						SET_BIT(RCC->CR, RCC_CR_HSEON);                     \
					  }                                                     \
					  else if ((__STATE__) == RCC_HSE_OFF)                  \
					  {                                                     \
						CLEAR_BIT(RCC->CR, RCC_CR_HSEON);                   \
						CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                  \
					  }                                                     \
					  else if ((__STATE__) == RCC_HSE_BYPASS)               \
					  {                                                     \
						SET_BIT(RCC->CR, RCC_CR_HSEBYP);                    \
						SET_BIT(RCC->CR, RCC_CR_HSEON);                     \
					  }                                                     \
					  else                                                  \
					  {                                                     \
						CLEAR_BIT(RCC->CR, RCC_CR_HSEON);                   \
						CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                  \
					  }                                                     \
					}while(0U)

								  /**
									* @}
									*/

									/** @defgroup RCC_LSE_Configuration LSE Configuration
									  * @{
									  */

									  /**
										* @brief  Macro to configure the External Low Speed oscillator (LSE).
										* @note Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not supported by this macro.
										* @note   As the LSE is in the Backup domain and write access is denied to
										*         this domain after reset, you have to enable write access using
										*         @ref HAL_PWR_EnableBkUpAccess() function before to configure the LSE
										*         (to be done once after reset).
										* @note   After enabling the LSE (RCC_LSE_ON or RCC_LSE_BYPASS), the application
										*         software should wait on LSERDY flag to be set indicating that LSE clock
										*         is stable and can be used to clock the RTC.
										* @param  __STATE__ specifies the new state of the LSE.
										*         This parameter can be one of the following values:
										*            @arg @ref RCC_LSE_OFF turn OFF the LSE oscillator, LSERDY flag goes low after
										*                              6 LSE oscillator clock cycles.
										*            @arg @ref RCC_LSE_ON turn ON the LSE oscillator.
										*            @arg @ref RCC_LSE_BYPASS LSE oscillator bypassed with external clock.
										*/
	#define __HAL_RCC_LSE_CONFIG(__STATE__)                                     \
					do{                                                     \
					  if ((__STATE__) == RCC_LSE_ON)                        \
					  {                                                     \
						SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                   \
					  }                                                     \
					  else if ((__STATE__) == RCC_LSE_OFF)                  \
					  {                                                     \
						CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);                 \
						CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                \
					  }                                                     \
					  else if ((__STATE__) == RCC_LSE_BYPASS)               \
					  {                                                     \
						SET_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                  \
						SET_BIT(RCC->BDCR, RCC_BDCR_LSEON);                   \
					  }                                                     \
					  else                                                  \
					  {                                                     \
						CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEON);                 \
						CLEAR_BIT(RCC->BDCR, RCC_BDCR_LSEBYP);                \
					  }                                                     \
					}while(0U)

										/**
										  * @}
										  */

										  /** @defgroup RCC_PLL_Configuration PLL Configuration
											* @{
											*/

											/** @brief Macro to enable the main PLL.
											  * @note   After enabling the main PLL, the application software should wait on
											  *         PLLRDY flag to be set indicating that PLL clock is stable and can
											  *         be used as system clock source.
											  * @note   The main PLL is disabled by hardware when entering STOP and STANDBY modes.
											  */
	#define __HAL_RCC_PLL_ENABLE()          (*(__IO uint32_t *) RCC_CR_PLLON_BB = ENABLE)

											  /** @brief Macro to disable the main PLL.
												* @note   The main PLL can not be disabled if it is used as system clock source
												*/
	#define __HAL_RCC_PLL_DISABLE()         (*(__IO uint32_t *) RCC_CR_PLLON_BB = DISABLE)

												/** @brief Macro to configure the main PLL clock source and multiplication factors.
												  * @note   This function must be used only when the main PLL is disabled.
												  *
												  * @param  __RCC_PLLSOURCE__ specifies the PLL entry clock source.
												  *          This parameter can be one of the following values:
												  *            @arg @ref RCC_PLLSOURCE_HSI_DIV2 HSI oscillator clock selected as PLL clock entry
												  *            @arg @ref RCC_PLLSOURCE_HSE HSE oscillator clock selected as PLL clock entry
												  * @param  __PLLMUL__ specifies the multiplication factor for PLL VCO output clock
												  *          This parameter can be one of the following values:
												  *             @arg @ref RCC_PLL_MUL4   PLLVCO = PLL clock entry x 4
												  *             @arg @ref RCC_PLL_MUL6   PLLVCO = PLL clock entry x 6
												  @if STM32F105xC
												  *             @arg @ref RCC_PLL_MUL6_5 PLLVCO = PLL clock entry x 6.5
												  @elseif STM32F107xC
												  *             @arg @ref RCC_PLL_MUL6_5 PLLVCO = PLL clock entry x 6.5
												  @else
												  *             @arg @ref RCC_PLL_MUL2   PLLVCO = PLL clock entry x 2
												  *             @arg @ref RCC_PLL_MUL3   PLLVCO = PLL clock entry x 3
												  *             @arg @ref RCC_PLL_MUL10  PLLVCO = PLL clock entry x 10
												  *             @arg @ref RCC_PLL_MUL11  PLLVCO = PLL clock entry x 11
												  *             @arg @ref RCC_PLL_MUL12  PLLVCO = PLL clock entry x 12
												  *             @arg @ref RCC_PLL_MUL13  PLLVCO = PLL clock entry x 13
												  *             @arg @ref RCC_PLL_MUL14  PLLVCO = PLL clock entry x 14
												  *             @arg @ref RCC_PLL_MUL15  PLLVCO = PLL clock entry x 15
												  *             @arg @ref RCC_PLL_MUL16  PLLVCO = PLL clock entry x 16
												  @endif
												  *             @arg @ref RCC_PLL_MUL8   PLLVCO = PLL clock entry x 8
												  *             @arg @ref RCC_PLL_MUL9   PLLVCO = PLL clock entry x 9
												  *
												  */
	#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSOURCE__, __PLLMUL__)\
		  MODIFY_REG(RCC->CFGR, (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL),((__RCC_PLLSOURCE__) | (__PLLMUL__) ))

												  /** @brief  Get oscillator clock selected as PLL input clock
													* @retval The clock source used for PLL entry. The returned value can be one
													*         of the following:
													*             @arg @ref RCC_PLLSOURCE_HSI_DIV2 HSI oscillator clock selected as PLL input clock
													*             @arg @ref RCC_PLLSOURCE_HSE HSE oscillator clock selected as PLL input clock
													*/
	#define __HAL_RCC_GET_PLL_OSCSOURCE() ((uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC)))

													/**
													  * @}
													  */

													  /** @defgroup RCC_Get_Clock_source Get Clock source
														* @{
														*/

														/**
														  * @brief  Macro to configure the system clock source.
														  * @param  __SYSCLKSOURCE__ specifies the system clock source.
														  *          This parameter can be one of the following values:
														  *              @arg @ref RCC_SYSCLKSOURCE_HSI HSI oscillator is used as system clock source.
														  *              @arg @ref RCC_SYSCLKSOURCE_HSE HSE oscillator is used as system clock source.
														  *              @arg @ref RCC_SYSCLKSOURCE_PLLCLK PLL output is used as system clock source.
														  */
	#define __HAL_RCC_SYSCLK_CONFIG(__SYSCLKSOURCE__) \
				  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__SYSCLKSOURCE__))

														  /** @brief  Macro to get the clock source used as system clock.
															* @retval The clock source used as system clock. The returned value can be one
															*         of the following:
															*             @arg @ref RCC_SYSCLKSOURCE_STATUS_HSI HSI used as system clock
															*             @arg @ref RCC_SYSCLKSOURCE_STATUS_HSE HSE used as system clock
															*             @arg @ref RCC_SYSCLKSOURCE_STATUS_PLLCLK PLL used as system clock
															*/
	#define __HAL_RCC_GET_SYSCLK_SOURCE() ((uint32_t)(READ_BIT(RCC->CFGR,RCC_CFGR_SWS)))

															/**
															  * @}
															  */

															  /** @defgroup RCCEx_MCOx_Clock_Config RCC Extended MCOx Clock Config
																* @{
																*/

	#if   defined(RCC_CFGR_MCO_3)
																/** @brief  Macro to configure the MCO clock.
																  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
																  *         This parameter can be one of the following values:
																  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK      No clock selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_SYSCLK       System clock (SYSCLK) selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_HSI          HSI selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_HSE          HSE selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_PLLCLK       PLL clock divided by 2 selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_PLL2CLK      PLL2 clock selected by 2 selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_PLL3CLK_DIV2 PLL3 clock divided by 2 selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_EXT_HSE XT1  external 3-25 MHz oscillator clock selected (for Ethernet) as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_PLL3CLK      PLL3 clock selected (for Ethernet) as MCO clock
																  * @param  __MCODIV__ specifies the MCO clock prescaler.
																  *         This parameter can be one of the following values:
																  *            @arg @ref RCC_MCODIV_1 No division applied on MCO clock source
																  */
	#else
																/** @brief  Macro to configure the MCO clock.
																  * @param  __MCOCLKSOURCE__ specifies the MCO clock source.
																  *         This parameter can be one of the following values:
																  *            @arg @ref RCC_MCO1SOURCE_NOCLOCK No clock selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_SYSCLK  System clock (SYSCLK) selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_HSI HSI selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_HSE HSE selected as MCO clock
																  *            @arg @ref RCC_MCO1SOURCE_PLLCLK  PLL clock divided by 2 selected as MCO clock
																  * @param  __MCODIV__ specifies the MCO clock prescaler.
																  *         This parameter can be one of the following values:
																  *            @arg @ref RCC_MCODIV_1 No division applied on MCO clock source
																  */
	#endif

	#define __HAL_RCC_MCO1_CONFIG(__MCOCLKSOURCE__, __MCODIV__) \
				 MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, (__MCOCLKSOURCE__))


																  /**
																	* @}
																	*/

																	/** @defgroup RCC_RTC_Clock_Configuration RCC RTC Clock Configuration
																	* @{
																	*/

																	/** @brief Macro to configure the RTC clock (RTCCLK).
																	  * @note   As the RTC clock configuration bits are in the Backup domain and write
																	  *         access is denied to this domain after reset, you have to enable write
																	  *         access using the Power Backup Access macro before to configure
																	  *         the RTC clock source (to be done once after reset).
																	  * @note   Once the RTC clock is configured it can't be changed unless the
																	  *         Backup domain is reset using @ref __HAL_RCC_BACKUPRESET_FORCE() macro, or by
																	  *         a Power On Reset (POR).
																	  *
																	  * @param  __RTC_CLKSOURCE__ specifies the RTC clock source.
																	  *          This parameter can be one of the following values:
																	  *             @arg @ref RCC_RTCCLKSOURCE_NO_CLK No clock selected as RTC clock
																	  *             @arg @ref RCC_RTCCLKSOURCE_LSE LSE selected as RTC clock
																	  *             @arg @ref RCC_RTCCLKSOURCE_LSI LSI selected as RTC clock
																	  *             @arg @ref RCC_RTCCLKSOURCE_HSE_DIV128 HSE divided by 128 selected as RTC clock
																	  * @note   If the LSE or LSI is used as RTC clock source, the RTC continues to
																	  *         work in STOP and STANDBY modes, and can be used as wakeup source.
																	  *         However, when the HSE clock is used as RTC clock source, the RTC
																	  *         cannot be used in STOP and STANDBY modes.
																	  * @note   The maximum input clock frequency for RTC is 1MHz (when using HSE as
																	  *         RTC clock source).
																	  */
	#define __HAL_RCC_RTC_CONFIG(__RTC_CLKSOURCE__) MODIFY_REG(RCC->BDCR, RCC_BDCR_RTCSEL, (__RTC_CLKSOURCE__))

																	  /** @brief Macro to get the RTC clock source.
																		* @retval The clock source can be one of the following values:
																		*            @arg @ref RCC_RTCCLKSOURCE_NO_CLK No clock selected as RTC clock
																		*            @arg @ref RCC_RTCCLKSOURCE_LSE LSE selected as RTC clock
																		*            @arg @ref RCC_RTCCLKSOURCE_LSI LSI selected as RTC clock
																		*            @arg @ref RCC_RTCCLKSOURCE_HSE_DIV128 HSE divided by 128 selected as RTC clock
																		*/
	#define __HAL_RCC_GET_RTC_SOURCE() (READ_BIT(RCC->BDCR, RCC_BDCR_RTCSEL))

																		/** @brief Macro to enable the the RTC clock.
																		  * @note   These macros must be used only after the RTC clock source was selected.
																		  */
	#define __HAL_RCC_RTC_ENABLE()          (*(__IO uint32_t *) RCC_BDCR_RTCEN_BB = ENABLE)

																		  /** @brief Macro to disable the the RTC clock.
																			* @note  These macros must be used only after the RTC clock source was selected.
																			*/
	#define __HAL_RCC_RTC_DISABLE()         (*(__IO uint32_t *) RCC_BDCR_RTCEN_BB = DISABLE)

																			/** @brief  Macro to force the Backup domain reset.
																			  * @note   This function resets the RTC peripheral (including the backup registers)
																			  *         and the RTC clock source selection in RCC_BDCR register.
																			  */
	#define __HAL_RCC_BACKUPRESET_FORCE()   (*(__IO uint32_t *) RCC_BDCR_BDRST_BB = ENABLE)

																			  /** @brief  Macros to release the Backup domain reset.
																				*/
	#define __HAL_RCC_BACKUPRESET_RELEASE() (*(__IO uint32_t *) RCC_BDCR_BDRST_BB = DISABLE)

																				/**
																				  * @}
																				  */

																				  /** @defgroup RCC_Flags_Interrupts_Management Flags Interrupts Management
																					* @brief macros to manage the specified RCC Flags and interrupts.
																					* @{
																					*/

																					/** @brief Enable RCC interrupt.
																					  * @param  __INTERRUPT__ specifies the RCC interrupt sources to be enabled.
																					  *          This parameter can be any combination of the following values:
																					  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
																					  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt
																					  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
																					  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt
																					  *            @arg @ref RCC_IT_PLLRDY main PLL ready interrupt
																					  @if STM32F105xx
																					  *            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																					  *            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																					  @elsif STM32F107xx
																					  *            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																					  *            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																					  @endif
																					  */
	#define __HAL_RCC_ENABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE1_ADDRESS |= (__INTERRUPT__))

																					  /** @brief Disable RCC interrupt.
																						* @param  __INTERRUPT__ specifies the RCC interrupt sources to be disabled.
																						*          This parameter can be any combination of the following values:
																						*            @arg @ref RCC_IT_LSIRDY LSI ready interrupt
																						*            @arg @ref RCC_IT_LSERDY LSE ready interrupt
																						*            @arg @ref RCC_IT_HSIRDY HSI ready interrupt
																						*            @arg @ref RCC_IT_HSERDY HSE ready interrupt
																						*            @arg @ref RCC_IT_PLLRDY main PLL ready interrupt
																						@if STM32F105xx
																						*            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																						*            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																						@elsif STM32F107xx
																						*            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																						*            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																						@endif
																						*/
	#define __HAL_RCC_DISABLE_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE1_ADDRESS &= (uint8_t)(~(__INTERRUPT__)))

																						/** @brief Clear the RCC's interrupt pending bits.
																						  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
																						  *          This parameter can be any combination of the following values:
																						  *            @arg @ref RCC_IT_LSIRDY LSI ready interrupt.
																						  *            @arg @ref RCC_IT_LSERDY LSE ready interrupt.
																						  *            @arg @ref RCC_IT_HSIRDY HSI ready interrupt.
																						  *            @arg @ref RCC_IT_HSERDY HSE ready interrupt.
																						  *            @arg @ref RCC_IT_PLLRDY Main PLL ready interrupt.
																						  @if STM32F105xx
																						  *            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																						  *            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																						  @elsif STM32F107xx
																						  *            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																						  *            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																						  @endif
																						  *            @arg @ref RCC_IT_CSS Clock Security System interrupt
																						  */
	#define __HAL_RCC_CLEAR_IT(__INTERRUPT__) (*(__IO uint8_t *) RCC_CIR_BYTE2_ADDRESS = (__INTERRUPT__))

																						  /** @brief Check the RCC's interrupt has occurred or not.
																							* @param  __INTERRUPT__ specifies the RCC interrupt source to check.
																							*          This parameter can be one of the following values:
																							*            @arg @ref RCC_IT_LSIRDY LSI ready interrupt.
																							*            @arg @ref RCC_IT_LSERDY LSE ready interrupt.
																							*            @arg @ref RCC_IT_HSIRDY HSI ready interrupt.
																							*            @arg @ref RCC_IT_HSERDY HSE ready interrupt.
																							*            @arg @ref RCC_IT_PLLRDY Main PLL ready interrupt.
																							@if STM32F105xx
																							*            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																							*            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																							@elsif STM32F107xx
																							*            @arg @ref RCC_IT_PLL2RDY Main PLL2 ready interrupt.
																							*            @arg @ref RCC_IT_PLLI2S2RDY Main PLLI2S ready interrupt.
																							@endif
																							*            @arg @ref RCC_IT_CSS Clock Security System interrupt
																							* @retval The new state of __INTERRUPT__ (TRUE or FALSE).
																							*/
	#define __HAL_RCC_GET_IT(__INTERRUPT__) ((RCC->CIR & (__INTERRUPT__)) == (__INTERRUPT__))

																							/** @brief Set RMVF bit to clear the reset flags.
																							  *         The reset flags are RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
																							  *         RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
																							  */
	#define __HAL_RCC_CLEAR_RESET_FLAGS() (*(__IO uint32_t *)RCC_CSR_RMVF_BB = ENABLE)

																							  /** @brief  Check RCC flag is set or not.
																								* @param  __FLAG__ specifies the flag to check.
																								*          This parameter can be one of the following values:
																								*            @arg @ref RCC_FLAG_HSIRDY HSI oscillator clock ready.
																								*            @arg @ref RCC_FLAG_HSERDY HSE oscillator clock ready.
																								*            @arg @ref RCC_FLAG_PLLRDY Main PLL clock ready.
																								@if STM32F105xx
																								*            @arg @ref RCC_FLAG_PLL2RDY Main PLL2 clock ready.
																								*            @arg @ref RCC_FLAG_PLLI2SRDY Main PLLI2S clock ready.
																								@elsif STM32F107xx
																								*            @arg @ref RCC_FLAG_PLL2RDY Main PLL2 clock ready.
																								*            @arg @ref RCC_FLAG_PLLI2SRDY Main PLLI2S clock ready.
																								@endif
																								*            @arg @ref RCC_FLAG_LSERDY LSE oscillator clock ready.
																								*            @arg @ref RCC_FLAG_LSIRDY LSI oscillator clock ready.
																								*            @arg @ref RCC_FLAG_PINRST  Pin reset.
																								*            @arg @ref RCC_FLAG_PORRST  POR/PDR reset.
																								*            @arg @ref RCC_FLAG_SFTRST  Software reset.
																								*            @arg @ref RCC_FLAG_IWDGRST Independent Watchdog reset.
																								*            @arg @ref RCC_FLAG_WWDGRST Window Watchdog reset.
																								*            @arg @ref RCC_FLAG_LPWRRST Low Power reset.
																								* @retval The new state of __FLAG__ (TRUE or FALSE).
																								*/
	#define __HAL_RCC_GET_FLAG(__FLAG__) (((((__FLAG__) >> 5U) == CR_REG_INDEX)?   RCC->CR   : \
									  ((((__FLAG__) >> 5U) == BDCR_REG_INDEX)? RCC->BDCR : \
																			  RCC->CSR)) & (1U << ((__FLAG__) & RCC_FLAG_MASK)))

																								/**
																								  * @}
																								  */

																								  /**
																									* @}
																									*/

																									/* Include RCC HAL Extension module */
	#include "stm32f1xx_hal_rcc_ex.h"

	/* Exported functions --------------------------------------------------------*/
	/** @addtogroup RCC_Exported_Functions
	  * @{
	  */

	  /** @addtogroup RCC_Exported_Functions_Group1
		* @{
		*/

	HAL_StatusTypeDef HAL_RCC_DeInit(void);

	/// <summary>
	///		根据指定的参数初始化RCC振荡器。
	/// 
	///		* 当PLL（相位锁定环）被用作系统时钟时，不会被禁用。
	///		* 当USB OTG FS（通用串行总线外设）时钟启用时，PLL不会被禁用（特定于带有USB FS的设备）。
	///		* 不支持LSE Bypass（低速外部振荡器旁路）到LSE On（低速外部振荡器开启）以及LSE On到LSE Bypass的转换。
	///		  用户应先请求转换到LSE Off（低速外部振荡器关闭）然后再转换到LSE On或LSE Bypass。
	///		* 不支持HSE Bypass（高速外部振荡器旁路）到HSE On（高速外部振荡器开启）以及HSE On到HSE Bypass的转换。
	///		  用户应先请求转换到HSE Off（高速外部振荡器关闭）然后再转换到HSE On或HSE Bypass。
	/// </summary>
	/// <param name="RCC_OscInitStruct">
	///		指向一个RCC_OscInitTypeDef结构体的指针，该结构体包含了RCC振荡器的配置信息。
	/// </param>
	/// <returns>HAL状态</returns>
	HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);


	/// <summary>
	///		根据在 RCC_ClkInitStruct 中指定的参数初始化CPU、AHB和APB总线时钟。
	/// </summary>
	/// 
	/// <note>
	///		SystemCoreClock CMSIS 变量用于存储系统时钟频率并通过在此函数中调用的
	///		HAL_RCC_GetHCLKFreq() 函数中更新。
	/// </note>
	/// 
	/// <note>
	///		在从重置启动后、从 STOP 和 STANDBY 模式唤醒，或者在使用 HSE
	///		作为系统时钟的直接或间接失败情况下（如果启用了时钟安全系统CSS），
	///		HSI 将会被用作（由硬件启用的）系统时钟源。
	/// </note>
	/// 
	/// <note>
	///		仅当目标时钟源准备就绪（启动延迟后时钟稳定或PLL锁定）时，
	///		才会从一个时钟源切换到另一个时钟源。
	///		如果选择了一个尚未准备好的时钟源，当时钟源准备就绪时，切换将发生。
	///		您可以使用 HAL_RCC_GetClockConfig() 函数来知道哪个时钟当前被用作系统时钟源。
	/// </note>
	/// 
	/// <param name="RCC_ClkInitStruct">指向一个RCC_OscInitTypeDef 结构的指针，该结构包含 RCC 外设的配置信息。</param>
	/// <param name="FLatency">FLASH延迟</param>
	/// 
	/// <returns>HAL状态</returns>
	HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

	/**
	  * @}
	  */

	  /** @addtogroup RCC_Exported_Functions_Group2
		* @{
		*/

		/* Peripheral Control functions  ************************************************/
	void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
	void              HAL_RCC_EnableCSS(void);
	void              HAL_RCC_DisableCSS(void);
	uint32_t          HAL_RCC_GetSysClockFreq(void);
	uint32_t          HAL_RCC_GetHCLKFreq(void);
	uint32_t          HAL_RCC_GetPCLK1Freq(void);
	uint32_t          HAL_RCC_GetPCLK2Freq(void);
	void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
	void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);

	/* CSS NMI IRQ handler */
	void              HAL_RCC_NMI_IRQHandler(void);

	/* User Callbacks in non blocking mode (IT mode) */
	void              HAL_RCC_CSSCallback(void);

	/**
	  * @}
	  */

	  /**
		* @}
		*/

		/** @addtogroup RCC_Private_Constants
		  * @{
		  */

		  /** @defgroup RCC_Timeout RCC Timeout
			* @{
			*/

			/* Disable Backup domain write protection state change timeout */
	#define RCC_DBP_TIMEOUT_VALUE          100U    /* 100 ms */
	/* LSE state change timeout */
	#define RCC_LSE_TIMEOUT_VALUE          LSE_STARTUP_TIMEOUT
	#define CLOCKSWITCH_TIMEOUT_VALUE      5000    /* 5 s    */
	#define HSE_TIMEOUT_VALUE              HSE_STARTUP_TIMEOUT
	#define HSI_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
	#define LSI_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */
	#define PLL_TIMEOUT_VALUE              2U      /* 2 ms (minimum Tick + 1) */

	/**
	  * @}
	  */

	  /** @defgroup RCC_Register_Offset Register offsets
		* @{
		*/
	#define RCC_OFFSET                (RCC_BASE - PERIPH_BASE)
	#define RCC_CR_OFFSET             0x00U
	#define RCC_CFGR_OFFSET           0x04U
	#define RCC_CIR_OFFSET            0x08U
	#define RCC_BDCR_OFFSET           0x20U
	#define RCC_CSR_OFFSET            0x24U

		/**
		  * @}
		  */

		  /** @defgroup RCC_BitAddress_AliasRegion BitAddress AliasRegion
			* @brief RCC registers bit address in the alias region
			* @{
			*/
	#define RCC_CR_OFFSET_BB          (RCC_OFFSET + RCC_CR_OFFSET)
	#define RCC_CFGR_OFFSET_BB        (RCC_OFFSET + RCC_CFGR_OFFSET)
	#define RCC_CIR_OFFSET_BB         (RCC_OFFSET + RCC_CIR_OFFSET)
	#define RCC_BDCR_OFFSET_BB        (RCC_OFFSET + RCC_BDCR_OFFSET)
	#define RCC_CSR_OFFSET_BB         (RCC_OFFSET + RCC_CSR_OFFSET)

			/* --- CR Register ---*/
			/* Alias word address of HSION bit */
	#define RCC_HSION_BIT_NUMBER      RCC_CR_HSION_Pos
	#define RCC_CR_HSION_BB           ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32U) + (RCC_HSION_BIT_NUMBER * 4U)))
	/* Alias word address of HSEON bit */
	#define RCC_HSEON_BIT_NUMBER      RCC_CR_HSEON_Pos
	#define RCC_CR_HSEON_BB           ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32U) + (RCC_HSEON_BIT_NUMBER * 4U)))
	/* Alias word address of CSSON bit */
	#define RCC_CSSON_BIT_NUMBER      RCC_CR_CSSON_Pos
	#define RCC_CR_CSSON_BB           ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32U) + (RCC_CSSON_BIT_NUMBER * 4U)))
	/* Alias word address of PLLON bit */
	#define RCC_PLLON_BIT_NUMBER      RCC_CR_PLLON_Pos
	#define RCC_CR_PLLON_BB           ((uint32_t)(PERIPH_BB_BASE + (RCC_CR_OFFSET_BB * 32U) + (RCC_PLLON_BIT_NUMBER * 4U)))

	/* --- CSR Register ---*/
	/* Alias word address of LSION bit */
	#define RCC_LSION_BIT_NUMBER      RCC_CSR_LSION_Pos
	#define RCC_CSR_LSION_BB          ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32U) + (RCC_LSION_BIT_NUMBER * 4U)))

	/* Alias word address of RMVF bit */
	#define RCC_RMVF_BIT_NUMBER       RCC_CSR_RMVF_Pos
	#define RCC_CSR_RMVF_BB           ((uint32_t)(PERIPH_BB_BASE + (RCC_CSR_OFFSET_BB * 32U) + (RCC_RMVF_BIT_NUMBER * 4U)))

	/* --- BDCR Registers ---*/
	/* Alias word address of LSEON bit */
	#define RCC_LSEON_BIT_NUMBER      RCC_BDCR_LSEON_Pos
	#define RCC_BDCR_LSEON_BB          ((uint32_t)(PERIPH_BB_BASE + (RCC_BDCR_OFFSET_BB * 32U) + (RCC_LSEON_BIT_NUMBER * 4U)))

	/* Alias word address of LSEON bit */
	#define RCC_LSEBYP_BIT_NUMBER     RCC_BDCR_LSEBYP_Pos
	#define RCC_BDCR_LSEBYP_BB         ((uint32_t)(PERIPH_BB_BASE + (RCC_BDCR_OFFSET_BB * 32U) + (RCC_LSEBYP_BIT_NUMBER * 4U)))

	/* Alias word address of RTCEN bit */
	#define RCC_RTCEN_BIT_NUMBER      RCC_BDCR_RTCEN_Pos
	#define RCC_BDCR_RTCEN_BB          ((uint32_t)(PERIPH_BB_BASE + (RCC_BDCR_OFFSET_BB * 32U) + (RCC_RTCEN_BIT_NUMBER * 4U)))

	/* Alias word address of BDRST bit */
	#define RCC_BDRST_BIT_NUMBER      RCC_BDCR_BDRST_Pos
	#define RCC_BDCR_BDRST_BB         ((uint32_t)(PERIPH_BB_BASE + (RCC_BDCR_OFFSET_BB * 32U) + (RCC_BDRST_BIT_NUMBER * 4U)))

	/**
	  * @}
	  */

	  /* CR register byte 2 (Bits[23:16]) base address */
	#define RCC_CR_BYTE2_ADDRESS          ((uint32_t)(RCC_BASE + RCC_CR_OFFSET + 0x02U))

	/* CIR register byte 1 (Bits[15:8]) base address */
	#define RCC_CIR_BYTE1_ADDRESS     ((uint32_t)(RCC_BASE + RCC_CIR_OFFSET + 0x01U))

	/* CIR register byte 2 (Bits[23:16]) base address */
	#define RCC_CIR_BYTE2_ADDRESS     ((uint32_t)(RCC_BASE + RCC_CIR_OFFSET + 0x02U))

	/* Defines used for Flags */
	#define CR_REG_INDEX                     ((uint8_t)1)
	#define BDCR_REG_INDEX                   ((uint8_t)2)
	#define CSR_REG_INDEX                    ((uint8_t)3)

	#define RCC_FLAG_MASK                    ((uint8_t)0x1F)

	/**
	  * @}
	  */

	  /** @addtogroup RCC_Private_Macros
		* @{
		*/
		/** @defgroup RCC_Alias_For_Legacy Alias define maintained for legacy
		  * @{
		  */
	#define __HAL_RCC_SYSCFG_CLK_DISABLE    __HAL_RCC_AFIO_CLK_DISABLE
	#define __HAL_RCC_SYSCFG_CLK_ENABLE     __HAL_RCC_AFIO_CLK_ENABLE
	#define __HAL_RCC_SYSCFG_FORCE_RESET    __HAL_RCC_AFIO_FORCE_RESET
	#define __HAL_RCC_SYSCFG_RELEASE_RESET  __HAL_RCC_AFIO_RELEASE_RESET
		  /**
			* @}
			*/

	#define IS_RCC_PLLSOURCE(__SOURCE__) (((__SOURCE__) == RCC_PLLSOURCE_HSI_DIV2) || \
									  ((__SOURCE__) == RCC_PLLSOURCE_HSE))
	#define IS_RCC_OSCILLATORTYPE(__OSCILLATOR__) (((__OSCILLATOR__) == RCC_OSCILLATORTYPE_NONE)                           || \
											   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSE) == RCC_OSCILLATORTYPE_HSE) || \
											   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_HSI) == RCC_OSCILLATORTYPE_HSI) || \
											   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSI) == RCC_OSCILLATORTYPE_LSI) || \
											   (((__OSCILLATOR__) & RCC_OSCILLATORTYPE_LSE) == RCC_OSCILLATORTYPE_LSE))
	#define IS_RCC_HSE(__HSE__) (((__HSE__) == RCC_HSE_OFF) || ((__HSE__) == RCC_HSE_ON) || \
							 ((__HSE__) == RCC_HSE_BYPASS))
	#define IS_RCC_LSE(__LSE__) (((__LSE__) == RCC_LSE_OFF) || ((__LSE__) == RCC_LSE_ON) || \
							 ((__LSE__) == RCC_LSE_BYPASS))
	#define IS_RCC_HSI(__HSI__) (((__HSI__) == RCC_HSI_OFF) || ((__HSI__) == RCC_HSI_ON))
	#define IS_RCC_CALIBRATION_VALUE(__VALUE__) ((__VALUE__) <= 0x1FU)
	#define IS_RCC_LSI(__LSI__) (((__LSI__) == RCC_LSI_OFF) || ((__LSI__) == RCC_LSI_ON))
	#define IS_RCC_PLL(__PLL__) (((__PLL__) == RCC_PLL_NONE) || ((__PLL__) == RCC_PLL_OFF) || \
							 ((__PLL__) == RCC_PLL_ON))

	#define IS_RCC_CLOCKTYPE(CLK) ((((CLK) & RCC_CLOCKTYPE_SYSCLK) == RCC_CLOCKTYPE_SYSCLK) || \
							   (((CLK) & RCC_CLOCKTYPE_HCLK)   == RCC_CLOCKTYPE_HCLK)   || \
							   (((CLK) & RCC_CLOCKTYPE_PCLK1)  == RCC_CLOCKTYPE_PCLK1)  || \
							   (((CLK) & RCC_CLOCKTYPE_PCLK2)  == RCC_CLOCKTYPE_PCLK2))
	#define IS_RCC_SYSCLKSOURCE(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_HSI) || \
										 ((__SOURCE__) == RCC_SYSCLKSOURCE_HSE) || \
										 ((__SOURCE__) == RCC_SYSCLKSOURCE_PLLCLK))
	#define IS_RCC_SYSCLKSOURCE_STATUS(__SOURCE__) (((__SOURCE__) == RCC_SYSCLKSOURCE_STATUS_HSI) || \
												((__SOURCE__) == RCC_SYSCLKSOURCE_STATUS_HSE) || \
												((__SOURCE__) == RCC_SYSCLKSOURCE_STATUS_PLLCLK))
	#define IS_RCC_HCLK(__HCLK__) (((__HCLK__) == RCC_SYSCLK_DIV1) || ((__HCLK__) == RCC_SYSCLK_DIV2) || \
							   ((__HCLK__) == RCC_SYSCLK_DIV4) || ((__HCLK__) == RCC_SYSCLK_DIV8) || \
							   ((__HCLK__) == RCC_SYSCLK_DIV16) || ((__HCLK__) == RCC_SYSCLK_DIV64) || \
							   ((__HCLK__) == RCC_SYSCLK_DIV128) || ((__HCLK__) == RCC_SYSCLK_DIV256) || \
							   ((__HCLK__) == RCC_SYSCLK_DIV512))
	#define IS_RCC_PCLK(__PCLK__) (((__PCLK__) == RCC_HCLK_DIV1) || ((__PCLK__) == RCC_HCLK_DIV2) || \
							   ((__PCLK__) == RCC_HCLK_DIV4) || ((__PCLK__) == RCC_HCLK_DIV8) || \
							   ((__PCLK__) == RCC_HCLK_DIV16))
	#define IS_RCC_MCO(__MCO__)  ((__MCO__) == RCC_MCO)
	#define IS_RCC_MCODIV(__DIV__) (((__DIV__) == RCC_MCODIV_1))
	#define IS_RCC_RTCCLKSOURCE(__SOURCE__)  (((__SOURCE__) == RCC_RTCCLKSOURCE_NO_CLK) || \
										  ((__SOURCE__) == RCC_RTCCLKSOURCE_LSE) || \
										  ((__SOURCE__) == RCC_RTCCLKSOURCE_LSI) || \
										  ((__SOURCE__) == RCC_RTCCLKSOURCE_HSE_DIV128))

	#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_HAL_RCC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

