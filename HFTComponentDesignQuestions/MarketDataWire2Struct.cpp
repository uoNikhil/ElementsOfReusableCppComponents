/**
 * Scenario Where the Structure of MarketData Received From Exchange is Fixed lenght
 * and your Internal Store is of exact same format
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdint>

#pragma pack(push,1)
struct  Trade
{
    char symbol[6];
    double price;
    int quantity;
};
#pragma pack(pop)

void print(const Trade& trade){
    std::ostringstream oss;
    oss << "{" << trade.symbol << ", " << trade.price << ", " << trade.quantity << "}\n";
    std::cout << oss.str();
}

void WireMsg2HumanReadable(char* wire_msg, size_t sz)
{
    std::ostringstream oss;
    std::string symbol(wire_msg, 6);
    double price;
    std::memcpy(&price, wire_msg + 6, sizeof(price));
    int quantity;
    std::memcpy(&quantity, wire_msg + 6+sizeof(price), sizeof(quantity));
    
    oss << "Symbol=" << symbol << "|price=" << price << "|quantity=" << quantity << "\n";
    std::cout << oss.str();
}

int main()
{
    Trade google = {"GOOGL", 100.16,160};

    //Send Trade to Wire using char buff
    char* wire_msg = reinterpret_cast<char*>(&google);

    WireMsg2HumanReadable(wire_msg, sizeof(google));

    ////Receive Trade from Wire in char buff format and convert it to Internal Format
    Trade someOtherTrade = *reinterpret_cast<Trade*>(wire_msg);
    print(someOtherTrade);

    
}


