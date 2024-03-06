#include "ipv4data_type.cpp"
#include <iostream>

void DisplayList(IPv4 start, IPv4 end)
{
    std::stringstream ss;
    uint32_t start_int = start.to_uint();
    uint32_t end_int = end.to_uint();
    std::cout << "start_int = " << start_int << "\n";
    std::cout << "end_int = " << end_int << "\n";
    if (start_int > end_int)
    {
        std::cout << "Start can't be greater than End\n";
        return;
    }

    uint32_t current = start_int;
    ss <<"[\n";
    while(current <= end_int)
    {
        IPv4 curr_ip(current);
        ss << "\t" << curr_ip << ",\n";
        current++;
    }
    ss << "]\n";
    std::cout << "List of IPs starting with" << start << ", ending with " << end << "\n";
    std::cout << ss.str();
}

int main()
{
    IPv4 startRange(10,190,0,0);
    IPv4 endRange(10,190,0,10);
    //std::cout << "Enter starting of the reange \n";
    //std::cin >> startRange;
    //std::cout << "Enter Ending of the reange \n";
    //std::cin >> endRange;
    
    for (IPv4 curr = startRange; curr<=endRange; curr++)
    {
        std::cout << "IP = " << curr << "\n";
    }

    return 0;
}