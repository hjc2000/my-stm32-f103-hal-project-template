#pragma once
#include<base/HandleWrapper.h>
#include<bsp-interface/ILcd.h>
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramConfig.h>
#include<hal-wrapper/peripheral/fsmc/FsmcNorSramTiming.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>
#include<stdexcept>

namespace bsp
{
	class Lcd :
		public bsp::ILcd,
		public base::HandleWrapper<SRAM_HandleTypeDef>
	{
	private:
		Lcd();

		SRAM_HandleTypeDef _sram_handle;

		/// <summary>
		///		屏幕初始宽度。与屏幕旋转无关，无论屏幕怎么旋转，本属性都保持不变。
		/// </summary>
		/// <returns></returns>
		static consteval uint32_t OriginalWidth()
		{
			return 240;
		}

		/// <summary>
		///		屏幕初始高度。与屏幕旋转无关，无论屏幕怎么旋转，本属性都保持不变。
		/// </summary>
		/// <returns></returns>
		static consteval uint32_t OriginHeight()
		{
			return 320;
		}

		/// <summary>
		///		屏幕总共有多少个点。
		/// </summary>
		/// <returns></returns>
		static consteval uint32_t PointCount()
		{
			return OriginalWidth() * OriginHeight();
		}

		bool _is_horizontal_priority_scanning = true;
		bsp::HorizontalDirection _horizontal_direction = bsp::HorizontalDirection::LeftToRight;
		bsp::VerticalDirection _vertical_direction = bsp::VerticalDirection::TopToBottom;

		#pragma region 连接到LCD的GPIO引脚
		/// <summary>
		///		连接 LCD 的 RD 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &RD_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPinConfig::PinEnum RD_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin4;
		}

		/// <summary>
		///		连接 LCD 的 WR 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &WR_Port()
		{
			return hal::GpioPortD::Instance();
		}
		hal::GpioPinConfig::PinEnum WR_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin5;
		}

		/// <summary>
		///		连接 LCD 的 BL 引脚。这是控制背光的。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &BL_Port()
		{
			return hal::GpioPortB::Instance();
		}
		hal::GpioPinConfig::PinEnum BL_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin0;
		}

		/// <summary>
		///		连接 LCD 的 CS 引脚。这是片选。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &CS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPinConfig::PinEnum CS_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin12;
		}

		/// <summary>
		///		连接到 LCD 的 RS 引脚。
		/// </summary>
		/// <returns></returns>
		hal::IGpioPort &RS_Port()
		{
			return hal::GpioPortG::Instance();
		}
		hal::GpioPinConfig::PinEnum RS_Pin()
		{
			return hal::GpioPinConfig::PinEnum::Pin0;
		}
		#pragma endregion

		volatile uint16_t *CommandAddress()
		{
			constexpr uint32_t addr = (uint32_t)((0X60000000 + (0X4000000 * (4 - 1))) | (((1 << 10) * 2) - 2));
			return reinterpret_cast<uint16_t *>(addr);
		}

		volatile uint16_t *DataAddress()
		{
			return CommandAddress() + 2;
		}

		uint16_t ColorCode(bsp::Color color)
		{
			switch (color)
			{
			case bsp::Color::Red:
				{
					return 0x001F;
				}
			case bsp::Color::Green:
				{
					return 0x07E0;
				}
			case bsp::Color::Blue:
				{
					return 0xF800;
				}
			case bsp::Color::White:
				{
					// 0xffff 表示该像素的 3 个液晶全部透光度开到最大，呈现出白色
					return UINT16_MAX;
				}
			case bsp::Color::Black:
			default:
				{
					// 0 表示全不透光，所以是黑色
					return 0;
				}
			}
		}

		void InitGpio();

		/// <summary>
		///		每次向屏幕中写像素前都需要调用一次本函数，然后就可以连续写入像素了。
		///		* 推测本函数的作用是让 LCD 驱动芯片内部的一个指针复位，这样写入像素
		///		  后才能从原点开始填充。或者之前用了其他命令将驱动芯片置于非写入像素的
		///		  模式下，此时必须调用本函数才能让驱动芯片回到写入像素的模式。
		/// </summary>
		void PrepareForRendering();

	public:
		static Lcd &Instance()
		{
			static Lcd o;
			return o;
		}

		SRAM_HandleTypeDef &Handle() override
		{
			return _sram_handle;
		}

		void WriteCommand(uint16_t cmd);
		void WriteCommand(uint16_t cmd, uint16_t param);

		void WriteData(uint16_t data);
		uint16_t ReadData();

		void TurnOnBackLight() override;
		void TurnOffBackLight() override;

		uint32_t LcdDriverChipId() override;

		void DisplayOn() override;
		void DisplayOff() override;

		void Clear(bsp::Color color) override;

		/// <summary>
		///		设置扫描方向。
		/// </summary>
		/// <note>
		///		让 LCD 显示的方法是将屏幕上的一个个像素的 RGB 值逐个写入。
		///		有多少个像素，就要写入多少组 RGB 值。写入一个像素的 RGB 值
		///		后，驱动芯片会自动将位置指针递增，下次写入 RGB 就是对应下一个像素了。
		/// 
		///		驱动芯片内部自动递增的指针就是扫描指针，指向的是当前要被写入的像素。
		///		扫描顺序可以是先水平，后竖直，也可以是先竖直，后水平。水平又可以分为
		///		从左到右和从右到左。竖直可以分为从上到下和从下到上。
		/// </note>
		/// <param name="horizontal_priority_scanning"></param>
		/// <param name="hdir"></param>
		/// <param name="vdir"></param>
		void SetScanDirection(
			bool horizontal_priority_scanning,
			bsp::HorizontalDirection hdir,
			bsp::VerticalDirection vdir
		) override;

		uint32_t Width() override;
		uint32_t Height() override;

		void SetWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SerCursor(uint32_t x, uint32_t y) override;
		void DrawPoint(uint32_t x, uint32_t y, uint16_t rgb_565) override;
	};
}
