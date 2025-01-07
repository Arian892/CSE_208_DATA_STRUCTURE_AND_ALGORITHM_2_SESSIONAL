#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

string arr[10001];

bool isPrime(int a)
{
    if (a <= 1)
        return false;

    if (a == 2)
        return true;

    for (int i = 2; i <= sqrt(a) + 1; i++)
    {
        if (a % i == 0)
            return false;
    }
    return true;
}

string randomWordGenerator()
{

    int wordLength = rand() % 6 + 5;

    string randomWord;
    for (int i = 0; i < wordLength; ++i)
    {

        char randomChar = 'a' + rand() % 26;
        randomWord.push_back(randomChar);
    }

    return randomWord;
}

int nearestPrime(int size)
{
    if (isPrime(size))
        return size;
    return nearestPrime(size + 1);
}

unsigned int hashFunction(string &str)
{
    unsigned int hash = 0;

    for (char c : str)
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

unsigned int hashFunction2(string &str)
{
    const int prime = 37;
    unsigned int key = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        key = key * prime + static_cast<unsigned int>(str[i]);
    }

    return key;
}

class element
{
public:
    string key;
    int value;
    element *next;
    bool isDeleted;
    element(string key, int value)
    {
        this->key = key;
        this->value = value;
        next = NULL;
        isDeleted = false;
    }
    void print()
    {
        cout << "(" << key << " " << value << ")";
    }
};

class HashTable
{
    int maxSize;
    vector<element *> hashelement;
    int totalcolission;
    int INSERT, DELETE;
    int chainLengthLimit;
    int initialSize;
    int totalProbe;
    int currentSize;

public:
    HashTable(int size)
    {
        maxSize = nearestPrime(size);
        initialSize = maxSize;
        hashelement.resize(maxSize, nullptr);
        totalcolission = 0;
        INSERT = 0;
        DELETE = 0;
        chainLengthLimit = 8;
        totalProbe = 0;
        currentSize = 0;
    }

    int calculateMaxChainLength()
    {
        int maxChainLength = 0;

        for (int i = 0; i < maxSize; ++i)
        {
            int chainLength = 0;
            element *current = hashelement[i];

            while (current != nullptr)
            {
                chainLength++;
                current = current->next;
            }

            if (chainLength > maxChainLength)
                maxChainLength = chainLength;
        }

        return maxChainLength;
    }

    void insert(string key, int value)
    {
        if (INSERT == 100)
            rehashingInsert();

        // cout <<  "insert " << INSERT << endl;
        // cout << "maxsize " << maxSize << endl;
        int index = hashFunction(key) % maxSize;

        if (find(key) != nullptr)
            return;

        element *temp = new element(key, value);

        // cout << "hash index " << index << endl;
        if (hashelement[index] == nullptr)
            hashelement[index] = temp;

        else
        {
            totalcolission++;
            temp->next = hashelement[index];
            hashelement[index] = temp;
        }
        INSERT++;
        currentSize++;
    }

    void rehashingInsert()
    {

        INSERT = 0;
        // cout << "maximum chain length" << calculateMaxChainLength() << endl ;
        if (calculateMaxChainLength() < chainLengthLimit)
            return;
        // cout << "rehashing" << endl;

        // vector<element*> temp = hashelement ;
        // cout << "temp size " << temp.size() << endl ;

        cout << "BEFORE REHASHING" << endl; 
        cout << "Average probe count" << randomSearch(maxSize) << endl ;
        cout << "load factor " << currentSize*1.0/maxSize << endl ;
        cout << "maximum chain length " << calculateMaxChainLength() << endl;
        

        int prevsize = maxSize;
        maxSize *= 2;
        maxSize = nearestPrime(maxSize);
        //cout << maxSize << endl;
        vector<element *> temp;
        temp.resize(maxSize, nullptr);
        // hashelement.resize (maxSize);
        //  for (int i = 0  ; i < maxSize ; i++)
        //  {
        //     // element * t = hashelement[i] ;
        //    //  delete t ;
        //      hashelement[i]= nullptr ;
        //  }
        // print () ;
        for (int i = 0; i < prevsize; i++)
        {
            element *current = hashelement[i];

            while (current != nullptr)
            {
                element *t = new element(current->key, current->value);
                int index = hashFunction(current->key) % maxSize;

                if (temp[index] == nullptr)
                    temp[index] = t;

                else
                {
                    t->next = temp[index];
                    temp[index] = t;
                }
                // insert (current->key,current->value);
                //    print();

                current = current->next;
            }
        }

        hashelement = temp;
        cout << endl;
        cout << "AFTER REHASHING" << endl; 
        cout << "Average probe count " <<  randomSearch(maxSize) <<endl ;
        cout << "load factor " << currentSize*1.0/maxSize << endl ;
        cout << "maximum chain length " << calculateMaxChainLength() << endl;
    }

    void rehashingDelete()
    {
        DELETE = 0;

        // cout << "maximum chanin length" << calculateMaxChainLength() << endl;
        // cout << "hello" << endl;
        // cout << 0.8*chainLengthLimit << endl;
        if (calculateMaxChainLength() > 0.8 * chainLengthLimit)
            return;

        int prevsize = maxSize;
        maxSize = maxSize / 2;
        maxSize = nearestPrime(maxSize);

        if (maxSize < initialSize)
        {
            maxSize = prevsize;
            return;
        }

        vector<element *> temp;
        temp.resize(maxSize, nullptr);

        for (int i = 0; i < prevsize; i++)
        {
            element *current = hashelement[i];

            while (current != nullptr)
            {
                element *t = new element(current->key, current->value);
                int index = hashFunction(current->key) % maxSize;

                if (temp[index] == nullptr)
                    temp[index] = t;

                else
                {
                    t->next = temp[index];
                    temp[index] = t;
                }
                // insert (current->key,current->value);
                //    print();

                current = current->next;
            }
        }

        hashelement = temp;
    }

    void print()
    {

        for (int i = 0; i < maxSize; ++i)
        {

            element *current = hashelement[i];
            cout << i << " : ";
            while (current != nullptr)
            {

                current->print();

                current = current->next;
            }
            cout << endl;
        }
       // cout << "totaL collision " << totalcolission << endl;
    }

    element *find(string key)
    {
        int index = hashFunction(key) % maxSize;
        element *current = hashelement[index];
        totalProbe++;

        while (current != nullptr)
        {
            if (current->key == key)
                return current;

            current = current->next;
            totalProbe++;
        }

        return nullptr;
    }

    void remove(string key)
    {
        if (DELETE == 100)
            rehashingDelete();
        int index = hashFunction(key) % maxSize;
        element *current = hashelement[index];
        element *prev = nullptr;

        if (find(key) == nullptr)
            return;

        currentSize--;

        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (prev != nullptr)
                    prev->next = current->next;
                else
                    hashelement[index] = current->next;

                DELETE++;

                delete current;
                return;
            }

            prev = current;
            current = current->next;
        }
    }

    float randomSearch(int totalWords)
    {
        int wordsToSearch = totalWords / 10;

        //  totalcolission = 0 ;
        totalProbe = 0;

      //  cout << "total word" << wordsToSearch << endl;

        for (int i = 0; i < wordsToSearch; ++i)
        {
            int randomIndex = rand() % totalWords + 1;
            string wordToSearch = arr[randomIndex];

            find(wordToSearch);
        }

        if (totalWords >=10000)
        {
             cout << "Average Probe count " << (totalProbe*1.0) / wordsToSearch << endl;
             cout << "totalcollision " << totalcolission << endl;


        }

        // cout << "totalProbe " << totalProbe << endl;
        // cout << "totalcollision " << totalcolission << endl;

        return ((totalProbe*1.0) / wordsToSearch );
    }
};

int main()
{
    unsigned int seed = static_cast<unsigned int>(time(0));
    seed = 1708347359;
    srand(seed);
   // cout << seed << endl;

    HashTable ht(5000);
    string a;

    for (int i = 1; i <= 10000; i++)
    {
        arr[i] = randomWordGenerator();
    }
    for (int i = 1; i <= 10000; i++)
    {
        // cin >> a ;
        ht.insert(arr[i], i);
        // ht.insert(randomWordGenerator(),i );
    }
    // cout << "heelo" ;
    //   ht.print();
    cout << endl;
    ht.randomSearch(10000);

    // for (int i=1 ; i<=10000 ; i++)
    // {
    //     ht.remove(arr[i]);
    // }
    // ht.print();
    // ht.randomSearch(arr,10000);

    // // for (int i = 1; i <= 100; i++)
    // {
    //     ht.insert(randomWordGenerator(), i);
    // } // ht.print();
}