

template<int a, int b>
struct isPrimeUtil
{
    inline static constexpr bool val = a%b!=0 && isPrimeUtil<a,b-1>::val;
};

template<int a>
struct isPrimeUtil<a,2>
{
    inline static constexpr bool val = a%2!=0;
};



template <int a>
struct isPrime
{
    inline static constexpr bool val = isPrimeUtil<a,a/2>::val;
};


int main()
{
    static_assert(isPrime<7>::val == true);
}

