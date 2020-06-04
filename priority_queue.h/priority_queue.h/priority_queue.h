#include<vector>

#include<functional>
namespace Qing

{
	template<class T>
	struct less
	{
		bool operator()(const T& left, const T& right)
		{
			return left < right;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& left, const T& right)
		{
			return left > right;
		}
	};

	template <class T, class Container = vector<T>, class Compare = less<T> >

	class priority_queue

	{

	public:

		priority_queue()
			:c()
		{
		}

		template <class InputIterator>

		priority_queue(InputIterator first, InputIterator last)
			:c(first,last)
		{
			//调整成堆结构
			int count = c.size();
			int root = ((count - 2) >> 1);
			for (; root >= 0; --root)
			{
				AdjustDown(root);
			}
		}

		bool empty() const
		{
			return c.empty();
		}

		size_t size() const
		{
			return c.size();
		}

		T& top() const
		{
			return c.front();
		}

		void push(const T& x)
		{
			c.push_back(data);
			AdjustUp(c.size() - 1);
		}

		void pop()
		{
			if (empty())
				return;
		}

	private:
		void AdjustUp(int child)
		{
			int parent = ((child - 1) >> 1);
			while (child)
			{
				if (Com()(c[parent], c[child]))
				{
					swap(c[child], c[parent]);
					child = parent;
					parent = ((child - 1) >> 1);
				}
				else
					return;
			}
		}

		void AdjustDown(int parent)
		{
			int child = parent * 2 + 1;
			while (child < c.size())
			{
				//找大孩子
				if (child + 1) < c.size() && Com((c[child], c[parent]))
					++child;
				
				if (Com()(c[parent], c[child]))
				{
					swap(c[child], c[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
			}
		}
		Container c;

		Compare comp;

	};

};