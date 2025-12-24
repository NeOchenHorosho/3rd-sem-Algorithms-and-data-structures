#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> 
#include <limits>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int verticies_num, edges_num;
    cin >> verticies_num >> edges_num;

    vector<vector<pair<int, int>>> adjacency_list(verticies_num + 1);

    for(int i = 0; i < edges_num; i++)
    {
        int l, r, a;
        cin >> l >> r >> a;
        adjacency_list[l].push_back({r, a});
        adjacency_list[r].push_back({l, a});
    }

    vector<int> max_min_weight(verticies_num + 1, -1);

    priority_queue<pair<int, int>> priority_queue;

    max_min_weight[1] = numeric_limits<int>::max();
    priority_queue.push({numeric_limits<int>::max(), 1});

    while(!priority_queue.empty())
    {
        int current_limit = priority_queue.top().first;
        int current_vertex = priority_queue.top().second;
        priority_queue.pop();

        if (current_limit < max_min_weight[current_vertex]) {
            continue;
        }

        for (auto edge : adjacency_list[current_vertex])
        {
            int incident_vertex = edge.first;
            int weight = edge.second;

            int new_limit = min(current_limit, weight);

            if (new_limit > max_min_weight[incident_vertex])
            {
                max_min_weight[incident_vertex] = new_limit;
                priority_queue.push({new_limit, incident_vertex});
            }
        }
    }

    for(int i = 2; i <= verticies_num; i++)
    {
        cout << max_min_weight[i] << "\n";
    }
}