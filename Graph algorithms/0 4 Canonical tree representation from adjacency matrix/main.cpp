#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    vector<int> canonical_representation(n+1, 0);
    for(int i = 1; i <= n; i++)
    {
        for(int j=1; j <=n; j++)
        {
            int num;
            in >> num;
            if(num)
            {
                canonical_representation[j]=i;
            }
        }
    }
    for (int i = 1; i < n + 1; i++)
        out << canonical_representation[i] << ' ';
}