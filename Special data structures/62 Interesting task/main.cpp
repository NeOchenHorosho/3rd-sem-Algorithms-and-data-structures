#include <iostream>
#include <cstring>
#include <utility>
using namespace std;
const int MAX_NUMS = 2000000;

int evens[MAX_NUMS];
int nums[MAX_NUMS];
long long merge_sort_and_count_inversions(int *arr, int size)
{
    long long num_of_inversions = 0; // здесь точно long long
    if (size <= 1)
    {
        return num_of_inversions;
    }
    int middle_idx = size / 2;
    num_of_inversions += merge_sort_and_count_inversions(arr, middle_idx);
    num_of_inversions += merge_sort_and_count_inversions(arr + middle_idx, size - middle_idx);
    int *left_copy = (int *)malloc(sizeof(int) * middle_idx);
    int *right_copy = (int *)malloc(sizeof(int) * (size - middle_idx));
    memcpy(left_copy, arr, sizeof(int) * middle_idx); // наверное можно было общий буфер вместо постоянной аллокации
    memcpy(right_copy, arr + middle_idx, sizeof(int) * (size - middle_idx));

    int i = 0, l = 0, r = 0;
    while (l < middle_idx && r < size - middle_idx)
    {
        if (left_copy[l] <= right_copy[r])
        {
            arr[i++] = left_copy[l++];
        }
        else
        {
            arr[i++] = right_copy[r++];
            num_of_inversions += middle_idx - l;
        }
    }
    while (l < middle_idx)
    {
        arr[i++] = left_copy[l++];
    }
    while (r < size - middle_idx)
    {
        arr[i++] = right_copy[r++];
    }
    return num_of_inversions;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int nums_size;
    cin >> nums_size;
    int curr_evens = 0;
    for (int i = 0; i < nums_size; i++)
    {
        int temp;
        cin >> temp;
        nums[i] = temp;
        if (temp % 2 == 0)
        {
            evens[curr_evens] = temp;
            curr_evens++;
        }
    }

    long long inversions = merge_sort_and_count_inversions(evens, curr_evens);
    int consecutive_evens = 0;
    for (int i = 0; i < nums_size; i++)
    {
        if (nums[i] % 2 == 0)
        {
            consecutive_evens++;
        }
        else if (consecutive_evens > 0)
        {
            inversions -= merge_sort_and_count_inversions(nums + i - consecutive_evens, consecutive_evens);
            consecutive_evens = 0;
        }
    }

    if (consecutive_evens > 0)
    {

        inversions -= merge_sort_and_count_inversions(nums + nums_size - consecutive_evens, consecutive_evens);
    }
    cout << inversions;
}