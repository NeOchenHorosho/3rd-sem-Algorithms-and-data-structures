#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <limits>
#include <cstring>
using namespace std;
bool matches(const string &phone, int pos, const string &word)
{
    int size = word.size();
    if (pos < size)
        return false;

    const char *p = phone.c_str() + pos - size;
    const char *w = word.c_str();

    for (int i = 0; i < size; i++)
    {
        if (p[i] != w[i])
            return false;
    }
    return true;
}
char lookup[128];
void init()
{
    for (int c = '0'; c <= '9'; c++)
        lookup[c] = c;

    lookup['I'] = lookup['J'] = '1';
    lookup['A'] = lookup['B'] = lookup['C'] = '2';
    lookup['D'] = lookup['E'] = lookup['F'] = '3';
    lookup['G'] = lookup['H'] = '4';
    lookup['K'] = lookup['L'] = '5';
    lookup['M'] = lookup['N'] = '6';
    lookup['P'] = lookup['R'] = lookup['S'] = '7';
    lookup['T'] = lookup['U'] = lookup['V'] = '8';
    lookup['W'] = lookup['X'] = lookup['Y'] = '9';
    lookup['O'] = lookup['Q'] = lookup['Z'] = '0';
}

int main()
{
    init();
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    string phone_number;
    in >> phone_number;
    int word_number;
    in >> word_number;
    vector<string> original_words(word_number);
    vector<string> converted_words(word_number);

    for (int i = 0; i < word_number; i++)
    {
        in >> original_words[i];
        converted_words[i] = original_words[i];
        for (auto &a : converted_words[i])
        {
            a = lookup[a];
        }
    }

    int n = phone_number.size();
    vector<int> dp(n + 1, std::numeric_limits<int>::max());
    vector<int> parent(n + 1, -1);

    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int word_id = 0; word_id < word_number; word_id++)
        {
            const string &word = converted_words[word_id];
            int size = word.size();
            if (dp[i - size] == std::numeric_limits<int>::max() || size > i || dp[i - size] + 1 < dp[i])
                continue;
            if (size <= i && strncmp(phone_number.c_str() + i - size, word.c_str(), size) == 0)
            {
                dp[i] = dp[i - size] + 1;
                parent[i] = word_id;
            }
        }
    }

    if (dp[n] == std::numeric_limits<int>::max())
    {
        out << "No solution" << '\n';
    }
    else
    {

        vector<string> result;
        int pos = n;

        while (pos > 0)
        {
            int word_id = parent[pos];
            result.push_back(original_words[word_id]);
            pos -= converted_words[word_id].size();
        }

        std::reverse(result.begin(), result.end());

        out << result.size() << '\n';
        for (int i = 0; i < result.size(); i++)
        {
            if (i > 0)
                out << " ";
            out << result[i];
        }
        out << '\n';
    }

    in.close();
    out.close();

    return 0;
}