// Example program
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache
{
private:
    list<int>items;
    unordered_map <int, pair<int, typename list<int>::iterator>> keyValuesMap; //(key: (value, node_in_list))
    int csize;

public:
    LRUCache(int s) :csize(s) {
        if (csize < 1)
            csize = 10;
    }

    void set(const int key, const int value) {
        auto pos = keyValuesMap.find(key);
        if (pos == keyValuesMap.end()) {
            items.push_front(key);
            keyValuesMap[key] = { value, items.begin() };
            if (keyValuesMap.size() > csize) {
                keyValuesMap.erase(items.back());
                items.pop_back();
            }
        }
        else {
            items.erase(pos->second.second);
            items.push_front(key);
            keyValuesMap[key] = { value, items.begin() };
        }
    }

    bool get(const int key, int &value) {
        auto pos = keyValuesMap.find(key);
        if (pos == keyValuesMap.end()) {
            value = -1;
            return false;
        }
        items.erase(pos->second.second);
        items.push_front(key);
        keyValuesMap[key] = { pos->second.first, items.begin() };
        value = pos->second.first;
        return true;
    }
};

int main()
{
    // Let’s say we have a LRU cache of capacity 2.
    LRUCache cache(2);
    int value = 0;
    cache.set(1, 10); // it will store a key (1) with value 10 in the cache.
    cache.set(2, 20); // it will store a key (1) with value 10 in the cache.
    
    cache.get(1, value); // returns 10
    cout << "key : 1 value: " << value << " " << endl; 
    
    cache.set(3, 30); // evicts key 2 and store a key (3) with value 30 in the cache.
    
    cache.get(2, value); // returns -1 (not found)
    cout << "key : 2 value: " << value << " " << endl; 
    
    cache.set(4, 40); // evicts key 1 and store a key (4) with value 40 in the cache.
    
    cache.get(1, value); // returns -1 (not found)
    cout << "key : 1 value: " << value << " " << endl; 
    cache.get(3, value); // returns 30
    cout << "key : 3 value: " << value << " " << endl; 
    cache.get(4, value); // returns 40
    cout << "key : 1 value: " << value << " " << endl; 
}
