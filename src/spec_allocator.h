#pragma once

#include <cstddef>
#include <array>

template<class T, std::size_t N>
class spec_allocator
{
    static_assert(N != 0, "zero allocating");
    using alloc_block_t = std::array<T, N>;
    std::size_t free_size = N;
    std::size_t block_size = N;
    alloc_block_t mem_pool;
    public:
        using value_type = T;
        spec_allocator() = default;
        template <class U, std::size_t M> spec_allocator(const spec_allocator<U, M> &) noexcept {}
        T* allocate(std::size_t n)
        {
            if(!free_size)  throw std::bad_alloc();
            if(n != 1)      throw std::invalid_argument("can't allocate bigger then 1 element.");
            return &mem_pool[--free_size];
        }

        void deallocate(T *p, size_t n){};

        template<class U> struct rebind {using other = spec_allocator<U,N>;};
};

template <class T, class U, std::size_t N>
bool operator==(const spec_allocator<T,N>&, const spec_allocator<U,N>&) { return true; }
template <class T, class U, std::size_t N>
bool operator!=(const spec_allocator<T,N>&, const spec_allocator<U,N>&) { return false; }