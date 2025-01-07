#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

bool isPrime(int a)
{
    if (a <= 1)
        return false;

    if (a == 2)
        return true;

    for (int i = 2; i <= a / 2; i++)
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

        char randomChar = 'a' + rand() % 26; // Generating lowercase letters
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
    const int prime = 31;
    unsigned int key = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        key = key * prime + static_cast<unsigned int>(str[i]);
    }

    return key;
}
unsigned int hashFunction2(string &str) {
    unsigned int hash = 0;

    for (char c : str) {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

unsigned int auxHash(string &str)
{
    const int prime2 = 37;
    unsigned int key = 0;

    for (int i = 0; i < str.length(); ++i)
    {
        key = key * prime2 + static_cast<unsigned int>(str[i]);
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
    int totalProbe;
    int currentSize ;
    int totalcolission ;
    int INSERT ;

public:
    HashTable(int size)
    {
        maxSize = nearestPrime(size);
        hashelement.resize(maxSize, nullptr);
        totalProbe = 0;
        currentSize = 0 ;
        totalcolission = 0 ;
       
    }
    void insert(string key, int value)
    {

        if (currentSize== maxSize) return ;

        // float load = (currentSize * 1.0) / maxSize ;
        // if (load > 0.6) rehashing();
        int probe = 0;
        int index = customProbing(key, probe);
        if (find(key) != nullptr)
            return;

      //  cout << "hash index " << index << endl;
        while (hashelement[index] != nullptr && hashelement[index]->isDeleted == false)
        {
            probe++;
            index = customProbing(key, probe);
        }

        if (probe > 0) totalcolission++ ;

        totalProbe += probe;

        if (hashelement[index] != NULL && hashelement[index]->isDeleted)
        {
            hashelement[index]->key = key;
            hashelement[index]->value = value;
            hashelement[index]->isDeleted = false;
        }
        else
        {
            element *temp = new element(key, value);
            hashelement[index] = temp;
        }

        currentSize ++;


    }

     unsigned int customProbing(string &str, int i)
    {
        unsigned int hash1 = hashFunction(str);
        unsigned int hash2 = auxHash(str);
        int c1 = 31, c2 = 59 ;

        return (hash1 + c1 *  i * hash2 + c2 * i * i)  % maxSize;
    }

    void print()
    {

        for (int i = 0; i < maxSize; ++i)
        {

            element *current = hashelement[i];
            cout << i << " : ";
            if (current != nullptr && current->isDeleted == false)
                current->print();

            cout << endl;
        }

        cout << "probe number " << totalProbe << endl;
        cout << "total collision " << totalcolission << endl;
    }

    element *find(string key)
    {
        int probe = 0;
        int index = customProbing(key, probe);
        element *current = hashelement[index];

        while (current != nullptr)
        {
         
            if (current->key == key && !current->isDeleted)
            {
              //  totalProbe++;

               // if (probe > 0) totalcolission++ ;
                totalProbe += (probe+1) ;
                return current;
            }
            probe++;

       //     totalProbe++;
            index = customProbing(key, probe);
            current = hashelement[index];
        }
       // if (probe > 0) totalcolission++ ;
              totalProbe+= (probe+1);

        return nullptr;
    }

    void remove(string key)
    {
        int probe = 0;
        int index = customProbing(key, probe);
        element *current = hashelement[index];

        if (find(key) == nullptr)return ;

        currentSize--;

        while (current != nullptr)
        {
            if (current->key == key && !current->isDeleted)
            {
                current->isDeleted = true;
                return;
            }

            probe++;
            index = customProbing(key, probe);
            current = hashelement[index];
        }
        
    }
    void rehashing()
    {
        cout << "rehashing" << endl; 
        int prevsize = maxSize;
        maxSize *= 2;
        maxSize = nearestPrime(maxSize);
        cout << maxSize << endl;
        vector<element *> temp;
        temp.resize(maxSize, nullptr);

        for (int i = 0; i < prevsize; i++)
        {
            if (hashelement[i] != nullptr)
            {
                int probe = 0;
                int index = customProbing(hashelement[i]->key, probe);
                while (temp[index] != nullptr && temp[index]->isDeleted == false)
                {
                    probe++;
                    index = customProbing(hashelement[i]->key, probe);
                }
                if (temp[index] != NULL && temp[index]->isDeleted)
                {
                    temp[index]->key = hashelement[i]->key;
                    temp[index]->value = hashelement[i]->value;
                    temp[index]->isDeleted = false;
                }
                else
                {
                    element *t = new element(hashelement[i]->key, hashelement[i]->value);
                    temp[index] = t;
                }
            }
        }

        hashelement = temp ;
    }

    void randomSearch (string arr[],int totalWords)
    {
         int wordsToSearch = totalWords / 10;

       //  totalcolission = 0 ;
         totalProbe = 0 ;

         cout << "total word" << wordsToSearch << endl; 

   
    for (int i = 0; i < wordsToSearch; ++i)
    {
        int randomIndex = rand() %  maxSize  + 1;
        string wordToSearch = arr[randomIndex];

        find (wordToSearch) ;
    }

   if (totalWords >=10000)
        {
             cout << "Average Probe count " << (totalProbe*1.0) / wordsToSearch << endl;
             cout << "totalcollision " << totalcolission << endl;


        }
}

    
};

int main()
{
    unsigned int seed = static_cast<unsigned int>(time(0));
    seed = 1708349400 ;
    srand(seed);
    cout << seed << endl;
    HashTable ht(10000);
    string a;
    string arr[10001];
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
   /// cout << "heelo" ;
  //   ht.print();
    ht.randomSearch(arr,10000);
  //  ht.print();

    // for (int i = 1; i <= 290; i++)
    // {
    //     //  cin >> a ;
    //     // ht.remove(a);

    //     ht.remove(arr[i]);
    //     // ht.print();
    // }
   //  ht.print();

    // for (int i = 1; i <= 15; i++)
    // {
    //     ht.insert(arr[i], i);
    // }
    // ht.print();

    // string a ;
    // for (int i = 1 ; i <= 20 ; i++)
    // {
    //     cin >> a ;
    //     ht.insert(a,i);
    //     ht.print();
    // }
    // cin >> a ;
    // ht.remove(a);
    // ht.print();
    // for (int i = 1 ; i <= 20 ; i++)
    // {
    //     cin >> a ;
    //     ht.insert(a,i);
    //     ht.print();
    // }

    // for (int i = 1; i <= 100; i++)
    // {
    //     a = randomWordGenerator();

    //     ht.insert(a, i);

    // }
    // ht.print();
    // ht.find(a)->print();
    // ht.remove(a);
    // ht.print();
}