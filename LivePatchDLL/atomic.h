#pragma once

#include <assert.h>
#include <intrin.h>
#include <cstdint>

template <typename T>
class atomic
{
    static_assert(sizeof(T) == sizeof(long), "T is expected to be a primitive type");
    long v;

public:
    atomic(T value = 0) : v(value)
    {
        assert((((uintptr_t)(&this->v))) & (sizeof(T) - 1) == 0);
    }

    T operator=(T v)
    {
        this->v = v;
        return v;
    }

    operator T() const { return v; }

    T compare_and_swap(T value, T comparand)
    {
        return _InterlockedCompareExchange(&this->v, value, comparand);
    }

    T operator++()
    {
        return _InterlockedIncrement(&v);
    }

    T operator--()
    {
        return _InterlockedDecrement(&v);
    }

    T operator++(int)
    {
        return _InterlockedIncrement(&v) - 1;
    }

    T operator--(int)
    {
        return _InterlockedDecrement(&v) + 1;
    }

    T swap(T value)
    {
        return _InterlockedExchange(&v, value);
    }
};