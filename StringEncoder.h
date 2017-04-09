#pragma once

#include <algorithm>
#include <string>
#include <exception>

#ifdef DEBUG
#include <iostream>
#endif

namespace NStringEncoder
{
    template <typename TChar>
    class TBasicConstExprString
    // Ref: https://github.com/boostcon/cppnow_presentations_2012/blob/master/wed/schurr_cpp11_tools_for_class_authors.pdf?raw=true
    {
        const TChar* const DataPtr;
        const size_t Size;
    public:
        template<size_t N>
        constexpr TBasicConstExprString(const TChar(&a)[N])
        : DataPtr(a), Size(N-1) {}

        constexpr TChar operator[](size_t n) const
        {
            return (n < Size) ? DataPtr[n] : throw std::out_of_range("");
        }

        constexpr size_t size() const
        {
            return Size;
        }

        constexpr size_t binarySearch(TChar t) const
        {
            return binarySearchImpl(t, 0, Size);
        }

    private:
        constexpr size_t binarySearchImpl(TChar t, size_t s, size_t e) const
        {
            return (e <= s)                ? (-1)                               :
                   (t == (*this)[(s+e)/2]) ? (s+e)/2                            :
                   (t < (*this)[(s+e)/2])  ? binarySearchImpl(t, s, (s+e)/2)    :
                                             binarySearchImpl(t, (s+e)/2 + 1, e);
        }
    };

    constexpr size_t pow(size_t a, size_t n)
    {
        return (n > 1) ? a*pow(a, n-1) : a;
    }

    constexpr size_t min(size_t a, size_t b)
    {
        return (a > b) ? b : a;
    }

    constexpr size_t max(size_t a, size_t b)
    {
        return (a < b) ? b : a;
    }

    constexpr size_t gcd(size_t a, size_t b)
    {
        return (min(a, b) == 0) ? max(a, b) : gcd(min(a, b), max(a, b)%min(a, b));
    }

    constexpr size_t lcm(size_t a, size_t b)
    {
        return (a*b) / gcd(a, b);
    }

    using TConstExprString = TBasicConstExprString<char>;
    using TString = std::basic_string<char>;

    constexpr TConstExprString sortedBase64Chars {".0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"};

};
