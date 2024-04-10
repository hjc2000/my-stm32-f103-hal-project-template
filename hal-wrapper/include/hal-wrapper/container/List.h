#pragma once
#include<stdint.h>

namespace hal
{
	template<typename T, uint16_t BufferSize>
	class List
	{
	private:
		T _buffer[BufferSize]{};
		uint16_t _pos = 0;

		/// <summary>
		///		将缓冲区中从 start_pos 开始，包括 start_pos 处的元素往前移动一格。
		/// </summary>
		/// <param name="start_pos"></param>
		void MoveUp(uint16_t start_pos)
		{
			if (start_pos == 0)
			{
				return;
			}

			if (IsEmpty())
			{
				// 为空就提前返回，避免后面有一句 _pos--; 错误地执行。
				return;
			}

			for (uint16_t pos = start_pos; pos < _pos; pos++)
			{
				_buffer[pos - 1] = _buffer[pos];
			}

			_pos--;
		}

	public:
		bool IsEmpty()
		{
			return _pos == 0;
		}

		bool IsFull()
		{
			return _pos == BufferSize;
		}

		bool TryAdd(T const &element)
		{
			if (IsFull())
			{
				return false;
			}

			_buffer[_pos] = element;
			_pos++;
			return true;
		}

		bool Remove(T const &element)
		{
			for (uint16_t pos = 0; pos < _pos; pos++)
			{
				if (_buffer[pos] == element)
				{
					// 现在 pos 指向的就是要被移除的元素
					MoveUp(pos + 1);
					return true;
				}
			}

			return false;
		}

		void Clear()
		{
			_pos = 0;
		}

		bool Contains(T const &element)
		{
			for (uint16_t i = 0; i < _pos; i++)
			{
				if (_buffer[i] == element)
				{
					return true;
				}
			}

			return false;
		}

		uint16_t Count()
		{
			return _pos;
		}

		T &operator[](uint16_t index)
		{
			return _buffer[index];
		}
	};
}