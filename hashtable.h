#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>

#include <list>

#include <sstream>
using namespace std;


namespace cop4530{

    template <typename K, typename V>
    class HashTable
    {
    public:
        HashTable(size_t size = 101);
        ~HashTable();
        bool contains(const K & k);
        bool match(const pair<K, V> &kv) const;
        bool insert(const pair<K, V> & kv);
        bool insert (pair<K,  V> && kv);
        bool remove(const K & k);
        void clear();
        bool load(const char *filename);
        void dump();
        size_t size();
        bool write_to_file(const char *filename);


    private:
        static const unsigned int max_prime = 1301081;
        static const unsigned int default_capacity = 11;
        size_t htsize;
        size_t htssize;
        vector<list<pair<K,V>>> htable;
        void makeEmpty();
        void rehash();
        size_t myhash(const K &k) const;
        unsigned long prime_below (unsigned long) const;
        void setPrimes(vector<unsigned long>&) const;

    };
#include "hashtable.hpp"
}

#endif