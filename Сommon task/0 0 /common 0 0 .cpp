#include <fstream>
#include <set>
#include <numeric>

int main()
{
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");
    long long res = 0;
    long long tmp;
    std::set<long long> tema; 
    while (in >> tmp)
    {
        tema.insert(tmp);
    }
    for(auto i: tema)
    {
        res+= i;
    }
    out << res;
    out.close();
}