#include<type_traits>


/*
template<int... nums>
struct  Vector{};

template<typename input, typename output = Vector<>>
struct remDup
{};

template<int i, int... tail, int... out>
struct remDup<Vector<i,i, tail...>, Vector<out...>>
{
    using value = typename remDup<Vector<i, tail...>, Vector<out...>>::value;
    
};

template<int i, int... tail, int... out>
struct remDup<Vector<i, tail...>, Vector<out...>>
{
    using value = typename remDup<Vector<tail...>, Vector<out...,i>>::value;
    
};

template<typename outvector>
struct remDup<Vector<>, outvector>
{
    using value =  outvector;
};


int main()
{
    //VECTOR<1,2,3,4,5>
    static_assert(std::is_same_v<remDup<Vector<1,2,3>>,Vector<1,2,3>>);
    return 0;
}
*/

#include <type_traits>

template<int... nums>
struct Vector{};

template<typename input, typename output = Vector<>, typename last = void>
struct remDup;

// Specialization for non-empty input vector.
template<int i, int... tail, int... out>
struct remDup<Vector<i, tail...>, Vector<out...>, void> {
    using value = typename remDup<Vector<tail...>, Vector<out..., i>, Vector<i>>::value;
};

// Specialization for non-empty input vector when the last number is not a duplicate.
template<int i, int... tail, int... out, int last>
struct remDup<Vector<i, tail...>, Vector<out...>, Vector<last>> {
    using value = typename remDup<Vector<tail...>, Vector<out..., i>, Vector<i>>::value;
};

// Specialization for non-empty input vector when the last number is a duplicate.
template<int... tail, int... out, int last>
struct remDup<Vector<last, tail...>, Vector<out...>, Vector<last>> {
    using value = typename remDup<Vector<tail...>, Vector<out...>, Vector<last>>::value;
};

// Specialization for empty input vector.
template<int... out>
struct remDup<Vector<>, Vector<out...>, void> {
    using value = Vector<out...>;
};

// Specialization for empty input vector when the last number is known.
template<int... out, int last>
struct remDup<Vector<>, Vector<out...>, Vector<last>> {
    using value = Vector<out...>;
};

int main()
{
    static_assert(std::is_same_v<typename remDup<Vector<1,1,2,2,3>>::value, Vector<1,2,3>>);
    return 0;
}
