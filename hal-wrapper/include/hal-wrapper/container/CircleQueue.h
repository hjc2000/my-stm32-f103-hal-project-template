#pragma once
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		循环队列
	/// </summary>
	template<typename T, uint16_t BufferSize>
	class CircleQueue
	{
	private:
		T _buffer[BufferSize]{};
		uint16_t _head = 0;
		uint16_t _tail = 0;
		bool _is_empty = true;

		void IncHead()
		{
			_head++;
			_head = _head % BufferSize;
		}

		void IncTail()
		{
			_tail++;
			_tail = _tail % BufferSize;
		}

	public:
		bool IsEmpty() const
		{
			return _is_empty;
		}

		bool IsFull() const
		{
			return _head == _tail && !_is_empty;
		}

		uint16_t Count() const
		{
			if (_is_empty)
			{
				return 0;
			}

			if (_tail > _head)
			{
				return _tail - _head;
			}

			// 发生了环绕
			return BufferSize - (_head - _tail);
		}

		/// <summary>
		///		入队
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		bool TryEnqueue(T const &element)
		{
			if (IsFull())
			{
				return false;
			}

			_buffer[_tail] = element;
			IncTail();
			_is_empty = false;
		}

		/// <summary>
		///		退队
		/// </summary>
		/// <param name="out_element"></param>
		/// <returns></returns>
		bool TryDequeue(T &out_element)
		{
			if (IsEmpty())
			{
				return false;
			}

			out_element = _buffer[_head];
			IncHead();
			if (_head == _tail)
			{
				_is_empty = true;
			}

			return true;
		}

		void Clear()
		{
			_head = 0;
			_tail = 0;
			_is_empty = true;
		}
	};
}