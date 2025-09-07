#include <iostream>

int main()
{
    unsigned arr_size;
    std::cin >> arr_size;
    unsigned short* arr = new unsigned short[arr_size];
    for (unsigned i = 0; i < arr_size; i++)
    {
        std::cin >> arr[i];
    }

    //Было
    // if (arr_size == 1)
    // {
    //     std::cout << "1\n1";
    // }

    //А должно быть
    if (arr_size == 1)
    {
        std::cout << arr[0] << "\n1";
        return 0;
    }

    if (arr_size < 3)
    {
        std::cout << "-1";
        return 0;
    }

    if(arr_size == 3)
    {
        std::cout << arr[0] + arr[2];
        std::cout << "\n1 3";
        return 0;
    }

    if(arr_size == 4)
    {
        std::cout << arr[0] + arr[3];
        std::cout << "\n1 4";
        return 0;
    }
    
    if(arr_size ==5)
    {
        std::cout << arr[0] + arr[2]+ arr[4];
        std::cout << "\n1 3 5";
        return 0;
    }

    long* arr_solution = new long[arr_size]{-1};
    arr_solution[arr_size-1] = 1;
    arr_solution[arr_size-3] = arr[arr_size-1] + arr[arr_size-3];
    arr_solution[arr_size-4] = arr[arr_size-1] + arr[arr_size-4]; 

    for (int i = arr_size - 3; i >= 0; i--)
    {
        if(i-2>=0 && arr_solution[i-2] < arr_solution[i]+ arr[i-2])
        {
            arr_solution[i-2] = arr_solution[i] + arr[i-2];
        }
        if(i-3>=0 && arr_solution[i-3] < arr_solution[i]+ arr[i-3])
        {
            arr_solution[i-3] = arr_solution[i] + arr[i-3];
        }
    }
    std::cout << arr_solution[0] << "\n";

    int i = 0;
    while(i <= arr_size-3)
    {
        std::cout << i+1 <<" ";
        if(arr_solution[i+3] > arr_solution[i+2])
        {
            i+= 3;
        }
        else
        {
            i+=2;
        }
    }
    
    std::cout << arr_size << "\n";
    
}