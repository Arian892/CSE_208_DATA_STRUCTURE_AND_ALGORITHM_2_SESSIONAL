#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

class information
{
public:
    int height;
    int age;
    int divorce_status;

    information(int height, int age, int divorce_status)
    {
        this->height = height;
        this->age = age;
        this->divorce_status = divorce_status;
    }
};

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
    int nodes, edges;
    vector<vector<int>> capacity;
    vector<vector<int>> residualcapacity;
    vector<vector<int>> flow;
    vector<int> inflow;
    vector<int> parent;
    vector<bool> visited;

public:
    Graph(int nodes)
    {
        this->nodes = nodes;

        capacity.resize(nodes + 1, vector<int>(nodes + 1, 0));
        residualcapacity.resize(nodes + 1, vector<int>(nodes + 1, 0));
        flow.resize(nodes + 1, vector<int>(nodes + 1, 0));
        parent.resize(nodes + 1);
        visited.resize(nodes + 1);
        inflow.resize(nodes + 1);
        fill(inflow.begin(), inflow.end(), 0);
    }
    void addEdge(Edge e)
    {

        capacity[e.start][e.end] = e.weight;
        residualcapacity[e.start][e.end] = e.weight;
        flow[e.start][e.end] = 0;
    }

    bool BFS(int source, int sink)
    {
        reset(); // Reset parent array and visited array

        queue<int> q;
        q.push(source);
        visited[source] = true;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (int neighbor = 1; neighbor <= nodes; ++neighbor)
            {
                if (!visited[neighbor] && residualcapacity[current][neighbor] > 0)
                {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    visited[neighbor] = true;

                    if (neighbor == sink)
                    {
                        // Found a path to the sink
                        return true;
                    }
                }
            }
        }

        // No path to the sink
        return false;
    }

    void foid_fulkerson(int source, int sink)
    {
        int max_flow = 0;
        while (BFS(source, sink))
        {
            int pathflow = INT_MAX;
            int i = sink;

            while (i != source)
            {
                int j = parent[i];
                if (pathflow > residualcapacity[j][i])
                {
                    pathflow = residualcapacity[j][i];
                }
                i = parent[i];
            }

            i = sink;
            while (i != source)
            {
                int j = parent[i];

                residualcapacity[i][j] += pathflow;
                residualcapacity[j][i] -= pathflow;

                flow[i][j] += pathflow;
                inflow[j] += pathflow;

                i = parent[i];
            }
            max_flow += pathflow;
        }

        cout << max_flow << endl;
    }

    void reset()
    {
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), false);
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int men, women;
    cin >> men >> women;

    Graph graph(men + women + 2);

    vector<information> allmen;
    vector<information> allwomen;

    allmen.push_back(information(0, 0, 0));
    allwomen.push_back(information(0, 0, 0));

    int height, age, divorce_status;
    for (int i = 1; i <= men; i++)
    {
        cin >> height >> age >> divorce_status;
        allmen.push_back(information(height, age, divorce_status));
        graph.addEdge(Edge(men + women + 1, i, 1)); // connecting source with every men
    }

    for (int i = 1; i <= women; i++)
    {
        cin >> height >> age >> divorce_status;
        allwomen.push_back(information(height, age, divorce_status));
        graph.addEdge(Edge(i + men, men + women + 2, 1)); // connecting sink with every women
    }

    for (int i = 1; i <= men; i++)
    {
        for (int j = 1; j <= women; j++)
        {
            if (abs(allmen[i].height - allwomen[j].height) <= 10 && abs(allmen[i].age - allwomen[j].age) <= 5 && allmen[i].divorce_status == allwomen[j].divorce_status)
            {
                graph.addEdge(Edge(i, j + men, 1));
            }
        }
    }
    graph.foid_fulkerson(men + women + 1, men + women + 2);

    fclose(stdin);
    fclose(stdout);
}