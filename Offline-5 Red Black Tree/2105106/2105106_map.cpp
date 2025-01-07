#include "red_black_tree.cpp"

using namespace std;

class Map
{
    Red_black_tree t;

public:
    void insert(pair<int, string> val)
    {
        if (t.find(val.first))
        {
            t.setValue(val);
        }
        else
        {
            t.insert(val);
        }
        t.print();
    }
    void Delete(int key)
    {

        if (t.find(key))
        {
            t.Delete(key);
            t.print();
        }
        else
        {
            cout << key << " not found" << endl;
        }
    }
    void find(int key)
    {
        if (t.find(key))
        {
            cout << key << " found" << endl;
        }
        else
        {
            cout << key << " not found" << endl;
        }
    }
    void size()
    {
        cout << t.size << endl;
    }
    void isEmpty()
    {
        if (t.size)
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
    void Iteration()
    {
        t.inorder();
    }

    void clear()
    {

        if (t.size == 0)
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            t.clear();
            cout << "successful" << endl;
        }
    }
};

int main()
{
    Map map;

    string str;
    int i = 1 ; 
    cout << "Cmd "<<1 <<": ";
    
    while (cin >> str)
    {
        
        
        int key;
        string value;
        if (str == "I")
        {
            
            cin >> key >> value;
            map.insert({key, value});
            i++ ;
            cout << endl;
        }
        else if (str == "F")
        {
            cin >> key;
            map.find(key);
            i++ ;
            cout << endl;
        }
        else if (str == "S")
        {
            map.size();
            i++ ;
            cout << endl;
        }
        else if (str == "E")
        {
            cin >> key;
            map.Delete(key);
            i++ ;
            cout << endl;
        }
        else if (str == "Em")
        {
            map.isEmpty();
            i++ ;
            cout << endl;
        }

        else if (str == "Clr")
        {
            map.clear();
            i++ ;
            cout << endl;
        }
        else if (str == "Itr")
        {
            map.Iteration();
            i++ ;
            cout << endl;
        }
        cout << "Cmd "<<i <<": ";
    }
}
