/***
Challenge 3: Real-time Risk Management System
Scenario: Design a real-time risk management system that monitors open positions and calculates potential exposure. 
Your application receives trade execution messages in the format: 
"EXECUTE symbol quantity price". 
Calculate and display the total exposure (sum of the product of quantity and price) per symbol and overall, 
updating in real-time with each new trade.

SAMPLE INPUT
EXECUTE AAPL 100 150.00
EXECUTE MSFT 200 210.00
EXECUTE GOOGL 50 1800.00
EXECUTE AAPL 150 148.00
EXECUTE MSFT 100 215.00
EXECUTE GOOGL 100 1785.00
EXECUTE AAPL 50 152.00


EXPECTED OUTPUT
After trade 1 - AAPL Exposure: 15000.00, Total Exposure: 15000.00
After trade 2 - MSFT Exposure: 42000.00, Total Exposure: 57000.00
After trade 3 - GOOGL Exposure: 90000.00, Total Exposure: 147000.00
After trade 4 - AAPL Exposure: 37200.00, Total Exposure: 184200.00
After trade 5 - MSFT Exposure: 63500.00, Total Exposure: 247700.00
After trade 6 - GOOGL Exposure: 268500.00, Total Exposure: 516200.00
After trade 7 - AAPL Exposure: 44500.00, Total Exposure: 560700.00

*/

#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

struct Trade
{
    std::string symbol;
    uint32_t qty;
    float price;

    Trade(std::string symbol,uint32_t qty,float price):symbol(symbol), qty(qty), price(price){}
};

void ProcessTrade(const Trade& trade, std::map<std::string, float>& exposure_map)
{
    auto& exposure = exposure_map[trade.symbol];
    exposure+=trade.qty*trade.price;
}

float getTotalExposure(const std::map<std::string, float>& exposure_map)
{
    float total_expo = 0.0;
    for (const auto [key,val] : exposure_map)
    {
        total_expo += val;
    }
    return total_expo;
}

void PrintRiskExposure(const Trade& trade, const std::map<std::string, float>& exposure_map, size_t trade_seq_num)
{
    //SAMPLE O/P :After trade 1 - AAPL Exposure: 15000.00, Total Exposure: 15000.00
    std::ostringstream oss;
    oss << "After trade " << trade_seq_num << " - " << trade.symbol << " Exposure: " << exposure_map.at(trade.symbol) << ", Total Exposure: " << getTotalExposure(exposure_map) << "\n"; 
    std::cout << oss.str();
}

int main()
{
    std::string Input_str = "EXECUTE AAPL 100 150.00\nEXECUTE MSFT 200 210.00\nEXECUTE GOOGL 50 1800.00\nEXECUTE AAPL 150 148.00\nEXECUTE MSFT 100 215.00\nEXECUTE GOOGL 100 1785.00\nEXECUTE AAPL 50 152.00";
    std::istringstream Input_stream(Input_str);
    std::map<std::string, float> exposure_map;

    string line;
    size_t trade_seq_num = 0;
    while (getline(Input_stream, line))
    {
        // SAMPLE LINE WOULD be : EXECUTE AAPL 100 150.00
        trade_seq_num++;
        std::string token;
        std::istringstream iss_line(line);
        getline(iss_line, token, ' ');
        getline(iss_line, token, ' ');
        std::string symbol = token;
        getline(iss_line, token, ' ');
        uint32_t qty = std::stoul(token);
        getline(iss_line, token, ' ');
        float price = std::stof(token);
        Trade trade(symbol,qty,price);
        ProcessTrade(trade,exposure_map);
        PrintRiskExposure(trade,exposure_map,trade_seq_num);
    }
    
}