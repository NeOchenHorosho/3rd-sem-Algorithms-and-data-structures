#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using std::pair;
using std::vector;

std::string palindrome(std::string first_seq)
{
    std::string second_seq = first_seq;
    std::reverse(second_seq.begin(), second_seq.end());
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
    std::string result = "";
    while (i > 0 && j > 0)
    {
        if (first_seq[i - 1] == second_seq[j - 1])
        {
            result.push_back(first_seq[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] >= dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string input;
    in >> input;
    auto res = palindrome(input);
    out << res.size() << "\n";
    out << res;
}