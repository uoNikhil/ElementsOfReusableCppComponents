


template<int a, int b>
struct GCD
{
    inline static constexpr int type = GCD<b, a%b>::type;
};

template<int a>
struct GCD<a, 0>
{
    inline static constexpr int type = a;
};

int main()
{
    static_assert(GCD<5,15>::type == 5);
    static_assert(GCD<21,31>::type == 1);
    static_assert(GCD<6,21>::type == 3);

}





