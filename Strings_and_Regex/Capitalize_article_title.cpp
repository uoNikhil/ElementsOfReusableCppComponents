#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

std::string capitalizer(const std::string& input)
{
    ostringstream oss;
    bool capitalizeNext = true;
    for (char c : input)
    {
        if (capitalizeNext && ((c>='A' && c<='Z') || (c>='a' && c<='z')))
        {
            c-= 'a' - 'A';
            capitalizeNext = false;
        }
        if (c == ' ')
        {
            capitalizeNext = true;
        }
        oss << c;
    }
    return oss.str();
}

int main()
{
    string input = "the c++ challenger";
    string expected_output = "The C++ Challenger";
    assert(expected_output == capitalizer(input));
}