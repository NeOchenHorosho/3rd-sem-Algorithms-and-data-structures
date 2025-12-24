#include <cstdio>
#include <cstring>
#include <limits>
#include <algorithm>

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

struct TrieNode
{
    TrieNode *children[10] = {nullptr};
    int word_id = -1;
};

struct Trie
{
    TrieNode *root;
    Trie() : root(new TrieNode) {}

    void insert(char *word, int word_id)
    {
        TrieNode *curr_node = root;
        int len = strlen(word);

        std::reverse(word, word + len);

        for (int i = 0; i < len; ++i)
        {
            int digit = word[i] - '0';
            if (curr_node->children[digit] == nullptr)
            {
                curr_node->children[digit] = new TrieNode;
            }
            curr_node = curr_node->children[digit];
        }
        curr_node->word_id = word_id;
    }
};

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
    Trie trie;
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
        if(strstr(phone_number, converted_words[i]) == NULL) continue;
        trie.insert(converted_words[i], i);
    }

    int n = strlen(phone_number);

    for (int i = 1; i <= n; i++)
    {
        dp[i] = std::numeric_limits<int>::max();
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        TrieNode *curr_node = trie.root;

        for (int len = 1; len <= i; len++)
        {
            int digit = phone_number[i - len] - '0';

            if (curr_node->children[digit] == nullptr)
            {
                break;
            }

            curr_node = curr_node->children[digit];

            if (curr_node->word_id != -1)
            {
                int prev_pos = i - len;

                if (dp[prev_pos] != std::numeric_limits<int>::max())
                {

                    if (dp[prev_pos] + 1 < dp[i])
                    {
                        dp[i] = dp[prev_pos] + 1;
                        parent[i] = curr_node->word_id;
                    }
                }
            }
        }
    }

    if (dp[n] == std::numeric_limits<int>::max())
    {
        fprintf(out, "No solution\n");
    }
    else
    {
        int result_count = dp[n];
        int result_ids[MAX_WORDS];
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