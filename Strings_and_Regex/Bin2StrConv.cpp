/**
 * Given a range of 8-bit Interger, Array/vector
 * Return string that contains hexadecimal representation of Input Data
 * Should Have both upper and lower case data
 * 
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include <sstream> // Include for std::ostringstream
#include <iomanip> // Include for std::hex, std::setw, std::setfill
using namespace std;

template <typename Iterator>
string hex_to_str(Iterator start, Iterator end, bool upper_case = false)
{
    std::ostringstream oss;
    if (upper_case)
        oss.setf(std::ios_base::uppercase);
    while ( start != end)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*start);
        start++;
    }
    return oss.str();
}

template<class Container>
string hex_to_str(const Container& c, bool upper_case = false)
{
    return hex_to_str(std::cbegin(c), std::cend(c), upper_case);
}

int get_val_from_Char(char c)
{
    if (c>='0' && c<='9')
        return c - '0';
    if (c>='A' && c<='F')
        return c - 'A' + 10;
    if (c>='a' && c<='f')
        return c - 'a' + 10;
    return 0;
}

vector<unsigned char> string_to_hex(string str)
{
    vector<unsigned char> result;
    for (size_t i =0; i<str.size()-1;i+=2)
    {
        result.push_back(get_val_from_Char(str[i]) << 4 | get_val_from_Char(str[i+1]));
    }
    return result;
}

template <typename T>
void print(const std::vector<T>& temp) {
    std::stringstream ss;
    ss << "{ ";
    for (size_t i = 0; i < temp.size(); ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(temp[i]);
        if (i < temp.size() - 1) {
            ss << ", ";
        }
    }
    ss << " }";
    std::cout << "Vec is " << ss.str() << "\n";
}

int main()
{
    vector<unsigned char> v1{0xBA, 0xAD, 0xF0, 0x0D};
    array<unsigned char, 6> a{1,2,3,4,5,6};
    unsigned char buff[5] = {0x11,0x22,0x33,0x44,0x55};

    assert(hex_to_str(v1,true) == "BAADF00D");
    assert(hex_to_str(a,true) == "010203040506");
    assert(hex_to_str(buff,true) == "1122334455");

    assert(hex_to_str(v1) == "baadf00d");
    assert(hex_to_str(a) == "010203040506");
    assert(hex_to_str(buff) == "1122334455");

    std::vector<unsigned char> expected{0xBA,0xAD,0xF0,0x0D,0x42};
    auto temp = string_to_hex("BAADF00D42");
    print(temp);
    assert(string_to_hex("BAADF00D42") == expected);
    assert(string_to_hex("BaaDF00D42") == expected);
}

