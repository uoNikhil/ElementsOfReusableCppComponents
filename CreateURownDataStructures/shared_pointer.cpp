#include <iostream>


template <typename T>
class shared_ptr
{
public:
    shared_ptr(T* ptr = nullptr): m_ptr(ptr), m_ref_count(new uint64_t(1))
    {
        if (ptr == nullptr)
            *m_ref_count = 0;
    }

    shared_ptr(const shared_ptr& ptr)
    {
        m_ptr = ptr.m_ptr;
        m_ref_count = ptr.m_ref_count;
        if (m_ptr)
            (*m_ref_count)++;
    }
    shared_ptr& operator=(const shared_ptr& ptr)
    {
        if (&ptr!=this)
        {
            if (m_ptr && --(*m_ref_count)==0)
            {
                delete m_ptr;
                delete m_ref_count;
            } 


            m_ptr = ptr.m_ptr;
            m_ref_count = ptr.m_ref_count;
            (*m_ref_count)++;
        }
        return *this;
    }

    shared_ptr(shared_ptr&& rhs)
    {
        m_ptr = rhs.m_ptr;
        m_ref_count = rhs.m_ref_count;
        rhs.m_ptr = nullptr;
        rhs.m_ref_count = nullptr;
    }


    shared_ptr& operator=(shared_ptr&& rhs)
    {
        if (&rhs!=this)
        {
            if (m_ptr && --(*m_ref_count)==0)
            {
                delete m_ptr;
                delete m_ref_count;
            } 

            m_ptr = rhs.m_ptr;
            m_ref_count = rhs.m_ref_count;

            rhs.m_ptr = nullptr;
            rhs.m_ref_count = nullptr;
        }
        return *this;
    }

    ~shared_ptr()
    {
        std::cout << "DTor of Shared Ptr |  *m_ref_count =" << *m_ref_count << std::endl;
        if (m_ptr && --(*m_ref_count)==0)
        {
            delete m_ptr;
            delete m_ref_count;
        } 
    }

    T operator*()
    {
        return *m_ptr;    
    }
    T* operator->()
    {
        return m_ptr;    
    }

    uint64_t getRefCount()
    {
        return *m_ref_count;
    }

private:
    T* m_ptr;
    uint64_t *m_ref_count;
};


int main()
{
    //shared_ptr ptr1(new int(10)); // ref count 1
    //shared_ptr ptr2 = ptr1;         // ref count ptr2 = ref count of ptr1 = ref count of ptr1 ++

    shared_ptr<int> ptr1();
    shared_ptr<int> ptr2(new int(10));

    shared_ptr<int> ptr3 = ptr2;
    std::cout << "ptr3 ref count = " << ptr3.getRefCount() << "\n";

    shared_ptr<int> ptr4 = std::move(ptr2);
    std::cout << "ptr4 ref count = " << ptr4.getRefCount() << "\n";

}