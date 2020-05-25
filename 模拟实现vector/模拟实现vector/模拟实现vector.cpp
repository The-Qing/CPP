#pragma once
#include<assert.h>
#include<iostream>
using namespace std;
namespace vector_s
{
	template<class T>

	class vector

	{

	public:

		// Vector的迭代器是一个原生指针

		typedef T* iterator;

		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin()
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}



		// construct and destroy

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end0fStorage(nullptr)
		{}

		vector(int n, const T& value = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end0fStorage(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(value);
			}
		}

		template<class InputIterator>

		vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);
			while (first != last)
			{
				push_back(*first);
				first++;
			}

		}

		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end0fStorage(nullptr)
		{
			reserve(v.capacity());
			for (const auto& e : v)
				push_back(e);
		}

		vector<T>& operator= (vector<T> v)
		{
			swap(v);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end0fStorage = nullptr;
		}

		// capacity

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end0fStorage - _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];

				if (_start)
				{
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start[i];
				}
			}

			_start = tmp;
			_finish = _start + sz;
			_end0fStorage = _start + n;
		}
		void resize(size_t n, const T& value = T())
		{
			if (n <= size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);

				iterator it = _finish;
				iterator _finish = _start + n;
				while (it != _finish)
				{
					*it = value;
					it++;
				}
			}
		}



		///////////////access///////////////////////////////

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}



		///////////////modify/////////////////////////////

		void push_back(const T& x)
		{
			insert(_finish, x);
		}

		void pop_back()
		{
			erase(_finish - 1);
		}

		void Swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_end0fStroage, v._end0fStroage);
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			//空间不够进行增容
			if (_finish == _end0fStorage)
			{
				size_t size = size();
				size_t newcapacity = (0 == capacity()) ? 2 : capacity() * 2;
				reserve(newcapacity);

				pos = _start + size;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = x;
			_finish++;
		}

		iterator erase(iterator pos)
		{
			assert(pos < _finish);

			iterator it = pos;
			while (it < _finish)
			{
				*it = *(it + 1);
				it++;
			}
			_finish--;
			return pos;
		}

	private:

		iterator _start; // 指向数据块的开始

		iterator _finish; // 指向有效数据的尾

		iterator _endOfStorage; // 指向存储容量的尾

	};

}