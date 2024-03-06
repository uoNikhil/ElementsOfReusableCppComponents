/**
 * Challenge: Trade Message Parser
Scenario: Your application receives trade messages from an exchange in a simple text format. 
Each message contains details about a single trade, including the symbol, price, and quantity. 
Messages are separated by newline characters, and fields within a message are separated by commas.

Example Message:
AAPL,120.50,100
MSFT,250.75,200
GOOGL,1500.10,50
Task: Write a C++ function to parse these trade messages and store them in a suitable data structure. 
Additionally, implement functionality to access the parsed data for further processing.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <string_view>

using namespace std;


struct Trade
{
    string symbol;
    double price;
    uint32_t quantity;
};



void Parse(const string_view& price_updates, std::vector<Trade>& trades)
{
    std::istringstream iss(price_updates.data());
    std::string line;

    while (getline(iss,line))
    {
        std::string token;
        std::istringstream issl(line);

        Trade trade;

        getline(issl, trade.symbol, ',');
        getline(issl,token, ',');
        trade.price = std::stod(token);
        getline(issl,token, ',');
        trade.quantity = std::stoul(token);
        trades.push_back(trade);
    }   
}

void SerializeTrades(const std::vector<Trade>& trades)
{
    std::ostringstream oss;
    for (auto trade: trades)
    {
        oss << "{" << trade.symbol << ", " << trade.price << ", " << trade.quantity << "}\n";
    }
    std::cout << oss.str();
}

int main()
{
    std::string_view price_updates = "AAPL,120.50,100\nMSFT,250.75,200\nGOOGL,1500.10,50";
    std::vector<Trade> trades;

    Parse(price_updates, trades);
    SerializeTrades(trades);
}