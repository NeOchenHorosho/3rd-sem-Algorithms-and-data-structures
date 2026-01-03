#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

struct Edge
{
    int u, v;
    bool destroyed = false;
};

struct DSU
{
    vector<int> parent;
    int components;

    DSU(int n): parent(n+1), components(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find_root(int num)
    {
        int root = num;
        while (parent[root] != root)
        {
            root = parent[root];
        }
        int curr = num;
        while (curr != root)
        {
            int next = parent[curr];
            parent[curr] = root;
            curr = next;
        }
        return root;
    }
    void unite(int a, int b)
    {
        a = find_root(a);
        b = find_root(b);
        if (a != b)
        {
            parent[b] = a;
            components--;
        }
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n, m, q;
    in >> n >> m >> q;

    vector<Edge> edges(m + 1);
    for (int i = 1; i <= m; i++)
    {
        in >> edges[i].u >> edges[i].v;
    }

    vector<int> earthquake_indices(q);
    for (int i = 0; i < q; i++)
    {
        in >> earthquake_indices[i];
        edges[earthquake_indices[i]].destroyed = true;
    }

    DSU dsu(n);
    for (int i = 1; i <= m; i++)
    {
        if (!edges[i].destroyed)
        {
            dsu.unite(edges[i].u, edges[i].v);
        }
    }

    string result = "";
    result.reserve(q);
    for (int i = q - 1; i >= 0; i--)
    {
        if (dsu.components == 1)
        {
            result.append(i + 1, '1');
            break;
        }
        else
        {
            result += '0';
        }

        int edge_idx = earthquake_indices[i];
        dsu.unite(edges[edge_idx].u, edges[edge_idx].v);
    }
    reverse(result.begin(), result.end());

    out << result;

    return 0;
}