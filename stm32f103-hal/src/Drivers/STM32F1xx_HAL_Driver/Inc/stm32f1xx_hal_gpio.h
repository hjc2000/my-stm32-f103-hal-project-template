#ifndef STM32F1xx_HAL_GPIO_H
#define STM32F1xx_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
	#endif

	#include "stm32f1xx_hal_def.h"


	/// <summary>
	///     用于 GPIO 引脚初始化
	/// </summary>
	typedef struct
	{
		/// <summary>
		///		选择引脚。
		///		可选值为 GPIO_pins_define 中的一个。
		///		例如：
		///			GPIO_PIN_0
		///			GPIO_PIN_1
		/// </summary>
		uint32_t Pin;

		/// <summary>
		///		引脚模式选择。
		///		可选值为 GPIO_mode_define 中的一个。
		/// </summary>
		uint32_t Mode;

		/// <summary>
		///		引脚上拉下拉模式选择。
		///		可选值为 GPIO_pull_define 中的一个。
		/// </summary>
		uint32_t Pull;

		/// <summary>
		///		引脚速度选择。
		///		可选值为 GPIO_speed_define 中的一个。
		/// </summary>
		uint32_t Speed;
	} GPIO_InitTypeDef;


	/// <summary>
	///		GPIO 置位复位枚举量。
	/// </summary>
	typedef enum
	{
		GPIO_PIN_RESET = 0u,
		GPIO_PIN_SET
	} GPIO_PinState;

	#pragma region GPIO_pins_define
	#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
	#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
	#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
	#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
	#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
	#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
	#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
	#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
	#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
	#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
	#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
	#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
	#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
	#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
	#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
	#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
	#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

	#define GPIO_PIN_MASK              0x0000FFFFu /* PIN mask for assert test */
	#pragma endregion


	#pragma region GPIO_mode_define
	/** @defgroup GPIO_mode_define GPIO mode define
	*	@brief GPIO Configuration Mode
	*        Elements values convention: 0xX0yz00YZ
	*           - X  : GPIO mode or EXTI Mode
	*           - y  : External IT or Event trigger detection
	*           - z  : IO configuration on External IT or Event
	*           - Y  : Output type (Push Pull or Open Drain)
	*           - Z  : IO Direction mode (Input, Output, Alternate or Analog)
	* @{
	*/

	// 浮空输入模式
	#define  GPIO_MODE_INPUT                        0x00000000u
	// 推挽输出模式
	#define  GPIO_MODE_OUTPUT_PP                    0x00000001u
	// 开漏输出模式
	#define  GPIO_MODE_OUTPUT_OD                    0x00000011u
	#define  GPIO_MODE_AF_PP                        0x00000002u   /*!< Alternate Function Push Pull Mode     */
	#define  GPIO_MODE_AF_OD                        0x00000012u   /*!< Alternate Function Open Drain Mode    */
	#define  GPIO_MODE_AF_INPUT                     GPIO_MODE_INPUT          /*!< Alternate Function Input Mode         */

	#define  GPIO_MODE_ANALOG                       0x00000003u   /*!< Analog Mode  */

	#define  GPIO_MODE_IT_RISING                    0x10110000u   /*!< External Interrupt Mode with Rising edge trigger detection          */
	#define  GPIO_MODE_IT_FALLING                   0x10210000u   /*!< External Interrupt Mode with Falling edge trigger detection         */
	#define  GPIO_MODE_IT_RISING_FALLING            0x10310000u   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

	#define  GPIO_MODE_EVT_RISING                   0x10120000u   /*!< External Event Mode with Rising edge trigger detection               */
	#define  GPIO_MODE_EVT_FALLING                  0x10220000u   /*!< External Event Mode with Falling edge trigger detection              */
	#define  GPIO_MODE_EVT_RISING_FALLING           0x10320000u   /*!< External Event Mode with Rising/Falling edge trigger detection       */
	#pragma endregion


	#pragma region GPIO 速度宏定义
	#define  GPIO_SPEED_FREQ_LOW              (GPIO_CRL_MODE0_1) /*!< Low speed */
	#define  GPIO_SPEED_FREQ_MEDIUM           (GPIO_CRL_MODE0_0) /*!< Medium speed */
	#define  GPIO_SPEED_FREQ_HIGH             (GPIO_CRL_MODE0)   /*!< High speed */
	#pragma endregion


	#pragma region 上下拉宏定义
	// 不上拉也不下拉。悬空。
	#define  GPIO_NOPULL        0x00000000u
	// 上拉
	#define  GPIO_PULLUP        0x00000001u
	// 下拉
	#define  GPIO_PULLDOWN      0x00000002u
	#pragma endregion



	/* Exported macro ------------------------------------------------------------*/
	/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
	  * @{
	*/

	/**
	  * @brief  Checks whether the specified EXTI line flag is set or not.
	  * @param  __EXTI_LINE__: specifies the EXTI line flag to check.
	  *         This parameter can be GPIO_PIN_x where x can be(0..15)
	  * @retval The new state of __EXTI_LINE__ (SET or RESET).
	  */
	#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

	  /**
		* @brief  Clears the EXTI's line pending flags.
		* @param  __EXTI_LINE__: specifies the EXTI lines flags to clear.
		*         This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
		* @retval None
		*/
	#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

		/**
		  * @brief  Checks whether the specified EXTI line is asserted or not.
		  * @param  __EXTI_LINE__: specifies the EXTI line to check.
		  *          This parameter can be GPIO_PIN_x where x can be(0..15)
		  * @retval The new state of __EXTI_LINE__ (SET or RESET).
		  */
	#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

		  /**
			* @brief  Clears the EXTI's line pending bits.
			* @param  __EXTI_LINE__: specifies the EXTI lines to clear.
			*          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
			* @retval None
			*/
	#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

			/**
			  * @brief  Generates a Software interrupt on selected EXTI line.
			  * @param  __EXTI_LINE__: specifies the EXTI line to check.
			  *          This parameter can be GPIO_PIN_x where x can be(0..15)
			  * @retval None
			  */
	#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))
			  /**
				* @}
				*/

				/* Include GPIO HAL Extension module */
	#include "stm32f1xx_hal_gpio_ex.h"

	/// <summary>
	///		初始化 GPIO
	/// </summary>
	/// 
	/// <param name="GPIOx">
	///		GPIO 组的宏定义。
	///		例如：
	///			#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
	///			#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
	///			#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
	///			#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)
	///			#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
	///			#define GPIOF   ((GPIO_TypeDef *)GPIOF_BASE)
	///			#define GPIOG   ((GPIO_TypeDef *)GPIOG_BASE)
	/// 
	///		范围就是从 GPIOA 到 GPIOG
	/// 
	///		原理就是将 GPIO 寄存器的内存布局定义为结构体 GPIO_TypeDef，然后将各个 GPIO
	///		组的寄存器基地址强制转换为 GPIO_TypeDef 指针，这样就可以通过 GPIO_TypeDef
	///		的实例对象来操作 GPIO 寄存器了。
	/// </param>
	/// 
	/// <param name="GPIO_Init"></param>
	void  HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);

	/// <summary>
	///		反初始化 GPIO。反初始化后，GPIO 寄存器的值等于复位后的初始状态。
	/// </summary>
	/// <param name="GPIOx">
	///		GPIO 组的宏定义。
	///		例如：
	///			#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
	///			#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
	///			#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
	///			#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)
	///			#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
	///			#define GPIOF   ((GPIO_TypeDef *)GPIOF_BASE)
	///			#define GPIOG   ((GPIO_TypeDef *)GPIOG_BASE)
	/// 
	///		范围就是从 GPIOA 到 GPIOG
	/// </param>
	/// <param name="GPIO_Pin">同 HAL_GPIO_Init 函数。详见 HAL_GPIO_Init 函数的注释。</param>
	void  HAL_GPIO_DeInit(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

	/** @addtogroup GPIO_Exported_Functions_Group2
		* @{
	*/

	/* IO operation functions *****************************************************/
	GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

	/// <summary>
	///		写引脚。可以置位或复位。内部利用 BSRR 寄存器。
	/// 
	///		利用 BSRR 寄存器的好处是置位、复位指定位的操作是原子的。如果直接从通过写输出寄存器
	///		来置位、复位某些位，一般的操作过程是：
	///		
	///		置位：
	///			读出输出寄存器
	///			构造一个要被置位的位为 1，其余位为 0 的掩码，
	///			将读出来的输出寄存器的值与这个掩码进行 |= 运算
	///		
	///		然而，当你读出输出寄存器的值以后，输出寄存器可能在中断中或别的线程中又被置位了 1 个
	///		位，然而你已经提前读出输出寄存器的值了，所以你读出的结果里，这个位仍然是 0. 等到你将
	///		读出的结果与位掩码进行 |= 运算，将结果写入输出寄存器的时候，另一个线程置位的操作被你给
	///		撤销了。
	/// 
	///		本函数利用 BSRR 寄存器，可以不用担心上述的线程问题，BSRR 的操作是原子的。
	/// </summary>
	/// <param name="GPIOx">
	///		GPIO 组的宏定义。
	///		例如：
	///			#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
	///			#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
	///			#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
	///			#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)
	///			#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
	///			#define GPIOF   ((GPIO_TypeDef *)GPIOF_BASE)
	///			#define GPIOG   ((GPIO_TypeDef *)GPIOG_BASE)
	/// 
	///		范围就是从 GPIOA 到 GPIOG
	/// </param>
	/// <param name="GPIO_Pin"></param>
	/// <param name="PinState"></param>
	void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

	/// <summary>
	///		
	/// </summary>
	/// <param name="GPIOx">
	///		GPIO 组的宏定义。
	///		例如：
	///			#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
	///			#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
	///			#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
	///			#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)
	///			#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
	///			#define GPIOF   ((GPIO_TypeDef *)GPIOF_BASE)
	///			#define GPIOG   ((GPIO_TypeDef *)GPIOG_BASE)
	/// 
	///		范围就是从 GPIOA 到 GPIOG
	/// </param>
	/// <param name="GPIO_Pin"></param>
	void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

	/// <summary>
	///		
	/// </summary>
	/// <param name="GPIOx">
	///		GPIO 组的宏定义。
	///		例如：
	///			#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
	///			#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
	///			#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
	///			#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)
	///			#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
	///			#define GPIOF   ((GPIO_TypeDef *)GPIOF_BASE)
	///			#define GPIOG   ((GPIO_TypeDef *)GPIOG_BASE)
	/// 
	///		范围就是从 GPIOA 到 GPIOG
	/// </param>
	/// <param name="GPIO_Pin"></param>
	/// <returns></returns>
	HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

	void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


	/* Private types -------------------------------------------------------------*/
	/* Private variables ---------------------------------------------------------*/
	/* Private constants ---------------------------------------------------------*/
	/** @defgroup GPIO_Private_Constants GPIO Private Constants
	  * @{
	*/

	/**
	  * @}
	*/

	/* Private macros ------------------------------------------------------------*/
	/** @defgroup GPIO_Private_Macros GPIO Private Macros
	  * @{
	*/
	#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
	#define IS_GPIO_PIN(PIN)           (((((uint32_t)PIN) & GPIO_PIN_MASK ) != 0x00u) && ((((uint32_t)PIN) & ~GPIO_PIN_MASK) == 0x00u))
	#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT_PP)          ||\
                            ((MODE) == GPIO_MODE_OUTPUT_OD)          ||\
                            ((MODE) == GPIO_MODE_AF_PP)              ||\
                            ((MODE) == GPIO_MODE_AF_OD)              ||\
                            ((MODE) == GPIO_MODE_IT_RISING)          ||\
                            ((MODE) == GPIO_MODE_IT_FALLING)         ||\
                            ((MODE) == GPIO_MODE_IT_RISING_FALLING)  ||\
                            ((MODE) == GPIO_MODE_EVT_RISING)         ||\
                            ((MODE) == GPIO_MODE_EVT_FALLING)        ||\
                            ((MODE) == GPIO_MODE_EVT_RISING_FALLING) ||\
                            ((MODE) == GPIO_MODE_ANALOG))

	#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_FREQ_LOW) || \
                              ((SPEED) == GPIO_SPEED_FREQ_MEDIUM) || ((SPEED) == GPIO_SPEED_FREQ_HIGH))

	#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))

	/**
	  * @}
	  */

	  /* Private functions ---------------------------------------------------------*/
	  /** @defgroup GPIO_Private_Functions GPIO Private Functions
		* @{
		*/

		/**
		  * @}
		  */

		  /**
			* @}
			*/

			/**
			  * @}
			  */

	#ifdef __cplusplus
}
#endif

#endif /* STM32F1xx_HAL_GPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
