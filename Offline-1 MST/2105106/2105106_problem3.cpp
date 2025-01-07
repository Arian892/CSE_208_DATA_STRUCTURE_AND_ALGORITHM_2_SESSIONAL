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
    vector<Edge> edgelist;
    vector<Edge> tempCheck;
    vector<int> parent;
    vector<Edge> MST;
    vector<vector<Edge>> Allmst;
    vector<Edge> baselist;
    vector<vector<int>> countinmst;
    vector<int> crirital;
    vector<int> pseudocritical;
    int minimum_weight;
    int mstsize;
    int edges, nodes;

public:
    Graph() {}

    Graph(int nodes, int edges)
    {
        this->nodes = nodes;
        this->edges = edges;
        countinmst.resize(nodes + 1);
        for (int i = 0; i <= nodes; i++)
            countinmst[i].resize(nodes + 1);
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
        countinmst[edge.start][edge.end] = 0;
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

    void increment(vector<Edge> check)
    {
        for (auto edge : check)
        {
            countinmst[edge.start][edge.end]++;
        }
    }

    void kruskalalgo()
    {
        baselist = edgelist;
        sort(edgelist.begin(), edgelist.end());

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
        vector<Edge> currentCombination(mstsize);
        recursiveCombination(0, edges - 1, 0, currentCombination);
    }

    void recursiveCombination(int start, int end, int index, vector<Edge> &currentCombination)
    {
        if (index == mstsize)
        {
            for (auto edge2 : currentCombination)
            {
                if (isCycle(edge2))
                {
                    reset();
                    return;
                }
            }
            if (weightofmst(currentCombination) == minimum_weight)
            {
                increment(currentCombination);
                Allmst.push_back(currentCombination);
            }
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

    void printcount()
    {
        for (auto edge : baselist)
        {

            if (Allmst.size() == countinmst[edge.start][edge.end])
                cout << "any" << endl;
            else if (countinmst[edge.start][edge.end] == 0)
                cout << "none" << endl;
            else
                cout << "at least one" << endl;
        }
    }

    void addinvector()
    {
        for (int i = 0; i < edges; i++)
        {

            if (Allmst.size() == countinmst[baselist[i].start][baselist[i].end])
                crirital.push_back(i);
            else if (countinmst[baselist[i].start][baselist[i].end] == 0)
            {
            }
            else
                pseudocritical.push_back(i);
        }
    }
    void printindex()
    {

        cout << "Critical edges: [";
        for (int i = 0; i < crirital.size(); i++)
        {
            cout << crirital[i];
            if (i != crirital.size() - 1)
                cout << ",";
        }
        cout << "]," << endl;
        cout << "Pseudo critical edges: [";

        for (int i = 0; i < pseudocritical.size(); i++)
        {
            cout << pseudocritical[i];
            if (i != pseudocritical.size() - 1)
                cout << ",";
        }
        cout << "]" << endl;
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

    graph.addinvector();
    graph.printindex();
}
