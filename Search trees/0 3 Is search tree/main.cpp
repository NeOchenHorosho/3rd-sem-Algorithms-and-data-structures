#include <fstream>
#include <vector>
#include <limits>
struct node_info
{
    long long node_val;
    long long node_par_num;
    char direction;
    long long upper_limit;
    long long lower_limit;
};

long long main()
{
    std::ifstream in ("bst.in");
    std::ofstream out ("bst.out");
    size_t nodes_num;
    in >> nodes_num;
    if(nodes_num == 1)
    {
        out << "YES";
        out.close();
        return 0;
    }
    std::vector<node_info> nodes(nodes_num);
    in >> nodes[0].node_val;
    nodes[0].upper_limit = std::numeric_limits<long long>::max();
    nodes[0].lower_limit = std::numeric_limits<long long>::min();
    for (size_t i = 1; i < nodes_num; i++)
    {
        in >> nodes[i].node_val;
        in >> nodes[i].node_par_num;
        nodes[i].node_par_num--;
        in >> nodes[i].direction;
        if(nodes[i].direction == 'L')
        {
            nodes[i].lower_limit = nodes[nodes[i].node_par_num].lower_limit;
            nodes[i].upper_limit = nodes[nodes[i].node_par_num].node_val;
        }
        if(nodes[i].direction == 'R')
        {
            nodes[i].lower_limit = nodes[nodes[i].node_par_num].node_val;
            nodes[i].upper_limit = nodes[nodes[i].node_par_num].upper_limit;
        }
        if(nodes[i].node_val >= nodes[i].upper_limit || nodes[i].node_val < nodes[i].lower_limit)
        {
            out << "NO";
            out.close();
            return 0;
        }
    }
    out << "YES";
    out.close();
    return 0;
}