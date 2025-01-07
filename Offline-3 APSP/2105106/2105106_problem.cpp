#include<iostream>
#include <vector>

using namespace std ;


class Edge
{

public:
    int start;
    int end;
    int weight;

    Edge() {}
    Edge(int a, int b, int w)
    {
        start = a;
        end = b;
        weight = w;
    }
    void print()
    {
        cout << start << " " << end << " " << weight << endl;
    }
};


class Graph 
{
    int nodes,edges,threesholdCost;
    vector <vector<int>> DPTable ;
    vector <int> solutionArray ;
    public :

     Graph(int nodes, int edges)
    {
        this->nodes = nodes;
        this->edges = edges;
        DPTable.resize(nodes+1,vector<int>(nodes+1));
        solutionArray.resize (nodes+1);
        reset ();
    }
    void reset ()
    {
        for (int i = 0  ; i <= nodes ; i++)
          for (int j =0 ; j <= nodes ; j++)
              DPTable[i][j] = 1000000 ;


         for (int i= 1 ; i <= nodes ; i++)
          solutionArray[i]=0 ;

    }
    void threeshold (int threeshold)
    {
        threesholdCost = threeshold;
    }
     void addEdge(Edge edge)
    {
        DPTable[edge.start][edge.end] = edge.weight ;
        DPTable[edge.end][edge.start] = edge.weight ;       
    }
    void FloydWarshall ()
    {
        for (int d = 1 ; d <= nodes ; d++)
        {
            for (int i = 1;  i<= nodes ; i++)
            {
                for (int j= 1; j<= nodes ; j++)
                {
                    if (i!= d && j!= d)
                    {
                        int a = DPTable[i][j] ;
                        int b = DPTable[i][d] + DPTable[d][j] ;
                        DPTable[i][j]= min (a,b);

                    }

                }
            }
        }
    }

    vector<int> checking ()
    {
        int count ;
        int min = 10000;
        
        for (int i = 1 ; i <= nodes ; i++ )
        {
            count = 0;
            for (int j= 1 ; j<= nodes ; j++)
            {
                if (i!= j)
                if (DPTable[i][j] <= threesholdCost)
                count++ ;
            }
            if (min > count) min = count ;
            solutionArray[i]= count ;


        

        }
       // cout << min << endl;

        
        vector <int> retans ;
            for (int i = 1 ; i <= nodes ; i++)
            {
                if (solutionArray[i] == min)
                retans.push_back (i);
            }
          //  cout << retans.size() << endl;

       return retans ;

    }

    void print ()
    {
        for (int i = 1;  i<= nodes ; i++)
            {
                for (int j= 1; j<= nodes ; j++)
                {
                  cout << DPTable[i][j] << " " ;
                }
                cout << endl; 
            }
        
    }


} ;


int main ()
{
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);

    int city, roads , threesholdCost ;

    cin >> city >> roads  ;
    Graph graph (city,roads) ;
    int a, b, w;
    for (int i = 0; i < roads; i++)
    {
        cin >> a >> b >> w;
        Edge e(a, b, w);
        graph.addEdge(e);
    }
    cin >> threesholdCost ;
    graph.threeshold(threesholdCost);
    
    graph.FloydWarshall();

    vector <int >answer ;
    answer = graph.checking ();
    ///cout << answer.size() << endl;


    for (auto v : answer)
     cout << v << " " ;
 //  graph.print();

    


    fclose(stdin);
    fclose (stdout);

}