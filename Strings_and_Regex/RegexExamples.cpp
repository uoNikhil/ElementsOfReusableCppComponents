#include <iostream>
#include <regex>
#include <string>
#include <cassert>
#include <optional>


// License Format could be LLL-LL DDD, LLL-LL DDDD
// L = A to Z upper case
// D is a Digit 0-9
bool License_plate_validation(std::string_view str)
{
    std::regex pattern(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
    return std::regex_match(str.data(), pattern);
}


/**
 * https://www.example.com:8080/path/to/resource?query1=value1&query2=value2#section1
 * Protocol: https
 * Domain: www.example.com
 * Port: 8080
 * Path: /path/to/resource
 * Query: query1=value1&query2=value2
 * Fragment: section1
*/
struct url_components
{
    std::string protocol;
    std::string domain;
    std::optional<int> port;
    std::optional<std::string> path;
    std::optional<std::string> query;
    std::optional<std::string> fragment;
};

std::optional<url_components> url_parser(std::string url)
{
    std::regex pattern(R"(^(https?):\/\/(www\.[a-zA-Z0-9.-]+\.[a-z]+)(?::(\d+))?(\/[^?#]*)?(?:\?([^#]*))?(?:#(.*))?$)");
    std::smatch matches;
    
    if (std::regex_match(url, matches,pattern))
    {
        url_components components;
        if (matches[1].matched && matches[2].matched)
        {
            components.protocol = matches[1].str();
            components.domain = matches[2].str();
            if (matches[3].matched)
                components.port = std::stoi(matches[3].str());
            if (matches[4].matched)
                components.path = matches[4].str();
            if (matches[5].matched)
                components.query = matches[5].str();
            if (matches[6].matched)
                components.fragment = matches[6].str();

            return components;
        }
        else
        {
            std::cout << "Invalid Protocol or Domain\n";
            return {};
        }
    }
    else
    {
        std::cout << "Invalid URL\n";
        return {};
    }
}


/**
 * Given dates in dd.mm.yyyy or dd-mm-yyyy format
 * convert to yyyy-mm-dd format
*/
std::string transform_date(std::string date_str)
{
    std::regex pattern1(R"(^([0-9]{2})\.([0-9]{2})\.([0-9]{4})$)");
    std::regex pattern2(R"(^([0-9]{2})-([0-9]{2})-([0-9]{4})$)");
    std::smatch matched;
    
    if (std::regex_match(date_str,matched,pattern1))
    {
        return std::regex_replace(date_str,pattern1,"$3-$2-$1");
    }
    else if (std::regex_match(date_str,matched,pattern2))
    {
        return std::regex_replace(date_str,pattern2,"$3-$2-$1");
    }
    else
    {
        std::cout << "Invalid Date format\n";
        return "";
    }
}

int main()
{
    assert(License_plate_validation("ABC-DE 123"));
    assert(License_plate_validation("ABC-DE 1234"));
    assert(!License_plate_validation("ABC-DE 12345"));
    assert(!License_plate_validation("abc-de 123"));
    std::cout << "Licence-plate-validation : ALL TEST CASES PASSED\n";

    std::optional<url_components> p1 = url_parser("https://www.google.com");
    assert(p1.has_value());
    assert(p1->protocol == "https");
    assert(p1->domain == "www.google.com");
    assert(!p1->port.has_value());
    assert(!p1->path.has_value());
    assert(!p1->query.has_value());
    assert(!p1->fragment.has_value());
    std::cout << "url-parser : ALL TEST CASES PASSED\n";
    
    using namespace std::string_literals; // Required for the "s" suffix
    assert(transform_date("01.12.2020"s) == "2020-12-01");
    std::cout << "date-transformation : ALL TEST CASES PASSED\n";
}