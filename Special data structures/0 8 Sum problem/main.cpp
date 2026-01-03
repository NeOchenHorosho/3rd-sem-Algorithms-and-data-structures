#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<long long> ft;
int arr_size;

void update_tree(int pos, long long val)
{
    for (pos++; pos <= arr_size; pos += pos & -pos)
    {
        ft[pos] += val;
    }
}

long long query_sum(int left, int right)
{
    long long result = 0;

    for (int i = right; i > 0; i -= i & -i)
    {
        result += ft[i];
    }

    for (int i = left; i > 0; i -= i & -i)
    {
        result -= ft[i];
    }

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> arr_size;
    ft.resize(arr_size + 1, 0);

    for (int idx = 0; idx < arr_size; idx++)
    {
        long long value;
        cin >> value;
        update_tree(idx, value);
    }

    int queries;
    cin >> queries;

    for (int q = 0; q < queries; q++)
    {
        string cmd;
        cin >> cmd;

        if (cmd[0] == 'A')
        {
            int pos;
            long long delta;
            cin >> pos >> delta;
            update_tree(pos, delta);
        }
        else
        {
            int L, R;
            cin >> L >> R;
            cout << query_sum(L, R) << '\n';
        }
    }
}