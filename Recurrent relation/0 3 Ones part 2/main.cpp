#include <iostream>
#include <cmath>
const int MOD = 1000000007;
//Внимание!!!1 ПРИ компиляции на винде (irunner2 на винде хостится) нужно заменить long на long long, мне лень было писать макросы
long mod_pow(long n, int power)
{
    if(power == 0)
    {
        return 1;
    }
    if(power%2==0)
    {
        return mod_pow((n*n)%MOD, power/2);
    }
    return n*mod_pow((n*n)%MOD, (power-1)/2)%MOD;
}
int main()
{
    int n, k;
    std::cin >> n >> k;
    long numerator = 1, denomenator =1;
    for(int i = k+1; i <= n; i++)
    {
        numerator =(numerator*i)%MOD;
    } 
    //по следствию из малой теоремы ферма a^-1 сравнимо с a^m-2 по модулю m 
    for(int i =1; i <= n-k; i++)
    {
        denomenator = (denomenator*mod_pow(i, MOD-2))%MOD;
    }
    long result = numerator*denomenator%MOD;
    std::cout << result;
}