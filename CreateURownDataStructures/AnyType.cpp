#include <iostream> 
#include <vector>
#include <memory>

class Anytype
{
    virtual ~Anytype() = default;
    virtual void print() =0;
};

template <typename T>
class SpecificType : public Anytype
{
public:
    print()
    {
        std::cout << m_value;
    }
private:
    T m_value;
};

template <typename T>
class AnyVector
{
public:
    void printall()
    {
        for (auto& ptr:m_vec)
        {
            ptr->print();
        }
    }
    void emplace(SpecificType<T> )
    {
        m_vec.emplace(std::make_shared<>)
    }
private:
    vector<std::shared_ptr<Anytype>> m_vec;
};

int main()
{

}