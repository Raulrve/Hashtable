#include "passserver.h"

// *****************************************************************
// * Function Name: PassServer
// * Description:  constructor
// * Parameter Description: size - size
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
PassServer::PassServer(size_t size )
{
    at = new cop4530::HashTable < string, string> (size);
    atsize = 0;
    password = 0;
}

// *****************************************************************
// * Function Name: ~Passserver
// * Description: desdtructor
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
PassServer::~PassServer()
{
    if (password != 0)
        delete password;
    delete at;
}

// *****************************************************************
// * Function Name: Load
// * Description: load a password file into the
//                  HashTable object
// * Parameter Description: filename - file
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::load(const char *filename)
{ return at->load(filename); }

// *****************************************************************
// * Function Name: assUser
// * Description: add a new username and
//                 password
// * Parameter Description: kv - username and password
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::addUser(pair<string,  string> & kv)
{
    if (at->contains (kv.first))
        return false;
    ++atsize;
    return (at->insert(make_pair(kv.first, encrypt(kv.second))));
}

// *****************************************************************
// * Function Name: assUser
// * Description: move version of addUser
// * Parameter Description: kv - username and password
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::addUser(pair<string, string> && kv)
{
    if (at->contains(kv.first))
        return false;

    return at->insert(make_pair(move(kv.first), encrypt(move(kv.second))));
    ++atsize;

}

// *****************************************************************
// * Function Name: removeUser
// * Description: delete an existing user with username k
// * Parameter Description: k - username
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::removeUser(const string & k)
{
    return at->remove(k);
    --atsize;
}


// *****************************************************************
// * Function Name: changePassword
// * Description: change user password
// * Parameter Description: p, username and password
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{

    if (at->match( make_pair(p.first, encrypt(p.second))))
    {
        if (encrypt(newpassword) == encrypt(p.second))
            return false;

        at->insert(make_pair(p.first, encrypt(newpassword)));
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name: find
// * Description: check if username exist
// * Parameter Description: user - username
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::find(const string & user)
{ return at->contains(user); }


// *****************************************************************
// * Function Name: dump
// * Description: show the structure and contents of the HashTable object to
//                  the screen
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
void PassServer::dump()
{ at->dump(); }

// *****************************************************************
// * Function Name: size
// * Description: returns size
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
size_t PassServer::size()
{
    return at->size();
}

// *****************************************************************
// * Function Name: write_to_file
// * Description: save the username and password combination into a file
// * Parameter Description: filename - file
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
bool PassServer::write_to_file(const char *filename)
{ return (at->write_to_file(filename)); }

// *****************************************************************
// * Function Name: encrypt
// * Description: encrypts parameter str and return the encrypted string
// * Parameter Description: str - string to be enctrypted
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
string PassServer::encrypt(const string & str) {
    if (password != 0)
        delete password;

    char salt[] = "$1$########";
    password = new char[40];
    string k = str;

    strcpy(password, crypt(k.c_str(), salt));
    string result(password);

    return result;
}