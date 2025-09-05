#include <iostream>
#include <string>
#include <math.h>
using namespace std;

size_t binary_search_left(long long* arr, size_t arr_size,  long long key)
{
    size_t l_bound = 0, r_bound = arr_size, mid;
    while(l_bound != r_bound)
    {
        mid = (l_bound + r_bound)/2;
        if (arr[mid] < key)
        {
            l_bound = mid + 1;
        }
        else
        {
            r_bound = mid;
        }
    }
    return l_bound;
}

size_t binary_search_right(long long* arr, size_t arr_size, long long key)
{
    size_t l_bound = 0, r_bound = arr_size, mid;
    while(l_bound != r_bound)
    {
        mid = (l_bound + r_bound)/2; //тоже самое что floor
        if (arr[mid] > key)
        {
            r_bound = mid;
        }
        else
        {
            l_bound = mid+1;
        }
    }
    return l_bound;
}


int main()
{
    size_t arr_size, reqs_size;
    cin >> arr_size;
    long long* arr = new long long[arr_size];
    for(size_t i = 0; i < arr_size; i++)
    {
        cin >> arr[i];
    }   
    cin >> reqs_size;
    long long* reqs = new long long[reqs_size];
    for (size_t i = 0; i < reqs_size; i++)
    {
        cin >> reqs[i];
    }
    int tmp_l, tmp_r;
    for (size_t i = 0; i < reqs_size; i++)
    {
        tmp_l = binary_search_left(arr, arr_size, reqs[i]);
        tmp_r = binary_search_right(arr, arr_size, reqs[i]);
        cout << (arr[tmp_l] == reqs[i] && tmp_l < arr_size) << " " << tmp_l << " " << tmp_r << "\n";
    }
    
}