#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge 
{
    long long to;
    long long weight;
};

struct VertexState 
{
    long long distance;
    long long vertex;

    bool operator>(const VertexState& other) const 
    {
        return distance > other.distance;
    }
};

int main() 
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    long long vertices_num, edges_num;
    in >> vertices_num >> edges_num;

    vector<vector<Edge>> graph_adjacencies(vertices_num + 1);

    for (long long i = 0; i < edges_num; i++) 
    {
        long long u, v, w;
        in >> u >> v >> w;
        graph_adjacencies[u].push_back({v, w});
        graph_adjacencies[v].push_back({u, w});
    }

    vector<long long> shortest_paths(vertices_num + 1, numeric_limits<long long>::max());
    priority_queue<VertexState, vector<VertexState>, greater<VertexState>> travel_queue;

    shortest_paths[1] = 0;
    travel_queue.push({0, 1});

    while (!travel_queue.empty()) 
    {
        VertexState current = travel_queue.top();
        travel_queue.pop();

        long long current_dist = current.distance;
        long long current_vertex = current.vertex;

        if (current_dist > shortest_paths[current_vertex]) 
            continue;

        for (const auto& edge : graph_adjacencies[current_vertex]) 
        {
            if (shortest_paths[current_vertex] + edge.weight < shortest_paths[edge.to]) 
            {
                shortest_paths[edge.to] = shortest_paths[current_vertex] + edge.weight;
                travel_queue.push({shortest_paths[edge.to], edge.to});
            }
        }
    }

    out << shortest_paths[vertices_num];

    return 0;
}