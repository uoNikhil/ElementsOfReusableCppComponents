/**
 * Market Data Aggregator
 * Scenario: Your application subscribes to a feed of market data for multiple securities. 
 * Each data point contains the security symbol, the last traded price, and the total traded volume, separated by commas. 
 * The feed is a continuous stream of data points where data for each security can appear at any time. 
 * Your task is to aggregate this stream to maintain the latest price and total volume for each symbol.
 * 
*/

/**
 * Input Format 1 : String
 * std::string inputData = 
    "AAPL,150.50,100\n"
    "MSFT,250.75,200\n"
    "GOOGL,2725.50,150\n"
    "AAPL,151.00,50\n"
    "MSFT,251.00,100\n"
    "AAPL,150.75,100";

  *Input Format 2: Char buffer
    char inputData[] = 
    "AAPL,150.50,100\n"
    "MSFT,250.75,200\n"
    "GOOGL,2725.50,150\n"
    "AAPL,151.00,50\n"
    "MSFT,251.00,100\n"
    "AAPL,150.75,100";

  *Input Format 3: Byte Data or Binary Format
    Symbol: Fixed-length string (e.g., 5 bytes for stock symbols). Symbols shorter than the fixed length could be padded with null characters or spaces.
    Price: Floating-point number (e.g., 4 or 8 bytes, depending on whether it's a float or double).
    Volume: Integer (e.g., 4 bytes for an int).
    char binaryData[] = {
    // AAPL,150.50,100
    0x41, 0x41, 0x50, 0x4C, 0x20, // AAPL
    0x40, 0x05, 0xEC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD, // 150.50 in double
    0x00, 0x00, 0x00, 0x64, // 100 in int

    // MSFT,250.75,200
    0x4D, 0x53, 0x46, 0x54, 0x20, // MSFT
    0x40, 0x6F, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, // 250.75 in double
    0x00, 0x00, 0x00, 0xC8, // 200 in int

    // GOOGL,2725.50,150
    0x47, 0x4F, 0x4F, 0x47, 0x4C, // GOOGL
    0x40, 0x2A, 0xF1, 0xA0, 0x00, 0x00, 0x00, 0x00, // 2725.50 in double
    0x00, 0x00, 0x00, 0x96, // 150 in int

    // AAPL,151.00,50
    0x41, 0x41, 0x50, 0x4C, 0x20, // AAPL
    0x40, 0x05, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, // 151.00 in double
    0x00, 0x00, 0x00, 0x32, // 50 in int

    // MSFT,251.00,100
    0x4D, 0x53, 0x46, 0x54, 0x20, // MSFT
    0x40, 0x6F, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, // 251.00 in double
    0x00, 0x00, 0x00, 0x64, // 100 in int

    // AAPL,150.75,100
    0x41, 0x41, 0x50, 0x4C, 0x20, // AAPL
    0x40, 0x05, 0xEB, 0x85, 0x1E, 0xB8, 0x51, 0xEC, // 150.75 in double
    0x00, 0x00, 0x00, 0x64, // 100 in int
};

*/

#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <map>
#include <cstring>
#include <cassert>


struct Trade
{
    char symbol[6];
    double price;
    int quantity;
};

//Covers both Cases 1 and Case 2
template<typename Input>
void ParseFromString(const Input& inputData, std::map<std::string, Trade>& MarketData)
{
    std::istringstream iss(inputData);
    std::string line;
    while(getline(iss, line))
    {
        std::string token;
        const char delimiter = ',';
        std::istringstream issl(line);
        Trade trade;

        std::getline(issl, token, delimiter); // GET SYM - char symbol[6]
        std::fill_n(trade.symbol, sizeof(trade.symbol)-1, ' '); // six spaces becuase 5 bytes for the symbol (ASCII encoding, padded with spaces if necessary)
        trade.symbol[sizeof(trade.symbol)-1] = '\0'; // // Null-terminate the string
        strncpy(trade.symbol, token.c_str(), std::min(token.size(), sizeof(trade.symbol)-1));//// Copy the symbol from the token, ensuring not to overwrite the null terminator
        
        std::getline(issl, token, delimiter); // GET price - double price;
            trade.price = std::stod(token);
        std::getline(issl, token, delimiter); // GET quantity - int quantity;
            trade.quantity = std::stoi(token);

        auto& existing_trade = MarketData[std::string(trade.symbol)];
        strncpy(existing_trade.symbol,trade.symbol, sizeof(trade.symbol));
        existing_trade.price = trade.price;
        existing_trade.quantity+=trade.quantity;
    }
}

//Covers Case 3
void ParseFromByteData(const unsigned char* input_buff,const size_t input_buff_size, std::map<std::string, Trade>& MarketData)
{
    size_t start = 0;
    while(start < input_buff_size)
    {
        Trade trade;
        memcpy(trade.symbol, input_buff+start, sizeof(trade.symbol)-1);
        trade.symbol[sizeof(trade.symbol)-1] = '\0';
        start+=sizeof(trade.symbol)-1;
        memcpy(&trade.price,input_buff+start,sizeof(trade.price));
        start+=sizeof(trade.price);
        memcpy(&trade.quantity,input_buff+start,sizeof(trade.quantity));
        start+=sizeof(trade.quantity);

        auto& existing_trade = MarketData[std::string(trade.symbol)];
        strncpy(existing_trade.symbol, trade.symbol, sizeof(trade.symbol));
        existing_trade.price = trade.price;
        existing_trade.quantity+= trade.quantity;
    }
}


std::string Print(const std::map<std::string,Trade>& MarketData)
{
    std::stringstream oss;
    for (const auto& [symbol,stock]: MarketData)
    {
        oss << "{ " << std::string(stock.symbol) << ", " << stock.price << ", " << stock.quantity << "}\n";
    }
    //std::cout << oss.str();
    return oss.str();
}


int main()
{
    std::map<std::string, Trade> MarketData;

    std::string inputData_case1 = 
    "AAPL,150.50,100\n"
    "MSFT,250.75,200\n"
    "GOOGL,2725.50,150\n"
    "AAPL,151.00,50\n"
    "MSFT,251.00,100\n"
    "AAPL,150.75,100";

    ParseFromString(inputData_case1, MarketData);
    std::string op = Print(MarketData);
    assert(op == "{ AAPL , 150.75, 250}\n{ GOOGL, 2725.5, 150}\n{ MSFT , 251, 300}\n");
    MarketData.clear();
    op.clear();


    char inputData_case2[] = 
    "AAPL,150.50,100\n"
    "MSFT,250.75,200\n"
    "GOOGL,2725.50,150\n"
    "AAPL,151.00,50\n"
    "MSFT,251.00,100\n"
    "AAPL,150.75,100";
    ParseFromString(inputData_case2, MarketData);
    op = Print(MarketData);
    assert(op == "{ AAPL , 150.75, 250}\n{ GOOGL, 2725.5, 150}\n{ MSFT , 251, 300}\n");
    MarketData.clear();


    //CASE 3 : Byte Data
    unsigned char binaryData[] = {
        0x41, 0x41, 0x50, 0x4C, 0x20,
        0x40, 0x05, 0xEC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD,
        0x00, 0x00, 0x00, 0x64,
        0x4D, 0x53, 0x46, 0x54, 0x20,
        0x40, 0x6F, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xC8,
        0x47, 0x4F, 0x4F, 0x47, 0x4C,
        0x40, 0x2A, 0xF1, 0xA0, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x96,
        0x41, 0x41, 0x50, 0x4C, 0x20,
        0x40, 0x05, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x32,
        0x4D, 0x53, 0x46, 0x54, 0x20,
        0x40, 0x6F, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x64,
        0x41, 0x41, 0x50, 0x4C, 0x20,
        0x40, 0x05, 0xEB, 0x85, 0x1E, 0xB8, 0x51, 0xEC,
        0x00, 0x00, 0x00, 0x64
    };

    ParseFromByteData(binaryData,sizeof(binaryData), MarketData);
    op = Print(MarketData);
}