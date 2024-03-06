#include <iostream>
#include <vector>
#include <map>
#include <sstream>

class newMap
{
public:
    void insert(int key, int val){
        m_map[key] = val;
    }
    int get(int key){
        return m_map[key];
    }
    void addToKey(int x){
        for (auto& [key, val]: m_map)
        {
            int temp_key = key;
            int temp_val = val;
            m_map.erase(key);
            m_map[temp_key+x] = val;
        }
    }
    void addToValue(int y){
        for (auto& [key, val]:m_map)
        {
            int temp_key = key;
            int temp_val = val;
            m_map.erase(key);
            m_map[temp_key] = val+y;
        }
    }
    void print_map()
    {
        std::ostringstream oss;
        for (const auto& [key, val]:m_map)
        {
            oss << "[" << key << "]=" << val << "\n";
        }
        std::cout << oss.str();
    }

private:
    std::map<int, int> m_map;
};

void ProcessQuery(const std::vector<std::string>& query_type, const std::vector<std::vector<int>>& query, newMap& myMap)
{
    
    for (int i = 0; i< query_type.size(); i++)
    {
        if (query_type[i] == "insert")
        {
            myMap.insert(query[i][0],query[i][1]);
        }
        else if (query_type[i] == "get")
        {
            myMap.get(query[i][0]);
        }
        else if (query_type[i] == "addToKey")
        {
            myMap.addToKey(query[i][0]);
        }
        else if (query_type[i] == "addToValue")
        {
            myMap.addToValue(query[i][0]);
        }
        else{
            std::cout << "INVALID QURERY TYPE\n";
        }
    }
    myMap.print_map();
}


int main()
{
    std::vector<std::string> query_type;
    std::vector<std::vector<int>> query;

    query_type = {"insert","insert","addToValue","addToKey","get"};
    query = {{1,2},{2,3}, {2},{1},{3}};
    newMap myMap;

    ProcessQuery(query_type,query,myMap);
}
