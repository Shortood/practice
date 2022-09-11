#include <iostream>

using namespace std;
long long n, k;
// 11401
//(n, k) = (n-1, k-1) + (n-1, k)
long long fac(int n, int k)
{
    long long tmp = 1;
    for (int i = n; i <= k; i++)
    {
        tmp = tmp * i % 1000000007;
    }

    return tmp;
}

long long pow(int x, int y)
{

    if (y == 1)
        return x % 1000000007;
    long long half;
    half = pow(x, y / 2);
    if (y % 2 == 1)
        return (half * half % 1000000007) * x % 1000000007;
    else
    {
        return half * half % 1000000007;
    }
}

int main()
{
    cin >> n >> k;
    if (n - k < k)
        k = n - k;

    cout << (fac(n - k + 1, n) * pow(fac(1, k), 1000000007 - 2)) % 1000000007 << endl;
    // cout << "done" << endl;
}
