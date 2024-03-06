/**
 * Data transmitted over networks is in big-endian format, but many computer systems use little-endian format for memory storage.
 * In a little-endian system, 
 *      the least significant byte (LSB) is stored first. 
 *      Therefore, the number 1 in memory would be stored as 01 00 00 00
 * In a Big-endian system
 *      the most significant byte (MSB) is stored first.
        int 1 = 00 00 00 01.
 * 
*/
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include <iomanip>


uint16_t ntohs(uint16_t value) {
    if (htonl(1) != 1) {
        //System is little-endian swap high and low
        return (value >> 8) | (value << 8);
    } else {
        // System is big-endian
        return value;
    }
}
//FOR uint64_t
uint64_t ntohll(uint64_t value) {
    if (htonl(1) != 1) {
        uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
        uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));
        return (static_cast<uint64_t>(low_part) << 32) | high_part;
    } else {
        return value;
    }
}

int main()
{
    // Test ntohs
    uint16_t testNtohs = ntohs(0x1234);
    std::cout << "ntohs(0x1234) = 0x" << std::hex << std::setw(4) << std::setfill('0') << testNtohs << std::endl;

    // Test ntohll
    uint64_t testNtohll = ntohll(0x123456789ABCDEF0);
    std::cout << "ntohll(0x123456789ABCDEF0) = 0x" << std::hex << std::setw(16) << std::setfill('0') << testNtohll << std::endl;
}

