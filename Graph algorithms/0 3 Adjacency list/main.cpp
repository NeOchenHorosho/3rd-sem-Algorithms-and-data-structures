#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm> 
#include <limits>

using namespace std;


int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int verticies_num, edges_num;
    in >> verticies_num >> edges_num;

    vector<vector<int>> adjacency_list(verticies_num + 1);

    for(int i = 0; i < edges_num; i++)
    {
        int left, right;
        in >> left >> right;

        adjacency_list[left].push_back(right);
        adjacency_list[right].push_back(left);
    }
    for(int i = 1; i < verticies_num +1; i++)
    {
        out << adjacency_list[i].size() << ' ';
        for(auto &b: adjacency_list[i])
        {
            out << b << ' ';
        }
        out << '\n';
    }
}