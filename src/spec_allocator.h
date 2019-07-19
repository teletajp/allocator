#pragma once

#include <cstddef>
#include <array>

template<class T, std::size_t N = 1>
class spec_allocator
{
    
    static_assert(N != 0, "zero allocating");
    public:
        std::size_t free_size = N;
        std::size_t count = 0;
        uint8_t* mem_pool = nullptr;
        using value_type = T;

        spec_allocator(){}
        constexpr spec_allocator(const spec_allocator&) noexcept = default;
        //~spec_allocator() { if(mem_pool) delete mem_pool; }
        template <class U, std::size_t M> spec_allocator(const spec_allocator<U, M> &right) noexcept
        {
            //std::cout << "copy spec_allocator()" << std::endl;
        };

        constexpr std::size_t max_size() { return N; };

        T* allocate(std::size_t n)
        {
            
            if (!mem_pool)
            {
                mem_pool = (uint8_t*)std::malloc( sizeof(T) * (N+1));
                free_size = N+1;
            }
            if(!free_size)  throw std::bad_alloc();
            if(n != 1)      throw std::invalid_argument("can't allocate bigger then 1 element.");
            count++;
            T* p = reinterpret_cast<T*>(&mem_pool[(--free_size) * sizeof(T)]);
            //std::cout << "allocate:" << p <<std::endl;
            return p;
        };

        void deallocate(T *p, size_t n)
        {
            //std::cout << "deallocate:" << p << std::endl;
            if (count && !(--count))
            {
                std::free(mem_pool);
                mem_pool = nullptr;
            }
        };

        template <typename U, typename ... Args>
        void construct(U *p, Args&& ... args)
        {
            new(p) U(std::forward<Args>(args) ...);
            //std::cout << "construct:" << p << std::endl;
        }
        template <typename U>
        void destroy(U *p)
        {
            p->~U();
            //std::cout << "destroy:" << p << std::endl;
        }

        template<class U> struct rebind {using other = spec_allocator<U,N>;};
};

template <class T, class U, std::size_t N>
bool operator==(const spec_allocator<T,N>&, const spec_allocator<U,N>&) { return true; }
template <class T, class U, std::size_t N>
bool operator!=(const spec_allocator<T,N>&, const spec_allocator<U,N>&) { return false; }