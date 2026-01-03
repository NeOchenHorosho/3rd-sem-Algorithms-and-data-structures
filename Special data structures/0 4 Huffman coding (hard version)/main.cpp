#include <fstream>
#include <queue>
using namespace std;
long long find_sum_and_pop(queue<long long> &left, queue<long long> &right)
{
    long long sum = 0;
    for (long long i = 0; i < 2; i++)
    {
        if (left.empty())
        {
            sum += right.front();
            right.pop();
            continue;
        }
        if (right.empty())
        {
            sum += left.front();
            left.pop();
            continue;
        }
        if (right.front() > left.front())
        {
            sum += left.front();
            left.pop();
        }
        else
        {
            sum += right.front();
            right.pop();
        }
    }
    return sum;
}
int main()
{
    ifstream in("huffman.in");
    ofstream out("huffman.out");
    long long char_num;
    in >> char_num;
    queue<long long> char_freqs;
    for (long long i = 0; i < char_num; i++)
    {
        long long freq;
        in >> freq;
        char_freqs.push(freq);
    }
    long long sum = 0;
    queue<long long> nodes_freqs;
    for (long long i = 0; i < char_num - 1; i++)
    {
        long long node_freq = find_sum_and_pop(char_freqs, nodes_freqs);
        sum += node_freq;
        nodes_freqs.emplace(node_freq);
    }
    out << sum;
}