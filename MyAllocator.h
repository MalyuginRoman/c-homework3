#pragma once

#include <iostream>
#include <memory>
#include "memblock.h"

template<class T>
class MemManager;
template<class T,size_t N>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using const_reference = const T&;
    using reference = T&;
    using size_type = std::size_t;
    template<typename U>
    struct rebind {
        using other = MyAllocator<U, N>;
    };
    MyAllocator(){};
    T * allocate(std::size_t n){
        return mem.allocate(n);
    };
    void deallocate(){};
    template<typename U, typename... Args>
    void construct(U * p, Args&& ... args){
        new((void*) p) U(std::forward<Args>(args)...);
    }
    void destroy(value_type * p){
        p->~T();
    };
private:
    MemManager<T> mem{N};
};
