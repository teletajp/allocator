#pragma once

#include <cstddef>
#include <array>

namespace ma
{
template<class T, std::size_t N>
class spec_allocator
{
    static_assert(N != 0, "zero allocating");
    using alloc_block_t = std::array<T, N>;
    std::size_t block_size = N;
    public:
        using value_type = T;
        spec_allocator() = default;
        T* allocate(std::size_t n)
        {

        }

        void deallocate(T *p, size_t n){};

        template<class U> struct rebind {using other = spec_allocator<U,N>;};
};
}
template <class T, class U, std::size_t N>
bool operator==(const ma::spec_allocator<T,N>&, const ma::spec_allocator<U,N>&) { return true; }
template <class T, class U, std::size_t N>
bool operator!=(const ma::spec_allocator<T,N>&, const ma::spec_allocator<U,N>&) { return false; }