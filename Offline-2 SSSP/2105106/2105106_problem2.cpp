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
};

class Graph
{
    vector<Edge> edgelist; // all the edges of graph
    vector<int> parent;
    vector<int> distance;
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
        distance.resize(nodes + 1);
        reset();
    }
    void reset()
    {
        for (int i = 0; i <= nodes; i++)
        {
            distance[i] = INT_MAX;
            parent[i] = -1;
        }
    }

    void addEdge(Edge edge)
    {
        edgelist.push_back(edge);
    }
    void ExtraEdgeAdd(Edge edge)
    {
        edgelist.push_back(edge);
        edges++;
    }
    void print()
    {
        for (auto v : edgelist)
            v.print();
    }
    int BellmanFord(int source, int destination)
    {
        reset();
        distance[source] = 0;

        for (int i = 1; i <= nodes - 1; i++)
        {
            for (auto v : edgelist)
            {
                relax(v);
            }
        }
        return distance[destination];
    }

    void relax(Edge a)
    {
        if (distance[a.start] == INT_MAX)
        {
            return;
        }
        if (distance[a.end] > distance[a.start] + a.weight)
        {
            distance[a.end] = distance[a.start] + a.weight;
        }
    }

    void printdis()
    {
        for (int i = 1; i <= nodes; i++)
            cout << i << "   " << distance[i] << endl;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int edges, nodes;
    cin >> nodes >> edges;

    Graph graph(nodes, edges);
    int ExtraEdgeStart, ExtraEdgeEnd, LowerRange, UpperRange, source, destination;
    int extraweight;

    int a, b, w;
    for (int i = 0; i < edges; i++)
    {
        cin >> a >> b >> w;
        Edge e(a, b, w);
        graph.addEdge(e);
    }
    cin >> ExtraEdgeStart >> ExtraEdgeEnd;
    cin >> LowerRange >> UpperRange;
    cin >> source >> destination;
    int prevWeight = graph.BellmanFord(source, destination);
    int cycleweight = graph.BellmanFord(ExtraEdgeEnd, ExtraEdgeStart);
    if (cycleweight == INT_MAX || (-cycleweight) <= LowerRange)
    {
        graph.ExtraEdgeAdd(Edge(ExtraEdgeStart, ExtraEdgeEnd, LowerRange));
        extraweight = LowerRange;
    }
    else if ((-cycleweight) > LowerRange && (-cycleweight) <= UpperRange)
    {
        graph.ExtraEdgeAdd(Edge(ExtraEdgeStart, ExtraEdgeEnd, -cycleweight));
        extraweight = -cycleweight;
    }
    else if ((-cycleweight) > UpperRange)
    {
        cout << "impossible" << endl;
        return 0;
    }
    else if (cycleweight >= LowerRange && cycleweight <= UpperRange)
    {
        graph.ExtraEdgeAdd(Edge(ExtraEdgeStart, ExtraEdgeEnd, LowerRange));
        extraweight = LowerRange;
    }

    int postweight = graph.BellmanFord(source, destination);
    if (postweight < prevWeight)
        cout << extraweight << " " << postweight << endl;

    else
        cout << "impossible" << endl;

    fclose(stdin);
    fclose(stdout);
}
