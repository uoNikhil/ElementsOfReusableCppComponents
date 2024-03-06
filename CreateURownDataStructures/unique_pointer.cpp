#include <iostream>
#include <string>

template<typename T, typename U>
struct SampleObject
{
    T x;
    U y;
    SampleObject(T x1, U y1):x(x1), y(y1){}
};

template<typename T>
class unique_ptr
{
public:
    unique_ptr(T* ptr = nullptr): m_ptr(ptr){}
    ~unique_ptr()
    {
        delete m_ptr;
    }

    unique_ptr(const unique_ptr& lhs) = delete;
    unique_ptr& operator=(const unique_ptr& lhs) = delete;

    unique_ptr(unique_ptr&& rhs)
    {
        rhs.m_ptr = m_ptr;
        rhs.m_ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& rhs)
    {
        if (&rhs!= this)
        {
            rhs.m_ptr = m_ptr;
            rhs.m_ptr = nullptr;
        }
        return *this;
    }

    T* operator->()
    {
        return m_ptr;
    }

    T operator*()
    {
        return *m_ptr;
    }

private:
    T* m_ptr;
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main()
{
    // // unique_ptr<T> ptr();
    // unique_ptr<T> ptr(new int(10));
    // unique_ptr<T> ptr = make_shared<T>();

    unique_ptr<int> ptr1();
    unique_ptr<int> ptr2(new int(10));
    std::cout << "ptr2 val = " << *ptr2 << std::endl;
    unique_ptr<SampleObject<bool, std::string>> ptr3 = make_unique<SampleObject<bool, std::string>>(false, "name");
    std::cout << "ptr3  X val = " << ptr3->x << ", Y val = " << ptr3->y << std::endl;
}