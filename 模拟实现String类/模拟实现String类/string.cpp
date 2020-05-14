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
			this->swap((string &)s);//��Ҫǿת ��Ϊswap�����еĲ���Ϊstring & ����
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

		void PushBack(char c) //β��
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

		void Append(const char* str)//׷���Ӵ�
		{
			//�ж��Ƿ���Ҫ����
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

		void resize(size_t newSize, char c = '\0') //����Ч�ַ��ĸ����ĳ�n��������Ŀռ����ַ�c���
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

		void reserve(size_t newCapacity) //��������չ��n
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
			int ret = strcmp(_str, s._str);   //strcmp �ַ����ȽϺ���,����ֵΪ����
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



		// ����c��string�е�һ�γ��ֵ�λ��

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

		// �����Ӵ�s��string�е�һ�γ��ֵ�λ��

		size_t find(const char* s, size_t pos = 0) const
		{
			char* p = strstr(_str, s);//�ж��ַ���str2�Ƿ���str1���Ӵ�������ǣ���ú������� str1�ַ����� str2��һ�γ��ֵ�λ�ÿ�ʼ�� str1��β���ַ��������򣬷���NULL
			if (p == nullptr)
			{
				return pos;
			}
			else
			{
				return p - _str;
			}
		}

		// ��posλ���ϲ����ַ�c/�ַ���str�������ظ��ַ���λ��

		string& insert(size_t pos, char c)
		{
			assert(pos <= _size);
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			int end = _size;
			while (end >= (int)pos) //��pos��������һ��λ��
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
			//�ж��Ƿ���Ҫ����
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
			strncpy(_str + pos, str, len); //��Ϊstrncpy�����������'\0'
			_size += len;
			return *this;
		}



		// ɾ��posλ����(����Ϊlen)��Ԫ�أ������ظ�Ԫ�ص���һ��λ��

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