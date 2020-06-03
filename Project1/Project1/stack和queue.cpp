#include<vector>
namespace Qing

{

	template<class T, class Con = deque<T>>

	class stack

	{

	public:

		stack()
		{}

		void push(const T& x)
		{
			_c.push_back(x);
		}

		void pop()
		{
			_c.popback();
		}

		T& top()
		{
			return _c.back();
		}

		const T& top()const
		{
			return _c.bakc();
		}

		size_t size()const
		{
			return _c.size();
		}

		bool empty()const
		{
			return _c.empty();
		}

	private:

		Con _c;

	};



	template<class T, class Con = deque<T>>

	class queue

	{

	public:

		queue();

		void push(const T& x)
		{
			_c.push_back();
		}

		void pop()
		{
			_c.pop_front();
		}

		T& back()
		{
			return _c.back();
		}

		const T& back()const
		{
			return _c.back();
		}

		T& front()
		{
			return _c.front();
		}

		const T& front()const
		{
			return _c.front();
		}

		size_t size()const
		{
			return _c.size();
		}

		bool empty()const
		{
			return _c.empty();
		}

	private:

		Con _c;

	};

};