#pragma once
#include<hal-wrapper/container/IList.h>
#include<stdint.h>

namespace hal
{
	template<typename T, uint16_t BufferSize>
	class List :public IList<T>
	{
	private:
		T _buffer[BufferSize]{};
		uint16_t _tail = 0;

	public:
		bool Add(const T &item) override
		{
			if (_tail >= BufferSize)
			{
				return false;
			}

			_buffer[_tail] = item;
			_tail++;
			return true;
		}

		bool Insert(int index, const T &item) override
		{
			if (index < 0 || index > _tail)
			{
				return false;
			}

			if (index == _tail)
			{
				return Add(item);
			}

			// 现在 index 在 [0, _tail) 内
			if (_tail >= BufferSize)
			{
				return false;
			}

			// 此时 _tail 可能的最大值为 BufferSize - 1
			for (int i = _tail; i > index; i--)
			{
				// 将前一格的元素移动到当前格
				_buffer[i] = _buffer[i - 1];
			}

			_buffer[index] = item;
			_tail++;
			return true;
		}

		bool Remove(const T &item) override
		{
			int index = IndexOf(item);
			if (index >= 0)
			{
				RemoveAt(index);
				return true;
			}

			return false;
		}

		void RemoveAt(int index) override
		{
			if (index < 0 || index >= _tail)
			{
				// _tail == 0 的情况也会导致必定直接返回。
				return;
			}

			// 到这里说明 _tail >= 1
			for (int i = index; i < _tail - 1; i++)
			{
				/* 将后一个元素往前拉到当前格子上
				*
				* 当 i == _tail - 1 时，就会把 _tail 处的元素拉到 _tail - 1 处，
				* 这个操作没有意义，因为 _tail 指向的是无效元素。所以 i 只要到 _tail - 2 就行了，
				* 所以循环条件是 i < _tail - 1。
				*
				* 开始循环前，因为循环前面的 if 进行了过滤，所以 _tail >= 1。
				*
				* 当 _tail == 1 时，_tail - 1 == 0，此时循环条件 i < _tail - 1 不可能成立，
				* 不会进入循环。而循环后面的 _tail-- 照常执行，实现了移除位于 0 位置的元素。
				*/
				_buffer[i] = _buffer[i + 1];
			}

			_tail--;
		}

		int IndexOf(const T &item) const override
		{
			for (uint16_t i = 0; i < _tail; i++)
			{
				if (_buffer[i] == item)
				{
					return i;
				}
			}

			return -1;
		}

		bool Contains(const T &item) const override
		{
			int index = IndexOf(item);
			return index >= 0;
		}

		void Clear() override
		{
			_tail = 0;
		}

		int Count() const override
		{
			return _tail;
		}

		T &operator[](int index) override
		{
			return _buffer[index];
		}

		T const &operator[](int index) const override
		{
			return _buffer[index];
		}
	};
}