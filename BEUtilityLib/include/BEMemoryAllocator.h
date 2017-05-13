#pragma once

#undef min
#undef max

#include <new>
#include <atomic>
#include <limits>
#include <utility>

namespace BlackEngine
{
	class MemoryAllocatorBase;

	class MemoryCounter
	{
	private:
		friend class MemoryAllocatorBase;

		static BE_UTILITY_EXPORT void IncrementAllocCount() { m_Allocs++; }
		static BE_UTILITY_EXPORT void IncrementFreeCount() { m_Frees++; }

		static BE_THREADLOCAL uint64 m_Allocs;
		static BE_THREADLOCAL uint64 m_Frees;
	public:
		static BE_UTILITY_EXPORT uint64 GetNumAllocs()
		{
			return m_Allocs;
		}

		static BE_UTILITY_EXPORT uint64 GetNumFrees()
		{
			return m_Frees;
		}

	};

	class MemoryAllocatorBase
	{
	protected:
		static void IncrementAllocCount() { MemoryCounter::IncrementAllocCount(); }
		static void IncrementFreeCount() { MemoryCounter::IncrementFreeCount(); }
	};

	template< class T>
	class MemoryAllocator : public MemoryAllocatorBase
	{
	public:
		static inline void* Allocate(SIZE_T bytes)
		{
#if BE_PROFILER_ENABLED
			IncrementAllocCount();
#endif
			return malloc(bytes);
		}

		static inline void* AllocateArray(SIZE_T bytes, uint32 count)
		{
#if BE_PROFILER_ENABLED
			IncrementAllocCount();
#endif
			return malloc(bytes * count);
		}

		static inline void Free(void* ptr)
		{
#if BE_PROFILER_ENABLED
			IncrementFreeCount();
#endif
			::free(ptr);
		}

		static inline void FreeArray(void* ptr, uint32 count)
		{
			BE_UNREFERENCED_PARAMETER(count);
#if BE_PROFILING_ENABLED
			IncrementFreeCount();
#endif
			::free(ptr);
		}
	};

	class GenAlloc
	{

	};

	template<class Alloc>
	inline void* be_alloc(SIZE_T count)
	{
		return MemoryAllocator<Alloc>::Allocate(count);
	}

	template<class T, class Alloc>
	inline T* be_alloc()
	{
		return (T*)MemoryAllocator<Alloc>::Allocate(sizeof(T));
	}

	template<class T, class Alloc>
	inline T* be_newN(uint32 count)
	{
		T* ptr = (T*)MemoryAllocator<Alloc>::AllocateArray(size(T), count);

		for (uint32 i = 0; i < count; i++)
		{
			new ((void*)&ptr[i]) T;
		}

	return ptr;
	}

		template<class Type, class Alloc, class... Args>
	Type* be_new(Args&&... args)
	{
		return new (be_alloc < Alloc(sizeof(Type))) Type(std::forward<Args>(args)...);
	}

	template<class Alloc>
	inline void be_free(void* ptr)
	{
		MemoryAllocator<Alloc>::Free(ptr);
	}

	template<class T, class Alloc = GenAlloc>
	inline void be_delete(T* ptr)
	{
		(ptr)->~T();
		MemoryAllocator<Alloc>::Free(ptr);
	}

	template<class T, class Alloc = GenAlloc>
	inline void be_deleteN(T* ptr, uint32 count)
	{
		for (uint32 i = 0; i < count; i++)
		{
			ptr[i].~T();
		}

		MemoryAllocator<Alloc>::FreeArray(ptr, count);
	}

	inline void* be_alloc(SIZE_T count)
	{
		return MemoryAllocator<GenAlloc>::Allocate(count);
	}

	template<class T>
	inline T* be_alloc()
	{
		return (T*)MemoryAllocator<GenAlloc>::Allocate(sizeof(T));
	}

	template<class T>
	inline T* be_newN(uint32 count)
	{
		T* = ptr = (T*)MemoryAllocator<GenAlloc>::AllocateArray(sizeof(T), count);

		for (uint32 i = 0; i < count; i++)
		{
			new ((void*)&ptr[i]) T;
		}

		return ptr;
	}

	template<class Type, class... Args>
	Type* be_new(Args&&... args)
	{
		return new (be_alloc<GenAlloc>(sizeof(Type))) Type(std::forward<Args>(args)...);
	}

	inline void be_free(void* ptr)
	{
		MemoryAllocator<GenAlloc>::Free(ptr);
	}

#define BE_PVT_DELETE(T, ptr)	\
	(ptr)->~T();				\
	MemoryAllocator<GenAlloc>::Free(ptr);

#define BE_PVT_DELETE_A(T, ptr, Alloc)	\
	(ptr)->~T();						\
	MemoryAllocator<GenAlloc>::Free(ptr);

	template <class T, class Alloc = GenAlloc>
	void ae_new()
	{

	}

	template <class T, class Alloc = GenAlloc>
	void ae_delete()
	{

	}
}

namespace BlackEngine
{
	template <class T, class Alloc = GenAlloc>
	class StdAlloc
	{
	public:
		typedef T value_type;
		StdAlloc() _NOEXCEPT {}
		template<class T, class Alloc> StdAlloc(const StdAlloc<T, Alloc>&) _NOEXCEPT {}
		template<class T, class Alloc> bool operator==(const StdAlloc<T, Alloc>&) const _NOEXCEPT { return true; }
		template<class T, class Alloc> bool operator!=(const StdAlloc<T, Alloc>&) const _NOEXCEPT { return false; }

		T* allocate(const size_t num) const
		{
			if (num == 0)
			{
				return nullptr;
			}

			if (num > static_cast<size_t>(-1) / sizeof(T))
			{
				throw std::bad_array_new_length();
			}

			void* const pv = be_alloc<Alloc>((uint32)(num * sizeof(T)));
			if (!pv)
			{
				throw std::bad_alloc();
			}

			return static_cast<T*>(pv);
		}

		void deallocate(T* p, size_t) const _NOEXCEPT
		{
			be_free<Alloc>((void*)p);
		}
	};
}

//#include "newClass"