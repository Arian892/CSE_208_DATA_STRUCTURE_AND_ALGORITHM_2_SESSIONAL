#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

    // for sorting operation
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class Graph
{
    vector<Edge> edgelist;  // all the edges of graph
    vector<Edge> tempCheck; // temporary to store all the possible combination
    vector<int> parent;
    vector<Edge> MST;            // first mst to find weight
    vector<vector<Edge>> Allmst; // to store all possible mst
    int minimum_weight;
    int mstsize;
    int edges, nodes;

public:
    Graph() {}

    Graph(int nodes, int edges)
    {
        this->nodes = nodes;
        this->edges = edges;
        parent.resize(nodes + 1);
        reset();
    }
    void reset()
    {
        for (int i = 0; i <= nodes; i++)
        {
            parent[i] = -1;
        }
    }

    void addEdge(Edge edge)
    {
        edgelist.push_back(edge);
    }
    int find(int i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent[i]);
    }
    void Union(int a, int b)
    {
        int x = find(a);
        int y = find(b);

        parent[x] = y;
    }

    int weightofmst(vector<Edge> mst)
    {
        int sum = 0;
        for (auto edge : mst)
            sum += edge.weight;

        return sum;
    }

    bool isCycle(Edge e)
    {
        int x = find(e.start);
        int y = find(e.end);
        if (x == y)
            return true;
        Union(x, y);
        return false;
    }

    void kruskalalgo()
    {
        sort(edgelist.begin(), edgelist.end());



        // using the kruskal algo for finding the actual mst to get the weight

        for (auto edge : edgelist)
        {
            if (!isCycle(edge))
            {
                MST.push_back(edge);
            }
        }
        mstsize = MST.size();
        tempCheck.resize(mstsize);
        reset();

        minimum_weight = weightofmst(MST);
        vector<Edge> currentCombination(mstsize);   // this is for checking all possible combination
        recursiveCombination(0, edges - 1, 0, currentCombination);
    }

    void recursiveCombination(int start, int end, int index, vector<Edge> &currentCombination)
    {
        if (index == mstsize)
        {

            /// detecting if there is any cycle
            for (auto edge2 : currentCombination)
            {
                if (isCycle(edge2))
                {
                    reset();
                    return;
                }
            }
            if (weightofmst(currentCombination) == minimum_weight)
                Allmst.push_back(currentCombination);  // storing the approved mst

            reset();
            return;
        }
        for (int i = start; i <= end && end - i + 1 >= mstsize - index; i++)
        {
            currentCombination[index] = edgelist[i];

            recursiveCombination(i + 1, end, index + 1, currentCombination);
        }
    }

    void allmstprint()
    {
        cout << "MSTs:" << endl;
        for (int i = 0; i < Allmst.size(); i++)
        {

            cout << i + 1 << " :  "
                 << "[";
            sort(Allmst[i].begin(), Allmst[i].end());
            for (int j = 0; j < Allmst[i].size(); j++)
            {
                cout << "[" << Allmst[i][j].start << ", " << Allmst[i][j].end << ", " << Allmst[i][j].weight << "]";
                if (j != Allmst[i].size() - 1)
                    cout << ",";
            }

            cout << "]" << endl;
        }
    }
};

int main()
{
    int edges, nodes;
    cin >> nodes >> edges;

    Graph graph(nodes, edges);

    int a, b, w;
    for (int i = 0; i < edges; i++)
    {
        cin >> a >> b >> w;
        Edge e(a, b, w);
        graph.addEdge(e);
    }
    graph.kruskalalgo();
    graph.allmstprint();
}
