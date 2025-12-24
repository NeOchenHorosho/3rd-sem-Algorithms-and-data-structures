#include <fstream>
#include <vector>

using namespace std;

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n;
    in >> n;
    if(n == 1)
    {
        out << 1;
        out.close();
        return 0;
    }
    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        in >> arr[i]; 

    vector<int> dp;
    dp.push_back(arr[0]);
    for (size_t i = 1; i < arr.size(); i++)
    {
        if(arr[i] > dp.back())
        {
            dp.push_back(arr[i]);
        }
        else
        {
            *std::lower_bound(dp.begin(), dp.end(), arr[i]) = arr[i];
        }
    }
    out << dp.size();
    out.close();
}