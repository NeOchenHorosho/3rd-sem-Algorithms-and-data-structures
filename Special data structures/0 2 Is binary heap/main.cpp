#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int size_of_heap;
    in >> size_of_heap;
    vector<int> heap_candidate(size_of_heap);
    for (int i = 0; i < size_of_heap; i++)
        in >> heap_candidate[i];
    for(int i = 0; i < size_of_heap; i++)
    {
        if(2*i+1 < size_of_heap)
        {
            if(heap_candidate[2*i+1] < heap_candidate[i])
            {
                out << "No";
                return 0;
            }
        }
        if(2*i+2 < size_of_heap)
        {
            if(heap_candidate[2*i+2] < heap_candidate[i])
            {
                out << "No";
                return 0;
            }
        }
    } 
    out << "Yes";
    return 0;
}