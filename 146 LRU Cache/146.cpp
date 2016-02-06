/*

Design and implement a data structure for Least Recently Used (LRU) cache. 

It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

set(key, value) - Set or insert the value if the key is not already present. 
    When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

*/

#include <list>
#include <unordered_map>
using namespace std;

class LRUCache{
public:
    LRUCache(int capacity) : capacity_(capacity) {}
    
    // Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
    int get(int key) {
        auto it = cache.find(key);
        if (it == cache.end())
            return -1;
        touch(it);
        return it->second.first;
    }

    // Set or insert the value if the key is not already present.
    // When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
    void set(int key, int value) {
        auto it = cache.find(key);
		if (it != cache.end())
		{
			touch(it);
			it->second.first = value;
		}
        else
        {
            if (cache.size() == capacity_)  // used.size() takes longer time in OJ, should both be constant time in C++11
            {
                cache.erase(used.back());   // erase by key
                used.pop_back();
            }
            used.push_front(key);
			cache[key] = make_pair(value, used.begin());  // begin() is iterator, front() is the reference to element
        }
    }

private:
    int capacity_;
    list<int> used;  // doubly-linked list of keys, to keep track of the order, front is most recently
    unordered_map<int, pair<int, list<int>::iterator>> cache;  // key, (value, iterator of used)

    void touch(unordered_map<int, pair<int, list<int>::iterator>>::iterator it) {
        used.erase(it->second.second);  // constant time, that's why we use list data structure
		used.push_front(it->first);
        it->second.second = used.begin();
    }
};