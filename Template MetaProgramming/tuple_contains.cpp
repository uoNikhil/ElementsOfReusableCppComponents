#include <vector>
using namespace std;


template<typename... Args>
struct unique<vector<>, vector<Args... args>>
{

};

vector<int> func(vector<int> ip, vector<int> op)
{
    if (ip.empty())
        return op;
    op.emplace_back(ip[0]);
    for (int i = 1; i < ip.size();i++)
    {
        if (ip[i] != ip[i-1])
            op.emplace_back(op[i]);
    }
}

int main()
{

    //static_assert()
}