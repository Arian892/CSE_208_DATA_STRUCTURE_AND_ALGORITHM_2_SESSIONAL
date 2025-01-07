#include "2105106_Fibonacci_heap.cpp" 
#include <iostream>
using namespace std ;


class Priority_queue {
    
    public :

    Priority_queue ()
    {
    
    }
    Fibonacci_heap make_heap ()
    {
        Fibonacci_heap  f;
        return f ;

    }
    void isEmpty (Fibonacci_heap &f)
    {
        if (f.isEmpty()) cout << "Empty" << endl;
        else cout << "not empty" << endl;


    }
    void insert (Fibonacci_heap &f , int key, int value)
    {
        f.insert (key,value);

    }
    node * extract_max (Fibonacci_heap &f )
    {
        f.extract_max ();
        return nullptr ;

    }
    void increase_key(Fibonacci_heap &f, int value , int new_key)
    {
        
        f.increaseKey(value,new_key);

    }
    void Delete (Fibonacci_heap &f , int value)
    {
        f.Delete (value);

    }
    Fibonacci_heap meld (Fibonacci_heap &f1, Fibonacci_heap &f2)
    {
        return f1.meld(f2);


    }
    void find_max (Fibonacci_heap &f)
    {
        pair<int,int>max =f.findmax ();
        cout << " max value : (key "<<max.first << ", value: " << max.second << ")"<< endl;

    }
    void print (Fibonacci_heap &f )
    {
        f.print();

    }
    void test ()
    {
    Fibonacci_heap h1 ;
    Fibonacci_heap h2; 
    Fibonacci_heap h3 ;
    h1 = make_heap ();
    h2 = make_heap ();
    h3 = make_heap ();
    for (int i = 1 ;  i<=10 ; i++)
    {
        insert(h1,i,i);
    }
    cout << endl;
    print(h1);
    cout << endl;
    extract_max (h1);
    print (h1);
    cout << endl;
    extract_max(h1);
    print (h1);
    cout << endl;
    increase_key (h1,1,10);
    print (h1);
    cout << endl;
    extract_max(h1);
    print (h1);
    cout << endl;
    increase_key(h1,5,100);
    print(h1);
    cout << endl;
    extract_max(h1);
    print(h1);
    cout << endl;
    find_max (h1);
   // cout << endl;
    
    insert (h1,10,10);
    print (h1);
    cout << endl;
    Delete (h1,8);
    print(h1);
    cout << endl;
    Delete (h1,2);
    print(h1);
    cout << endl;


    // heap2

    for (int i = 11 ; i <= 20 ; i++)
     insert(h2,i,i);

     print (h2);
     cout << endl;

     extract_max(h2);
     print(h2);
     cout << endl;

     h3= meld(h1,h2);
     print(h3);
     cout << endl;

     extract_max (h3);
     print(h3);
     cout << endl;

    }



};


int main ()
{
    Priority_queue pq ;
    pq.test();
    




    
   // print(h1);


//     insert(h,10,10);
//     insert(h,1,1);
//     insert(h,2,2);
//     insert(h,3,3);
//     extract_max(h);
//  //   print(h);
//     insert (h2,4,4);
//     print (h2);
//     h3 = meld (h2,h);
//    print(h2);
//    print (h3);
  
    
   // extract_max (h2);
  //  print (h2);
}