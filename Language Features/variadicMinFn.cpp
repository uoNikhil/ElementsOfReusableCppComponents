#include <iostream>
using namespace std;
#include <climits>


template<typename Arg>
Arg minFunc(Arg min, Arg start)
{
    return min<start?min:start;
}

template<typename Arg, typename... Args>
int minFunc(Arg start, Args... rest)
{
    return minFunc(start, minFunc(rest...));
}

template<class Compare, typename Arg>
Arg minFuncComp(Compare comp, Arg first, Arg second)
{
    return comp(first, second)?first:second;
}

template<class Compare, typename Arg, typename... Args>
Arg minFuncComp(Compare comp, Arg first, Args... rest)
{
    return minFuncComp(comp, first, minFuncComp(comp, rest...));
}

int main()
{
    int minimum = minFunc(1,2,3,4,5);
    std::cout <<"Min = " << minimum << std::endl;

    minimum = minFuncComp(std::less<>(), 1,2,3,0,4,5);
    std::cout <<"Min = " << minimum << std::endl;
}