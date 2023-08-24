#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <utility>

#include <crypt.h>

#include "hashtable.h"
using namespace std;

class PassServer
{

public:
    PassServer(size_t size = 101);
    ~PassServer();
    bool load(const char *filename);
    bool addUser(pair<string, string> & kv);
    bool addUser(pair<string, string> && kv);
    bool removeUser(const string & k);
    bool changePassword(const pair<string, string> &p, const string & newpassword);
    bool find(const string & user);
    void dump();
    size_t size();
    bool write_to_file(const char *filename);

private:
    string encrypt(const string & str);
    char* password;
    size_t atsize;
    cop4530::HashTable<string, string>* at;
};

#include "passserver.h"
#endif