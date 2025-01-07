#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>
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
    int nodes, edges;
    vector<vector<int>> capacity;
    vector<vector<int>> residualcapacity;
    vector<vector<int>> flow;
    vector<int> inflow;
    vector<int> parent;
    vector<bool> visited;

public:
    Graph(int nodes, int edges)
    {
        this->nodes = nodes;
        this->edges = edges;
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

    void dfs(int node)
    {

        visited[node] = true;

        for (int neighbor = 1; neighbor <= nodes; ++neighbor)
        {
            if (!visited[neighbor] && residualcapacity[node][neighbor] > 0)
            {
                dfs(neighbor);
            }
        }
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

        int max_flow_index = -1, max_inflow = INT_MIN;
        for (int i = 1; i <= nodes; i++)
        {
            if (i != source && i != sink && inflow[i] > max_inflow)

            {
                max_inflow = inflow[i];
                max_flow_index = i;
            }
        }
        reset();
        dfs(source);

        vector<int> set1;
        vector<int> set2;
        for (int i = 1; i <= nodes; i++)
        {
            if (visited[i] == true)
                set1.push_back(i);

            else
                set2.push_back(i);
        }

        cout << "[{";
        for (int i = 0; i < set1.size(); i++)
        {
            if (i != set1.size() - 1)
            {
                cout << set1[i] << ",";
            }
            else
            {
                cout << set1[i] << "},{";
            }
        }

        for (int i = 0; i < set2.size(); i++)
        {
            if (i != set2.size() - 1)
            {
                cout << set2[i] << ",";
            }
            else
            {
                cout << set2[i] << "}]" << endl;
            }
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
    int source, sink;
    cin >> source >> sink;

    graph.foid_fulkerson(source, sink);

    fclose(stdin);
    fclose(stdout);
}