// *****************************************************************
// * Function Name: Hashtable
// * Description: constructor
// * Parameter Description: size - size
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
    htsize = 0;

    if(size < (max_prime + 1) && size > 0)
        htssize = size;
    else htssize = default_capacity;
    htable.resize(prime_below(htssize));
}

// *****************************************************************
// * Function Name: ~HashTable
// * Description: destructor
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
    makeEmpty();
}

// *****************************************************************
// * Function Name: contains
// * Description: check if jey j is in the hash table
// * Parameter Description: k - key
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k)
{
    auto x = myhash(k);
    if (htable[x].empty())
        return false;
    else
    {
        for (auto itr = htable[x].begin(); itr != htable[x].end(); itr++)
        {
            if (k == itr->first)
                return true;
        }
    }

    return false;
}

// *****************************************************************
// * Function Name: match
// * Description: check if key value pair is in the hash table
// * Parameter Description: kv - key
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) const
{
    auto x = myhash(kv.first);
    if (htable[x].empty())
        return false;
    else
    {
        auto itr1 = htable[x].begin();
        while (itr1 != htable[x].end())
        {
            if (kv == *itr1)
                return true;
            ++itr1;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: insert
// * Description: add the key-value pair kv into the
//                hash table
// * Parameter Description: kv - key pair
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv)
{
    if (match(kv))
        return false;
    if (htsize == htable.size())
        rehash();

    auto x = myhash(kv.first);
    if (!htable[x].empty())
    {
        auto itr = htable[x].begin();
        while(  itr != htable[x].end())
        {
            if(kv.first ==itr->first)
            {
                itr->second = kv.second;
                htsize++;
                return true;
            }
            itr++;
        }
        htable[x].push_back(kv);
        htsize++;
        return true;
    }
    else
    {
        htable[x].push_back(kv);
        htsize++;
        return true;
    }


}

// *****************************************************************
// * Function Name: insert
// * Description: move version of insert
// * Parameter Description: kv - key
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::insert (pair<K,  V> && kv)
{
    if (match(kv))
        return false;
    if (htsize == htable.size())
        rehash();

    auto x = myhash(kv.first);
    if (htable[x].empty())
    {
        htable[x].push_back(kv);
        htsize++;
        return true;
    }
    else
    {
        for (auto itr = htable[x].begin(); itr != htable[x].end(); itr++)
            if(itr->first == kv.first)
            {
                itr->second = kv.second;
                return true;
            }
        htable[x].push_back(kv);
        htsize++;
        return true;
    }
}

// *****************************************************************
// * Function Name: remove
// * Description: delete the key k and the corresponding value if it is
//                in the hash table
// * Parameter Description: k - key
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
    if(contains(k) )
    {
        auto matched = myhash(k);
        auto itr = htable[matched].begin();

        while (itr != htable[matched].end())
        {
            if (itr->first == k)
            {
                htable[matched].erase(itr);
                --htsize;
                return true;
            }
            itr++;
        }
        return true;
    }
    else
        return false;
}

// *****************************************************************
// * Function Name: clear
// * Description: delete all elements
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::clear()
{
    makeEmpty();
    htsize = 0;
}

// *****************************************************************
// * Function Name: load
// * Description:  load the content of the file with name
//                  filename into the hash tabl
// * Parameter Description: filename - file
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
    ifstream infile;
    infile.open(filename);
    if (infile.is_open())
    {
        pair <K, V> p;
        string buffer;
        K k;
        V v;
        while (infile >> buffer)
        {
            istringstream sk(buffer);
            infile >> buffer;
            istringstream sv(buffer);
            sk >> k;
            sv >> v;
            p.first = k;
            p.second = v;
            if(contains(p.first))
            {
                continue;
            }
            else
                insert(p);
        }
    }
    else
        return false;

    infile.close();
    return true;
}

// *****************************************************************
// * Function Name: dump
// * Description:   display all entries in the hash table
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::dump()
{
    for (int i = 0; i < htable.size(); i++)
    {
        if (htable[i].empty()) cout << "v[" << i << "]: " << endl;
        else
        {
            cout << "v[" << i << "]: ";

            for (auto itr1 = htable[i].begin(); itr1 != htable[i].end(); itr1++)
            {
                if (itr1 != htable[i].begin())
                    cout << " : ";
                cout << itr1->first << ' ' << itr1->second;
            }
            cout << endl;
        }
    }
}

// *****************************************************************
// * Function Name: size
// * Description:   returns size of the hash table
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
size_t HashTable<K, V>::size()
{ return htsize; }

// *****************************************************************
// * Function Name: write_to_file
// * Description: write all elements in the hash table
//                  into a file with name filename
// * Parameter Description: filename - file
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename)
{
    ofstream ofile;
    ofile.open(filename);

    if (ofile.is_open())
    {
        for (int x = 0; x < htable.size(); x++)
        {
            if (htable[x].empty())
                continue;

            auto itr = htable[x].begin();
            while (itr != htable[x].end())
            {
                ofile << itr->first << ' ' << itr->second << '\n';
                itr++;
            }
        }
        return true;
    }
    else
        return false;

}

// *****************************************************************
// * Function Name: makeEmpty
// * Description: delete all elements in the hash table
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
    for (int i = 0; i < htable.size(); i++)
    {
        if (htable[i].empty())
            continue;
        else
            htable[i].clear();
    }
}

// *****************************************************************
// * Function Name: rehash
// * Description: Called when the number of elements in the
//                  hash table is greater than the size of the vector
// * Parameter Description: -
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::rehash()
{

    htable.resize(prime_below(htssize * 2 ));

}

// *****************************************************************
// * Function Name: myhash
// * Description: return the index of the vector entry where k should
//                  be stored
// * Parameter Description: k - for the index
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
    hash<K> hf;
    return hf(k) % htable.size();
}

// *****************************************************************
// * Function Name: prime_below
// * Description: returns largest prime number <= n or zero if input is too large
// * Parameter Description: n - size
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n) const
{
    if (n > max_prime)
    {
        cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime)
    {
        return max_prime;
    }
    if (n <= 1)
    {
        cerr << "** input too small \n";
        return 0;
    }


    vector <unsigned long> v (n+1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

// *****************************************************************
// * Function Name: setPrimes
// * Description: Sets all prime number indexes to 1
// * Parameter Description: vprimes
// * Date: 11/13/2020
// * Author: Raul Rodriguez
// * Referenes: -
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes) const
{
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for( i = 2; i*i < n; ++i)
    {
        if (vprimes[i] == 1)
            for(j = i + i ; j < n; j += i)
                vprimes[j] = 0;
    }
}