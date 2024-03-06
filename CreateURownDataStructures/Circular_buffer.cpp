#include <iostream>
#include <vector>

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(const size_t size)
    {
        if (size==0)
        {
            std::cout << "Size cant be 0\n";
        }
        m_vec=std::vector<T>(size);
        m_empty = true;
        m_full=false;
        r_idx=0;
        w_idx=0;
    }

    size_t size() const
    {
        return m_vec.size();
    }
    bool empty() const
    {
        return m_empty;
    }
    bool full() const
    {
        return m_full;
    }

    void increment(size_t& idx)
    {
        idx = (idx+1)%m_vec.size();
    }
    void decrement(size_t& idx)
    {
        idx--;
        if(idx<0)
        {
            idx = m_vec.size() - idx;
        }
    }

    void Push(T val)
    {
        if (m_full)
        {
            increment(r_idx);
            m_vec[w_idx] = val;
            increment(w_idx);
        }   
        else{
            m_vec[w_idx] = val;
            increment(w_idx);
        }
        if(r_idx == w_idx)
            m_full = true;
        if(m_empty)
            m_empty = false;
    }

    T Read()
    {
        if(m_empty)
        {
            throw std::runtime_error("ERROR: Read from empty Buffer");
        }
        T ret_val = m_vec[r_idx];
        increment(r_idx);
        if (r_idx==w_idx)
            m_empty = true;
        if(m_full)
            m_full = false;
        return ret_val;
    }

private:
    bool m_empty;
    bool m_full;
    size_t r_idx;
    size_t w_idx;
    std::vector<T> m_vec;
};

int main()
{
    CircularBuffer<int> cb(5); // Create a CircularBuffer of size 5

    std::cout << "Initially, is empty? " << cb.empty() << std::endl;

    // Pushing elements into the buffer
    for (int i = 1; i <= 5; ++i) {
        cb.Push(i);
        std::cout << "Pushed: " << i << ", is full? " << cb.full() << std::endl;
    }

    // The buffer should be full now
    std::cout << "After pushing 5 elements, is full? " << cb.full() << std::endl;

    // Reading and printing all elements
    std::cout << "Reading elements: ";
    while (!cb.empty()) {
        std::cout << cb.Read() << " ";
    }
    std::cout << "\nAfter reading all elements, is empty? " << cb.empty() << std::endl;

    // Testing overwrite
    for (int i = 6; i <= 10; ++i) {
        cb.Push(i);
    }
    std::cout << "After pushing elements 6 to 10, buffer contents: ";
    while (!cb.empty()) {
        std::cout << cb.Read() << " ";
    }
    std::cout << std::endl;

    // Attempting to read from an empty buffer should throw an exception
    try {
        std::cout << "Attempting to read from an empty buffer: ";
        cb.Read();
    } catch (const std::runtime_error& e) {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }

    return 0;
}