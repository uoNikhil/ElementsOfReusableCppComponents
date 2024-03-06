#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <cassert>

// Helper function to check if a container contains a specific element.
template<class Container, typename Arg>
bool contains(const Container& c, const Arg& arg) {
    return std::find(c.begin(), c.end(), arg) != c.end();
}

template<class Container, typename... Args>
bool contains_any(const Container& c, Args... args) {
    return (... || contains(c, args));
}

template<class Container, typename... Args>
bool contains_all(const Container& c, Args... args) {
    return (... && contains(c, args));
}

template<class Container, typename... Args>
bool contains_none(const Container& c, Args... args) {
    return (... && !contains(c, args));
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    assert(contains_any(v, 0, 3, 30)); // True, because 3 is in v

    std::array<int, 6> a{{1, 2, 3, 4, 5, 6}};
    assert(contains_all(a, 1, 3, 6)); // True, because 1, 3, and 6 are all in a

    std::list<int> l{1, 2, 3, 4, 5, 6};
    assert(!contains_none(l, 0, 6)); // False, because 6 is in l
    std::cout << "ALL TESTS PASSED\n";
}
