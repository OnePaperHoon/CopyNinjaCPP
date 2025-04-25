#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP
#include <memory>

template <typename T, typename Deleter = std::default_delete<T>>
class _Munique_ptr
{
	public:
		explicit _Munique_ptr(T* p = nullptr, Deleter d = Deleter())
		: ptr(p)
		, deleter(d)
		{}

		~_Munique_ptr()
		{
			if (ptr)
				delete ptr;
		}

		_Munique_ptr(const _Munique_ptr&) = delete;
		_Munique_ptr& operator=(const _Munique_ptr&) = delete;

		_Munique_ptr(_Munique_ptr&& other) noexcept
		: ptr(other.ptr)
		, deleter(std::move(other.deleter))
		{
			other.ptr = nullptr;
		}

		_Munique_ptr& operator=(_Munique_ptr&& other) noexcept
		{
			if (this != &other)
			{
				delete ptr;
				ptr = other.ptr;
				deleter = std::move(other.deleter);
				other.ptr = nullptr;
			}
			return *this;
		}

		T& operator*() const { return *ptr; }
		T* operator->() const { return ptr; }

		T* get() const
		{
			return (ptr);
		}

		void reset(T* p = nullptr)
		{
			delete ptr;
			ptr = p;
		}

		T* release()
		{
			T* oldPtr = ptr;
			ptr = nullptr;
			return oldPtr;
		}

		void swap(_Munique_ptr& other) noexcept
		{
			std::swap(ptr, other.ptr);
			std::swap(deleter, other.deleter);
		}

		Deleter& get_deleter() noexcept
		{
			return deleter;
		}

		const Deleter& get_deleter() const noexcept
		{
			return deleter;
		}

	private:
		T* ptr;
		Deleter deleter;
};

#endif // MY_UNIQUE_PTR_HPP
