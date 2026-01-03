#include <fstream>
#include <vector>
using namespace std;
struct Unit
{
    int val;
    bool is_full;
};
int main()
{
    int m, c, n;
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> m >> c >> n;
    vector<Unit> table(m, {0, false});
    for (int i = 0; i < n; i++)
    {
        int key;
        in >> key;
        int num_of_tries = 0;
        int first_hash = key % m;

        while (true)
        {
            int hash = ((first_hash) + c * num_of_tries) % m;
            if (!table[hash].is_full)
            {
                table[hash].val = key;
                table[hash].is_full = true;
                break;
            }
            if (table[hash].val == key)
            {
                break;
            }
            num_of_tries++;
        }
    }
    for (auto a : table)
    {
        if (a.is_full)
            out << a.val << ' ';
        else
            out << "-1 ";
    }
}