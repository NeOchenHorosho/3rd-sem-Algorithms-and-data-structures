#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int vertices_num;
    in >> vertices_num;
    stack<int> dfs_stack;
    vector<vector<int>> adjacency_matrix(vertices_num + 1, vector<int>(vertices_num + 1, 0));
    for (int i = 1; i <= vertices_num; i++)
        for (size_t j = 1; j < vertices_num + 1; j++)
            in >> adjacency_matrix[i][j];
    vector<int> labels(vertices_num + 1, 0);

    int current_label = 1;
    for (int i = 1; i <= vertices_num; i++)
    {
        if (labels[i] == 0)
        {
            stack<int> dfs_stack;
            dfs_stack.push(i);
            while (!dfs_stack.empty())
            {
                int curr_vert = dfs_stack.top();
                dfs_stack.pop();
                if (labels[curr_vert] == 0)
                {
                    labels[curr_vert] = current_label++;
                    for (int j = vertices_num; j >= 1; j--)
                    {
                        if (adjacency_matrix[curr_vert][j] == 1 && labels[j] == 0)
                        {
                            dfs_stack.push(j);
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= vertices_num; i++)
    {
        out << labels[i] << ' ';
    }
}