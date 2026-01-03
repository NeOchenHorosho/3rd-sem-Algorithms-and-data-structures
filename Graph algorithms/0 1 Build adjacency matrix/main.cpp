#include <fstream>
#include <vector>
    
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int nodes_num, edges_num;
    in >> nodes_num >> edges_num;

    vector<vector<int>> adjacency_matrix(nodes_num, vector<int>(nodes_num, 0));
    
    for (int i =0; i < edges_num; i++)
    {
        int left_node, right_node;
        in >> left_node >> right_node;
        adjacency_matrix[left_node-1][right_node-1] = 1;
        adjacency_matrix[right_node-1][left_node-1] = 1;
    }
    for(auto &rows: adjacency_matrix)
    {
        for(auto a: rows)
            out << a << " ";
        out << '\n';
    }
}
