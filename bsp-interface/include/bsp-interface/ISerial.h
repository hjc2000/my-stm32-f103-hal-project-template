#pragma once
#include<bsp-interface/stream/Stream.h>
#include<string>

namespace bsp
{
	class ISerial :public bsp::Stream
	{
	public:
		/// <summary>
		///		串口类中，流的 Length 属性的意义是当前接收缓冲区中的可读数据的长度。
		/// </summary>
		/// <returns></returns>
		virtual int64_t Length() = 0;

		/// <summary>
		///		以指定的波特率启动串口。
		/// </summary>
		/// <param name="baud_rate"></param>
		virtual void Begin(uint32_t baud_rate) = 0;

		void Print(std::string const &str);
		void PrintLine(std::string const &str);
		void Print(char const *str);
		void PrintLine(char const *str);

		/// <summary>
		///		错误汇报。
		///		* 尝试利用串口输出错误信息。
		///		* 本函数不会抛出异常，内部捕获了所有异常，这确保当串口不可用，
		///		  串口类抛出异常时不会导致异常逃逸。因为 ReportError 是设计
		///		  为在 catch 块中使用的，而 catch 块一般不再嵌套 try-catch。
		///		* 严重错误时可能会连本函数都用不了。
		/// </summary>
		/// <param name="str"></param>
		void ReportError(char const *str) noexcept;
		void ReportError(std::string const &str) noexcept;
	};
}
