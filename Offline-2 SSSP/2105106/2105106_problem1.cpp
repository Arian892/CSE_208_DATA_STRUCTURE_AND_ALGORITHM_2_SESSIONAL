#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Edge
{
public:
    int start;
    int end;
    int weight;

    Edge(int a, int b, int w)
    {
        start = a;
        end = b;
        weight = w;
    }
};

class Graph
{
    map<pair<int, int>, int> AllstateToNode;
    map<pair<int, int>, int> WeightOfEdge;
    vector<int> priceInCity;
    vector<vector<int>> adjlist;
    int city, gasCapacity;
    vector<int> distance;
    int nodecount = 0;

public:
    // adding the edges to graph accordingly
    void ExtraEdgeAdd(vector<Edge> edgelist)
    {
        for (int i = 0; i < edgelist.size(); i++)
        {
            for (int j = edgelist[i].weight; j <= gasCapacity; j++)
            {
                int st = AllstateToNode[{edgelist[i].start, j}];
                int end = AllstateToNode[{edgelist[i].end, j - edgelist[i].weight}];
                WeightOfEdge.insert({{st, end}, 0});
            }
        }
    }

    // adding all the states/nodes to a corresponding in a map for example (1,0) state would be index 0
    // also adding the edges connected to each of the states
    void addNodeandEdge(int city, int gasCapacity, vector<int> priceInCity)
    {
        this->city = city;
        this->gasCapacity = gasCapacity;
        this->priceInCity = priceInCity;
        for (int i = 1; i <= city; i++)
        {
            for (int j = 0; j <= gasCapacity; j++)
            {
                AllstateToNode.insert({{i, j}, nodecount});
                if (j != gasCapacity)
                    WeightOfEdge.insert({{nodecount, nodecount + 1}, priceInCity[i]});

                nodecount++;
            }
        }
    }

    // for debugging purpose
    void printmap()
    {
        for (auto v : AllstateToNode)
        {
            cout << v.first.first << " " << v.first.second << " " << v.second << endl;
        }

        cout << "now theh edges" << endl;
        for (auto v : WeightOfEdge)
        {
            cout << v.first.first << " " << v.first.second << " " << v.second << endl;
        }
    }
    void creatingadjlist()
    {
        adjlist.resize(city * (gasCapacity + 1));
        for (auto v : WeightOfEdge)
        {
            adjlist[v.first.first].push_back(v.first.second);
        }
    }

    // for debugging purpose
    void printadjlist()
    {
        for (auto v : adjlist)

        {
            for (auto c : v)
            {
                cout << c << " ";
            }
            cout << endl;
        }
    }

    // reseting all the nodes distance to INF
    void reset()
    {
        for (auto &v : distance)
            v = INT_MAX;
    }

    void dijkstra(int source1, int des)
    {
        distance.resize(adjlist.size());
        reset();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        int source = AllstateToNode[{source1, 0}];
        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            for (auto neighbor : adjlist[u])
            {
                int v = neighbor;

                int weight = WeightOfEdge[{u, v}]; // Edge weight from WeightOfEdge map

                if (distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;

                    pq.push({distance[v], v});
                }
            }
        }

        int destination = AllstateToNode[{des, 0}];
        if (distance[destination] == INT_MAX)
        {
            cout << "impossible" << endl;
            return;
        }

        cout << distance[destination] << endl;
    }
    // void dijstra ()
    // {
    //     distance.resize(adjlist.size());
    //     reset ();
    //     //
    // }
};
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Graph graph;
    int city, roads, gasCapacity;

    cin >> city >> roads >> gasCapacity;
    vector<int> priceInCity;
    priceInCity.resize(city + 1);
    vector<Edge> edgelist;

    priceInCity.resize(city + 1);
    for (int i = 1; i <= city; i++)
    {
        cin >> priceInCity[i];
    }
    graph.addNodeandEdge(city, gasCapacity, priceInCity); // adding each stages to the graph

    int start, end, weight;

    for (int i = 1; i <= roads; i++)
    {
        cin >> start >> end >> weight;
        edgelist.push_back(Edge(start, end, weight));
    }
    graph.ExtraEdgeAdd(edgelist); /// adding the extra edges to the graph

    int source, destination;
    cin >> source >> destination;

    graph.creatingadjlist();
    graph.dijkstra(source, destination);
}
