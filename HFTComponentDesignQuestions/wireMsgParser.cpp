#include <sstream>
#include <iostream>
#include <string>

using namespace std;

struct FixMessage
{
    string Account;     // Tag - 1
    string ClOrdID;     // TAG - 11
    uint64_t MsgSeqNum; // Tag - 34
    uint32_t OrderQty;  // Tag - 38
    double Price;       // Tag - 44
    string SenderCompID;// Tag - 49
    string Symbol;      // TAG - 55
    bool Side;          // Tag - 54
    string TargetCompId;// Tag - 56
    
    void print()
    {
        ostringstream oss;
        oss << "Account = " << Account
            << ",ClOrdID = " << ClOrdID
            << ",MsgSeqNum = " << MsgSeqNum
            << ",OrderQty = " << OrderQty
            << ",Price = " << Price
            << ",SenderCompID = " << SenderCompID
            << ",Symbol = " << Symbol
            << ",Side = " << Side
            << ",TargetCompId = " << TargetCompId;
        cout << "FIX Message: " << oss.str() << "\n";
    }
};

void Parse(FixMessage& fix_msg, const char* buff)
{
    istringstream iss(buff);
    std::string token;
    while(std::getline(iss,token,'|'))
    {
        auto pos = token.find('=');
        if(pos==std::string::npos)
        {
            cout << "ERROR\n";
            return;
        }
        
        int tag = std::stoi(token.substr(0, pos));
        string value = token.substr(pos+1);
        switch (tag)
        {
            case 1:
                fix_msg.Account = value;
                break;
            case 11:
                fix_msg.ClOrdID = value;
                break;
            case 34:
                fix_msg.MsgSeqNum = std::stoull(value);
                break;
            case 38:
                fix_msg.OrderQty = std::stoul(value);
                break;
            case 44:
                fix_msg.Price = std::stod(value);
                break;
            case 49:
                fix_msg.SenderCompID = value;
                break;
            case 56:
                fix_msg.TargetCompId = value;
                break;
            case 55:
                fix_msg.Symbol = value;
                break;
            case 54:
                fix_msg.Side = value=="0"?false:true;
                break;
            default:
                cout << "Error: Unknown Tag Detected\n";
                return;
        }
    }
}

int main()
{
    
    char buff1[] = "1=Account1|11=ABC123|34=1|38=100|44=123.45|49=SENDER1|55=XYZ|54=1|56=TARGET|";
    char buff2[] = "1=Account1|11=QMWENBocivj3213|34=2|38=10|44=123|49=SENDER1|55=AVC|54=2|56=TARGET|";
    char buff3[] = "1=Account2|11=UOQHWEnxc3252f1|34=3|38=200|44=13.45|49=SENDER2|55=KPL|54=1|56=TARGET|";
    char buff4[] = "1=Account3|11=OIUJONhdafj2342|34=4|38=140|44=0.12345|49=SENDER2|55=TGH|54=2|56=TARGET|";
    FixMessage my_msg;
    Parse(my_msg, buff1);
    my_msg.print();
    Parse(my_msg, buff2);
    my_msg.print();
    Parse(my_msg, buff3);
    my_msg.print();
    Parse(my_msg, buff4);
    my_msg.print();
}

