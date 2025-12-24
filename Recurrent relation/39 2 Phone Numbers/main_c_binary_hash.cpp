#include <cstdio>
#include <cstring>
#include <limits>
#include <algorithm>
#include <vector>
#include <utility>

const int MAX_PHONE = 100001;
const int MAX_WORDS = 50001;
const int MAX_WORD_LEN = 101;

char lookup[256];
char phone_number[MAX_PHONE];
char original_words[MAX_WORDS][MAX_WORD_LEN];
char converted_words[MAX_WORDS][MAX_WORD_LEN];
int word_lengths[MAX_WORDS];
int dp[MAX_PHONE];
int parent[MAX_PHONE];
std::vector<int> words_id_by_length[MAX_WORD_LEN];

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
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");

    fscanf(in, "%s", phone_number);

    int word_number;
    fscanf(in, "%d", &word_number);

    for (int i = 0; i < word_number; i++)
    {
        fscanf(in, "%s", original_words[i]);
        int len = strlen(original_words[i]);
        word_lengths[i] = len;

        for (int j = 0; j < len; j++)
        {
            converted_words[i][j] = lookup[original_words[i][j]];
        }
        converted_words[i][len] = '\0';
        words_id_by_length[len].push_back(i);
    }
    for (int i = 0; i < MAX_WORD_LEN; i++)
    {
        if (words_id_by_length[i].empty())
            continue;
        std::sort(words_id_by_length[i].begin(), words_id_by_length[i].end(), [](int first, int second)
                  { return strcmp(converted_words[first], converted_words[second]) < 0; });

        words_id_by_length[i].erase(
            std::unique(words_id_by_length[i].begin(), words_id_by_length[i].end(),
                        [&](int first, int second)
                        {
                            return strcmp(converted_words[first], converted_words[second]) == 0;
                        }),
            words_id_by_length[i].end());
    }

    int n = strlen(phone_number);

    for (int i = 1; i <= n; i++)
    {
        dp[i] = std::numeric_limits<int>::max();
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int len = 1; len <= i && len < MAX_WORD_LEN; len++)
        {
            if (dp[i] <= 1)
                break;
            if (dp[i - len] == std::numeric_limits<int>::max())
                continue;
            if (dp[i - len] + 1 >= dp[i])
                continue;
            const char *str = phone_number + i - len;
            auto possible_substr_id = std::lower_bound(words_id_by_length[len].begin(), words_id_by_length[len].end(), str, [&](int word_id, const char *sub)
                                                       { return memcmp(converted_words[word_id], sub, len) < 0; });
            if (possible_substr_id == words_id_by_length[len].end())
                continue;
            if (memcmp(converted_words[*possible_substr_id], str, len) != 0)
                continue;
            dp[i] = dp[i - len] + 1;
            parent[i] = *possible_substr_id;
        }
    }

    if (dp[n] == std::numeric_limits<int>::max())
    {
        fprintf(out, "No solution\n");
    }
    else
    {
        int result_count = dp[n];
        int result_ids[MAX_PHONE];
        int pos = n;

        for (int i = result_count - 1; i >= 0; i--)
        {
            int word_id = parent[pos];
            result_ids[i] = word_id;
            pos -= word_lengths[word_id];
        }

        fprintf(out, "%d\n", result_count);
        for (int i = 0; i < result_count; i++)
        {
            if (i > 0)
                fprintf(out, " ");
            fprintf(out, "%s", original_words[result_ids[i]]);
        }
        fprintf(out, "\n");
    }

    fclose(in);
    fclose(out);

    return 0;
}