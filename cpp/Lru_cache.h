#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>
#include <deque>

// @include
template<std::size_t capacity>
class Lru_cache {
public:
    bool lookup(int isbn, int& price)
    {
        auto it = _price_table.find(isbn);
        if (it == _price_table.end()) { return false; }

        price = it->second.second;
        // Since key has just been accessed, move it to the front.
        _move_to_front(isbn, it);
        return true;
    }

    void insert(int isbn, int price)
    {
        auto it = _price_table.find(isbn);
        // We add the value for key only if key is not present - we don't update
        // existing values.
        if (it != _price_table.end()) {
            // Specification says we should make isbn the most recently used.
            _move_to_front(isbn, it);
        } else {
            if (_price_table.size() == capacity) {
                // Removes the least recently used ISBN to get space.
                _price_table.erase(_lru_queue.back());
                _lru_queue.pop_back();
            }
            _lru_queue.emplace_front(isbn);
            _price_table[isbn] = {_lru_queue.begin(), price};
        }
    }

    bool erase(int isbn)
    {
        auto it = _price_table.find(isbn);
        if (it == _price_table.end()) { return false; }
        _lru_queue.erase(it->second.first);
        _price_table.erase(it);
        return true;
    }

private:
    using Table_type = std::unordered_map<int, std::pair<std::deque<int>::iterator, int>>;
    using Table_iterator = typename Table_type::iterator;

    // Forces this key-value pair to move to the front.
    void _move_to_front(int isbn, const Table_iterator& it)
    {
        _lru_queue.erase(it->second.first);
        _lru_queue.emplace_front(isbn);
        it->second.first = _lru_queue.begin();
    }

    Table_type _price_table;
    std::deque<int> _lru_queue;
};

#endif // LRU_CACHE_H
