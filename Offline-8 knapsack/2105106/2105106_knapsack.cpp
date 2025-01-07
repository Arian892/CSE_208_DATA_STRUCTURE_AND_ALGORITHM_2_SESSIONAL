#include<vector>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std ;



class knapsack {

    vector <int> values ;
    int elements ;
    vector <int> weights ; 
    int capacity ;
    vector <vector<int>> dp_table;
    int max_value ;
    int original_ans ;

    public :
    knapsack (vector <int> values , vector <int > weights,int capacity)
    { 
        this->values =values ;
        this->weights = weights ;
        elements = values.size()-1;
       this->capacity = capacity ;
       max_value = maxValue();


       
       dp_table.resize(elements+1, vector<int>(maxValue()*elements + 1));





       

        for (int i = 1; i <= elements ; i++)
    {
        // cin >> values_array[i] >> weights_array [i] ;
       // cout << this->values[i] << "  " << this->weights[i] << endl;
        
    }

   
        

        

    }
     void dynamic_programming2 ()
    {
        int col = dp_table[0].size ();
        int row = dp_table.size ();
      //  cout << row  << elements;
    //  cout << row << col << endl;
        
       // cout << maxValue() << endl;

       for (int i = 0 ;  i < row; i++)
       {
        dp_table[i][0] = 0 ;
         
       }
        for (int i = 1 ;  i < col ; i++)
       {
        dp_table[0][i] = 10000000 ;
         
       }
        for (int i = 1 ; i < row ; i++)
        {
            //cout << values[i] << endl; ;
            for (int v = 1 ; v < col ; v++)
            {
                // if (v == 0) dp_table[i][v] = 0 ;
                // else if (i == 0 && v > 0) dp_table[i][v] = 10000000;

            
                   int a =  dp_table[i-1][v] ;
                 //  cout << "v " << v << " values of i " << values[i] << endl;

                   if (v - values[i]  < 0) 
                   dp_table[i][v]= a ;
                 else 
                 { 
                 
                    int b = dp_table[i-1][v-values[i]] + weights[i] ;
                   dp_table[i][v] = min(a,b);
                 }
                }

            }
        

        int ans ;
        int val ;
        int max = INT_MIN ;

       // cout << dp_table[elements][262] ;
       
        for (int i = 1 ; i < dp_table[elements].size (); i++)
        {  
            if (dp_table[elements][i] <= capacity && i >= max  )
         { 
              ans = dp_table[elements][i] ; 
          //    cout << " ans " << ans << endl;
       
             max = i ;
          //    cout << " max " << max << endl;
         }
        }
        original_ans = max ;
        cout << "Original Instance: " << endl;
        cout << "Answer: " <<max << endl; 
        cout << "Used Weight:  " << ans << endl;
        cout << "Indices :" ;
        vector <int > indices = backTracing(dp_table, max,values);
        for (auto v : indices)
        {
            cout << v << " " ;
        }
        cout << endl; 

    }

    void printdp_table ()
    {
        for (int i = 0 ; i <= elements ; i++)
        {
            for (int v = 0 ; v < dp_table[0].size() ; v++)
            {
                cout << dp_table[i][v] << " " ;
                

            }
            cout << endl; 
        }
        
    }

    void dp_with_eps (double eps)
    {
       // cout << max_value << eps << elements << endl;
        vector<int> another_values(elements +1);

        
        double thita =( max_value * eps * 1.0) / (2 * elements);
      //  cout <<setprecision (17) <<thita << endl;
        for (int i = 1 ;i<= elements ; i++)
        {
           // cout << values[i]<< " " << endl;
            another_values[i] = ceil(values[i]/thita) ;
          //  cout << another_values[i] << endl;
        }
        int new_max = -1000 ;
        for (int i = 1; i <= elements ; i++)
        {
            if (another_values[i] >= new_max)new_max = another_values[i];
        }
      //  cout << new_max << endl;




        vector <vector <int>> another_dp_table ;
        another_dp_table.resize(elements+1, vector<int>(new_max*elements + 1));
         int row = another_dp_table.size();
         int col = another_dp_table[0].size ();

       //  cout << row << col << endl;

           for (int i = 0 ;  i < row; i++)
       {
        another_dp_table[i][0] = 0 ;
         
       }
        for (int i = 1 ;  i < col ; i++)
       {
        another_dp_table[0][i] = 10000000 ;
         
       }
        for (int i = 1 ; i < row ; i++)
        {
            //cout << values[i] << endl; ;
            for (int v = 1 ; v < col ; v++)
            {
                // if (v == 0) dp_table[i][v] = 0 ;
                // else if (i == 0 && v > 0) dp_table[i][v] = 10000000;

            
                   int a =  another_dp_table[i-1][v] ;
                 //  cout << "v " << v << " values of i " << values[i] << endl;

                   if (v - another_values[i]  < 0) 
                   another_dp_table[i][v]= a ;
                 else 
                 { 
                 
                    int b = another_dp_table[i-1][v-another_values[i]] + weights[i] ;
                   another_dp_table[i][v] = min(a,b);
                 }
                }

            }
        

        int ans ;
        int val ;
        int max = INT_MIN ;

       // cout << dp_table[elements][262] ;
       
        for (int i = 1 ; i < another_dp_table[elements].size (); i++)
        {  
            if (another_dp_table[elements][i] <= capacity && i >= max  )
         { 
              ans = another_dp_table[elements][i] ; 
          //    cout << " ans " << ans << endl;
       
             max = i ;
          //    cout << " max " << max << endl;
         }
        }

        cout << "Rounded Instance with Eps: " << eps << endl;
        cout << "Theta: " << thita << endl;
        cout << "Answer of reduced instance: " << max << endl ;
        cout << "Answer of reduced instance multiplied by theta: " << max * thita << endl; 
        cout << "Indices : " ;
        

        int rounded_original_instance = 0 ;
        vector <int > indices = backTracing(another_dp_table,max,another_values);
        for (auto v : indices)
        {
            cout << v << " " ;
            rounded_original_instance += values[v] ;

        }
        
        cout << endl; 

        cout << "Answer of original instance (rounded up): " << rounded_original_instance << endl;
        cout << "Used Weight: " <<ans << endl; 

        cout << "Ratio: " << original_ans* 1.0/rounded_original_instance << endl;
       

        // int col = 
    }


    int maxValue ()
    {
        int max = -1000 ;
        for (int i = 1; i <= elements ; i++)
        {
            if (values[i] >= max) max = values[i];
        }
        return max ;

    }


    vector <int> backTracing (vector<vector<int>> dp, int value,vector <int> value_array)
    {
       // cout << value << endl;

        vector <int> indices ;
        for (int i = elements ; i > 0 ; i--)
        {
           // cout << dp[i][value] << endl;
            if (dp[i][value] == dp[i-1][value])
            continue;


            else {
                value -= value_array[i] ;
             indices.push_back(i);

            }

        }
        return indices ;


    }





};


int main ()
{
    freopen ("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int elements; 
    int weights ;
    cin >> elements ;
    cin >> weights ;
    vector <int > values_array  (elements+1);
    vector<int> weights_array (elements+1);

    for (int i = 1; i <= elements ; i++)
    {
        cin >> values_array[i] >> weights_array [i] ;

    }
   // cout << endl;

    for (int i = 1; i <= elements ; i++)
    {
        // cin >> values_array[i] >> weights_array [i] ;
      //  cout << values_array[i] << "  " << weights_array[i] << endl;
        
    }

    knapsack ks (values_array, weights_array,weights);
    ks.dynamic_programming2();
    cout << endl; 
    ks.dp_with_eps(0.5);

    cout << endl; 
    ks.dp_with_eps(0.2);
    cout << endl; 
    ks.dp_with_eps(0.1);
    cout << endl; 
    ks.dp_with_eps(0.05);

    fclose (stdin);
    fclose (stdout);
  //  ks.printdp_table();
    return 0 ;
}

