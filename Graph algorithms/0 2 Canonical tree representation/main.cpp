#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int vertices_num;
    in >> vertices_num;
    vector<int> canonical_representation(vertices_num + 1, 0);
    for (int i = 0; i < vertices_num - 1; i++)
    {
        int first, second;
        in >> first >> second;
        canonical_representation[second] = first;
    }
    for (int i = 1; i < vertices_num + 1; i++)
        out << canonical_representation[i] << ' ';
}