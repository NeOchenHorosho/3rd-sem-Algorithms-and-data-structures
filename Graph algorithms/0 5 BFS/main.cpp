#include <fstream>
#include <queue>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int vertices_num;
    in >> vertices_num;
    queue<int> bfs_queue;
    vector<vector<int>> adjacency_matrix(vertices_num + 1, vector<int>(vertices_num + 1, 0));
    for (int i = 1; i <= vertices_num; i++)
        for (size_t j = 1; j < vertices_num + 1; j++)
            in >> adjacency_matrix[i][j];
    vector<int> labels(vertices_num + 1, 0);

    int current_label = 1;
    for (int i = 1; i < vertices_num + 1; i++)
    {
        if (labels[i] == 0)
        {
            bfs_queue.push(i);
            labels[i] = current_label++;
            while (!bfs_queue.empty())
            {
                int curr_vert = bfs_queue.front();
                bfs_queue.pop();
                for(int j =1; j <= vertices_num; j++)
                {
                    if(adjacency_matrix[curr_vert][j]&&labels[j]==0)
                    {
                        labels[j]=current_label++;
                        bfs_queue.push(j);
                    }
                }
            }
        }
    }

    for (int i=1; i<= vertices_num; i++)
    {
        out << labels[i] << ' ';
    }
}