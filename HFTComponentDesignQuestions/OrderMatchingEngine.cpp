/**
 * Order Matching Engine
 * Scenario: Implement a basic order matching engine for a stock exchange. 
 * Your application receives buy and sell orders in a simple text format: "BUY symbol price quantity" or "SELL symbol price quantity", each separated by newlines. 
 * Orders for each symbol are matched based on price and time priority - highest price (for buys) and lowest price (for sells) with the earliest orders being matched first. 
 * Output the details of each trade made.
*/

/**
 * Sample Input
    BUY AAPL 150.00 100
    SELL AAPL 155.00 50
    BUY MSFT 210.00 200
    SELL MSFT 215.00 150
    SELL AAPL 149.00 100
    BUY AAPL 148.00 50
    SELL MSFT 210.00 100
    BUY GOOGL 1800.00 20
    SELL GOOGL 1805.00 10
    BUY GOOGL 1795.00 30
    SELL MSFT 208.00 50
* Sample Output
    Trade executed: AAPL at $150.00 for 100 shares
    Trade executed: MSFT at $210.00 for 100 shares
    Trade executed: GOOGL at $1800.00 for 10 shares
*/


#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Trade
{
    bool side;
    string symbol;
    double price;
    uint32_t quantity;

    Trade(bool side, string symbol, double price, uint32_t quantity): side(side), symbol(symbol), price(price), quantity(quantity){}

    std::string to_str()
    {
        std::ostringstream oss;
        oss << side << "|" << symbol << "|" << price << "|" << quantity << "\n";
        return oss.str();
    }
};

ostringstream& operator<<(ostringstream& oss, Trade t)
{
    oss << t.side << "|" << t.symbol << "|" << t.price << "|" << t.quantity << "\n";
    return oss;
}

// For Buying - higher price = more priority => MAX Heap
struct BuyComparator
{
    bool operator()(const Trade& lhs,const Trade& rhs) const
    {
        return lhs.price < rhs.price;
    }
};

// For Sell - lower price = more priority => MIN Heap
struct SellComparator
{
    bool operator()(const Trade& lhs,const Trade& rhs) const
    {
        return rhs.price < lhs.price;
    }
};

void ProcessOrder(Trade& trade, map<string, priority_queue<Trade, vector<Trade>, BuyComparator>>& BuyLadder, map<string, priority_queue<Trade, vector<Trade>, SellComparator>>& SellLadder)
{
    if (trade.side) //BUY
    {
        //check if Sell Side 1)for same symbol has 2) price lower or eq to curr.price 3) Quantity Check
        auto& sell_queue = SellLadder[trade.symbol];
        if (!sell_queue.empty())
        {
            if (sell_queue.top().price <= trade.price)
            {
                //Trade must Execute
                cout << "TRADE EXECUTED\n";
                if(sell_queue.top().quantity > trade.quantity)
                {
                    auto top_trade = sell_queue.top();
                    sell_queue.pop();
                    top_trade.quantity-=trade.quantity;
                    sell_queue.push(top_trade);
                }
                else if(sell_queue.top().quantity == trade.quantity)
                {
                    sell_queue.pop();
                }
                else
                {
                    auto top_trade = sell_queue.top();
                    sell_queue.pop();
                    trade.quantity-=top_trade.quantity;
                    auto& buy_queue = BuyLadder[trade.symbol];
                    buy_queue.emplace(trade);
                }
            }
            else{
                auto& buy_queue = BuyLadder[trade.symbol];
                buy_queue.emplace(trade);
                return;
            }
        }
        else
        {
            auto& buy_queue = BuyLadder[trade.symbol];
            buy_queue.emplace(trade);
            return;
        }
    }
    else{//SELL
        auto& buy_queue = BuyLadder[trade.symbol];
        if (!buy_queue.empty())
        {    
            if (buy_queue.top().price>=trade.price)
            {
                cout << "TRADE EXECUTED\n";
                    if(buy_queue.top().quantity > trade.quantity)
                    {
                        auto top_trade = buy_queue.top();
                        buy_queue.pop();
                        top_trade.quantity-=trade.quantity;
                        buy_queue.push(top_trade);
                    }
                    else if(buy_queue.top().quantity == trade.quantity)
                    {
                        buy_queue.pop();
                    }
                    else
                    {
                        auto top_trade = buy_queue.top();
                        buy_queue.pop();
                        trade.quantity-=top_trade.quantity;
                        auto& sell_queue = SellLadder[trade.symbol];
                        sell_queue.emplace(trade);
                    }
            }
            else
            {
                auto& sell_queue = SellLadder[trade.symbol];
                sell_queue.emplace(trade);
                return;
            }
        }
        else{
            auto& sell_queue = SellLadder[trade.symbol];
                sell_queue.emplace(trade);
                return;
        }
    }
}

void print(std::string symbol, map<string, priority_queue<Trade, vector<Trade>, BuyComparator>> BuyLadder, map<string, priority_queue<Trade, vector<Trade>, SellComparator>> SellLadder)
{
    auto buy_q = BuyLadder[symbol];
    auto sell_q = SellLadder[symbol];

    std::string topS;
    std::string topB;
    if(buy_q.empty())
    {
        topB = "EMPTY";
    }
    else
    {
        Trade t =buy_q.top();
        topB = t.to_str();
    }
    if(sell_q.empty())
    {
        topS = "EMPTY";
    }
    else
    {
        Trade t =buy_q.top();
        topS =t.to_str();
    }
    cout << symbol << ": BUY Ladder : " << topB << "\n";
    cout << symbol << ": SELL Ladder : " << topS << "\n";  
}

int main()
{
    std::string trades = "BUY AAPL 150.00 100\nSELL AAPL 155.00 50\nBUY MSFT 210.00 200\nSELL MSFT 215.00 150\nSELL AAPL 149.00 100\nBUY AAPL 148.00 50\nSELL MSFT 210.00 100\nBUY GOOGL 1800.00 20\nSELL GOOGL 1805.00 10\nBUY GOOGL 1795.00 30\nSELL MSFT 208.00 50";

    map<string, priority_queue<Trade, vector<Trade>, BuyComparator>> BuyLadder;
    map<string, priority_queue<Trade, vector<Trade>, SellComparator>> SellLadder;

    string line;
    istringstream trades_stream(trades);
    while(getline(trades_stream, line))
    {
        cout << "\t\tTRADE:" << line << "\n";
        istringstream iss(line);
        string side;
        string symbol;
        double price;
        uint32_t quantity;
        iss >> side >> symbol >> price >> quantity;
        Trade trade((side=="BUY"?true:false), symbol,price,quantity);
        ProcessOrder(trade, BuyLadder, SellLadder);
        print(trade.symbol, BuyLadder,SellLadder );
    }
}


