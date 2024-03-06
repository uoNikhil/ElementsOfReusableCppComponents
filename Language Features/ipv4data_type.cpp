/**
 * read write such addresses from or to the console
 * can be of the format 127.0.0.1 or 168.192.0.100
*/

#include <iostream>
#include <string>
#include <sstream>

struct ip_components
{
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};


class IPv4{
public:
    IPv4(){}
    IPv4(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
    {
        m_component = {a,b,c,d};
    }
    IPv4(uint32_t ip)
    {
        m_component.a = (ip >> 24) & 0xFF;
        m_component.b = (ip >> 16) & 0xFF;
        m_component.c = (ip >> 8) & 0xFF;
        m_component.d = (ip) & 0xFF;
    }

    IPv4(const IPv4& other)
    {
        this->m_component = other.m_component;
    }
    
    IPv4& operator=(const IPv4& other)
    {
        this->m_component = other.m_component;
        return *this;
    }

    //prefix Increment
    IPv4& operator++()
    {
        *this = IPv4(1+to_uint());
        return *this;
    }

    //Postfix Increment
    IPv4& operator++(int)
    {
        ++(*this);
        return *this;
    }


    IPv4& operator--()
    {
        uint32_t ip = this->to_uint();
        ip--;
        m_component.a = (ip >> 24) & 0xFF;
        m_component.b = (ip >> 16) & 0xFF;
        m_component.c = (ip >> 8) & 0xFF;
        m_component.d = (ip) & 0xFF;
        return *this;
    }

    IPv4& operator--(int)
    {
        --(*this);
        return *this;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << static_cast<int>(m_component.a) << ".";
        ss << static_cast<int>(m_component.b) << ".";
        ss << static_cast<int>(m_component.c) << ".";
        ss << static_cast<int>(m_component.d);
        return ss.str();
    }

    uint32_t to_uint()
    {
        return static_cast<uint32_t>(static_cast<uint32_t>(m_component.a << 24) | 
                static_cast<uint32_t>(m_component.b << 16) | 
                static_cast<uint32_t>(m_component.c << 8) | 
                static_cast<uint32_t>(m_component.d));
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& addr)
    {
        os << static_cast<int>(addr.m_component.a) << ".";
        os << static_cast<int>(addr.m_component.b) << ".";
        os << static_cast<int>(addr.m_component.c) << ".";
        os << static_cast<int>(addr.m_component.d);
        return os;
    } 

    friend std::istream& operator>>(std::istream& is, IPv4& addr)
    {
        char d1, d2, d3;
        int b1,b2,b3,b4;
        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if (d1 == '.' && d2 == '.' && d3 == '.')
        {
            addr = IPv4(b1,b2,b3,b4);
        }
        else
        {
            std::cout << "ERROR in collecting IP from console\n";
        }
        return is;
    }

    friend bool operator==(IPv4 first, IPv4 second)
    {
        return first.to_uint() == second.to_uint();
    }
    friend bool operator!=(IPv4 first, IPv4 second)
    {
        return !(first==second);
    }
    friend bool operator<(IPv4 first, IPv4 second)
    {
        return first.to_uint() < second.to_uint();
    }
    friend bool operator<=(IPv4 first, IPv4 second)
    {
        return first.to_uint() <= second.to_uint();
    }

    friend bool operator>(IPv4 first, IPv4 second)
    {
        return second < first;
    }
    friend bool operator>=(IPv4 first, IPv4 second)
    {
        return second <= first;
    }

private:
    ip_components m_component;
};

/*
void test_ipv4_data_type()
{
    IPv4 my_addr;
    std::cout << "Please enter the IP\n";
    std::cin >> my_addr;
    std::cout << "1) Your IP is " << my_addr.to_string() << "\n";
    std::cout << "2) Your IP is " << my_addr << "\n";

    IPv4 my_addr2(192, 207, 0,10);
    std::cout << "New IP is " << my_addr2 << "\n";
}
*/
