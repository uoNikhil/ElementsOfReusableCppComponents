#include <iostream>
#include <thread>
#include <utility>

class Scoped_thread
{
public:
    template<typename... Args>    
    explicit Scoped_thread(Args&&... args):m_thread(std::forward<Args> (args)...){
        if(!m_thread.joinable())
        {
            throw std::logic_error("Failed to create Joinable Thread");
        }
    }
    ~Scoped_thread() {
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }
    Scoped_thread(Scoped_thread& t) = delete;
    Scoped_thread& operator=(Scoped_thread& t) = delete;
private:
    std::thread m_thread;
};

void printFunc()
{
    std::cout << "JUST a work function \n";
}

int main()
{
    Scoped_thread t(printFunc);
}
