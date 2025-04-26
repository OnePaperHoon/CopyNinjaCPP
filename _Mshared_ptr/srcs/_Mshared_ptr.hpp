#ifndef _MSHARED_PTR
#define _MSHARED_PTR

/*
	shared_ptr 개념
		- 여려 개의 스마트 포인터가 동일한 객체를 공유
		- 내부적으로 참조 카운터(reference count)를 사용
		- 마지막 참조가 소멸될 때 자원도 자동으로 해제됨
	구조적 특징
		- 포인터(T*)와 참조 카운터 (int*)를 함께 소유
		- 복사 시 참조 수 증가, 소멸 시 감소
		- 참조수가 0이되면 실제 객체 메모리를 해제
*/
template <typename T>
class _Mshared_ptr
{
	public:
		_Mshared_ptr(T* p = nullptr)
		: ptr(p)
		{
			if (p)
				refCount = new int(1);
			else
				refCount = nullptr;
		}

		_Mshared_ptr(const _Mshared_ptr& other)
		: ptr(other.ptr), refCount(other.refCount)
		{
			if (refCount)
				++(*refCount);
		}

		_Mshared_ptr& operator=(const _Mshared_ptr& other)
		{
			if (this != &other)
			{
				release();
				ptr = other.ptr;
				refCount = other.refCount;
				if (refCount)
					++(*refCount);
			}
			return *this;
		}
		_Mshared_ptr& operator=(_Mshared_ptr&& other) noexcept
		{
			if (this != &other)
			{
				release();
				ptr = other.ptr;
				refCount = other.refCount;
				other.ptr = nullptr;
				other.refCount = nullptr;
			}
			return *this;
		}
		_Mshared_ptr(_Mshared_ptr&& other) noexcept
		: ptr(other.ptr), refCount(other.refCount)
		{
			other.ptr = nullptr;
			other.refCount = nullptr;
		}

		~_Mshared_ptr()
		{
			release();
		}

		T& operator*() const
		{
			return *ptr;
		}

		T* operator->() const
		{
			return ptr;
		}

		T* get() const
		{
			return ptr;
		}

		int use_count() const
		{
			return refCount ? *refCount : 0;
		}

		bool unique() const
		{
			return use_count() == 1;
		}

		explicit operator bool() const
		{
			return ptr != nullptr;
		}

	private:
		void release()
		{
			if (refCount && --(*refCount) == 0)
			{
				delete ptr;
				delete refCount;
			}
		}

	private:
		T*		ptr;
		int*	refCount;
};

#endif
