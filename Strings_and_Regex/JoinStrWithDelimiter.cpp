#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>

using namespace std;

//Tokentization
std::vector<string> Tokenize(const std::string& str, const char& delimiter)
{
    std::istringstream iss(str);
    std::string token;
    std::vector<string> result;
    while(getline(iss,token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}


//Concatenation
template <typename DelimiterType>
std::string Concatenate(const std::vector<string>& vec, const DelimiterType& delimeter)
{
    if (vec.empty())
        return "";
    

    std::string delimeterStr = [&delimeter](){
        if constexpr (std::is_same<DelimiterType,char>::value)
        {
            return std::string(1,delimeter);
        }
        else
        {
            return delimeter;
        }
    }();
    return std::accumulate(
        std::next(vec.begin()),
        vec.end(),
        vec[0],
        [&delimeterStr](const string& a, const string& b){return a + delimeterStr + b;}
    );
}

int main()
{
    vector<string> vec = {"This","is","an","example"};
    char delimiter1 = ' ';
    string delimiter2 = " ";
    string expected = "This is an example";
    //assert(expected == join(vec, delimiter));
    assert(expected == Concatenate(vec, delimiter1));
    assert(expected == Concatenate(vec, delimiter2));
}