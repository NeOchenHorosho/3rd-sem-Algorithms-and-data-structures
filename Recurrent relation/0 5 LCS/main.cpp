#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using std::cin;
using std::cout;
using std::pair;
using std::vector;

template <class T>
pair<vector<size_t>, vector<size_t>> LCS(const vector<T> &first_seq, const vector<T> &second_seq)
{
    vector<vector<size_t>> dp(first_seq.size() + 1, vector<size_t>(second_seq.size() + 1, 0));
    for (size_t i = 1; i < dp.size(); i++)
    {
        for (size_t j = 1; j < dp[0].size(); j++)
        {
            if (first_seq[i - 1] == second_seq[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
        }
    }
    vector<size_t> first_indices;
    vector<size_t> second_indices;

    size_t i = first_seq.size();
    size_t j = second_seq.size();

    while (i > 0 && j > 0)
    {
        if (first_seq[i - 1] == second_seq[j - 1])
        {
            first_indices.push_back(i - 1);
            second_indices.push_back(j - 1);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    std::reverse(first_indices.begin(), first_indices.end());
    std::reverse(second_indices.begin(), second_indices.end());

    return {first_indices, second_indices};
}

int main()
{
    int sequence_len;
    cin >> sequence_len;
    vector<short> a(sequence_len), b(sequence_len);
    for (int i = 0; i < sequence_len; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < sequence_len; i++)
    {
        cin >> b[i];
    }
    auto res = LCS(a, b);
    cout << res.first.size() << "\n";
    for(auto a : res.first)
    {
        cout << a << " ";
    }
    cout << '\n';
    
    for(auto a : res.second)
    {
        cout << a << " ";
    }
}
