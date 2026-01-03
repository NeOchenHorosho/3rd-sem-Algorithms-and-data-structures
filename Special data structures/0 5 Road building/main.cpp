#include <fstream>
#include <numeric>
#include <vector>

using namespace std;
int find_root(vector<int> &dsu, int num)
{
    int root = num;
    while (dsu[root] != root)
    {
        root = dsu[root];
    }
    int curr = num;
    while (curr != root)
    {
        int next = dsu[curr];
        dsu[curr] = root;
        curr = next;
    }
    return root;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int cities_num;
    in >> cities_num;
    vector<int> dsu(cities_num + 1, 0);
    iota(dsu.begin(), dsu.end(), 0);
    int components = cities_num;
    int roads_num;
    in >> roads_num;

    for (int i = 0; i < roads_num; i++)
    {
        int first, second;
        in >> first >> second;
        int first_root = find_root(dsu, first), second_root = find_root(dsu, second);
        if (first_root != second_root)
        {
            dsu[first_root] = second_root;
            components--;
        }
        out << components << '\n';
    }
}
