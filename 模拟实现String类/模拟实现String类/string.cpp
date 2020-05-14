#include<iostream>
using namespace std;
#include<assert.h>
namespace bit
{

	class string

	{

		friend ostream& operator<<(ostream& _cout, const bit::string& s)
		{
			for (size_t i = 0; i < s._size(); i++)
			{
				cout << s[i];
			}
			return _cout;
		}

		friend istream& operator>>(istream& _cin, bit::string& s)
		{
			while (1)
			{
				char ch;
				ch = _cin.get();
				if (ch == ' ' || ch == '\n')
					break;
				else
				{
					s += ch;
				}
			}
			return _cin;
		}

	public:

		typedef char* iterator;

	public:

		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);
			this->swap(tmp);
		}

		string& operator=(const string &s)
		{
			this->swap((string &)s);//需要强转 因为swap函数中的参数为string & 类型
			return *this;
		}

		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
				_size = _capacity = 0;
			}
		}



		//////////////////////////////////////////////////////////////

		// iterator

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}



		/////////////////////////////////////////////////////////////

		// modify

		void PushBack(char c) //尾插
		{
			if (_size == _capacity)
			{
				size_t newcapycity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapycity);
			}
			_str[_size] = c; //_str[_str++] = c;
			_size++;
			_str[_size] = '\0';
		}

		string& operator+=(char c)
		{
			PushBack(c);
			return *this;
		}

		void Append(const char* str)//追加子串
		{
			//判断是否需要增容
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}

		string& operator+=(const char* str)
		{
			this->Append(str); //Append(str);
			return *this;
		}

		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		const char* c_str()const
		{
			return _str;
		}



		/////////////////////////////////////////////////////////////

		// capacity

		size_t size()const
		{
			return _size;
		}

		size_t capacity()const
		{
			return _capacity;
		}

		bool empty()const
		{
			if (this)
				return true;
			else
				return false;
		}

		void resize(size_t newSize, char c = '\0') //将有效字符的个数改成n个，多出的空间用字符c填充
		{
			if (newSize < _size)
			{
				_str[newSize] = '\0';
				_size = newSize;
			}
			else
			{
				if (newSize > _size)
				{
					reserve(newSize);
				}
				for (size_t i = 0; i < newSize; i++)
				{
					_str[i] = c;
				}
				_size = newSize; //_str[newSize] = '\0';
				_str[_size] = '\0';
			}
		}

		void reserve(size_t newCapacity) //将容量扩展到n
		{
			if (newCapacity > _size)
			{
				char* newstr = new char[newCapacity + 1];
				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr;
				_capacity = newCapacity;
			}
		}



		/////////////////////////////////////////////////////////////

		// access

		char& operator[](size_t index)
		{
			assert(index < _size);
			return _str[index];
		}

		const char& operator[](size_t index)const
		{
			assert(index < _size);
			return _str[index];
		}



		/////////////////////////////////////////////////////////////

		//relational operators

		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);   //strcmp 字符串比较函数,返回值为整数
			return ret < 0;
		}

		bool operator<=(const string& s)
		{
			return *this < s || *this == s;
		}

		bool operator>(const string& s)
		{
			return !(*this <= s);
		}

		bool operator>=(const string& s)
		{
			return !(*this < s);
		}

		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}

		bool operator!=(const string& s)
		{
			return !(*this == s);
		}



		// 返回c在string中第一次出现的位置

		size_t find(char c, size_t pos = 0) const
		{
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == c)
				{
					return i;
				}
			}
			return pos;
		}

		// 返回子串s在string中第一次出现的位置

		size_t find(const char* s, size_t pos = 0) const
		{
			char* p = strstr(_str, s);//判断字符串str2是否是str1的子串。如果是，则该函数返回 str1字符串从 str2第一次出现的位置开始到 str1结尾的字符串；否则，返回NULL
			if (p == nullptr)
			{
				return pos;
			}
			else
			{
				return p - _str;
			}
		}

		// 在pos位置上插入字符c/字符串str，并返回该字符的位置

		string& insert(size_t pos, char c)
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			int end = _size;
			while (end >= (int)pos) //从pos起向后调整一个位置
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = c;
			++_size;
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			//判断是否需要增容
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + len] = _str[end];
				--end;
			}
			strncpy(_str + pos, str, len); //因为strncpy函数不会添加'\0'
			_size += len;
			return *this;
		}



		// 删除pos位置上(长度为len)的元素，并返回该元素的下一个位置

		string& erase(size_t pos, size_t len)
		{
			assert(pos < _size);
			if (len >= _size - pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t i = pos + len;
				while (i <= _size)
				{
					_str[i - len] = _str[i];
					i++;
				}
				_size -= len;
			}
		}

	private:

		char* _str;

		size_t _capacity;

		size_t _size;

	};

};