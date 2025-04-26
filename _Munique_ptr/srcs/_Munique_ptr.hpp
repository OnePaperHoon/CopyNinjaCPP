#ifndef _MUNIQUE_PTR_HPP
#define _MUNIQUE_PTR_HPP
#include <cstddef>
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
				deleter(ptr);
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
				deleter(ptr);
				ptr = other.ptr;
				deleter = std::move(other.deleter);
				other.ptr = nullptr;
			}
			return *this;
		}

		T& operator*() const { return *ptr; }
		T* operator->() const { return ptr; }

		explicit operator bool() const noexcept
		{
			return ptr != nullptr;
		}

		T* get() const
		{
			return (ptr);
		}

		void reset(T* p = nullptr)
		{
			if (ptr != p)
			{
				deleter(ptr);
				ptr = p;
			}
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

template <typename T, typename D>
bool operator==(const _Munique_ptr<T, D>& lhs, std::nullptr_t) {
	return lhs.get() == nullptr;
}

template <typename T, typename D>
bool operator!=(const _Munique_ptr<T, D>& lhs, std::nullptr_t) {
	return lhs.get() != nullptr;
}

template <typename T, typename D>
void swap(_Munique_ptr<T, D>& lhs, _Munique_ptr<T, D>& rhs) noexcept
{
	lhs.swap(rhs);
}

template <typename T, typename... Args>
_Munique_ptr<T> make_munique(Args&&... args)
{
	return _Munique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif // _MUNIQUE_PTR_HPP
