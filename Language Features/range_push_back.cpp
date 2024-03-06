#include<iostream>
#include<vector>
#include<list>
#include <sstream>


template <typename Container, typename T>
void push_back(Container& c, const T val)
{
    c.push_back(val);
}
template <typename Container, typename T, typename... P>
void push_back(Container& c, const T val, P... rest)
{
    c.push_back(val);
    push_back(c, rest...);
}

template <typename Container>
void print(const Container& c) 
{
    std::stringstream ss;
    ss << "{ ";
    for(auto itr = c.begin(); itr!=c.end(); itr++)
    {
        ss << *itr << ", ";
    }
    ss << "}\n";
    std::cout << ss.str();
}

int main()
{
    std::vector<int> vec;
    push_back(vec, 1,2,3,4);
    print(vec);

    std::vector<char> vec2;
    push_back(vec2, 'a', 'c', 'b', 'd');
    print(vec2);

    std::list<int> l;
    push_back(l, 2,3,1,0);
    print(l);
}