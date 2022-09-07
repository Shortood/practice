#include <iostream>

using namespace std;
int n, k;
// 11401
//(n, k) = (n-1, k-1) + (n-1, k)
int bio(int n, int k)
{
    // cout << "chek" << n << " " << k << endl;
    if (k < 0 || k > n)
        return 0;
    else if (k == 1)
    {
        cout << "chek" << n << endl;
        return n;
    }
    else
        return bio(n - 1, k - 1) % 1000000007 + bio(n - 1, k) % 1000000007;
}

int main()
{
    cin >> n >> k;
    if (n - k < k)
        k = n - k;
    
    cout << bio(n, k) << endl;
    cout << "done" << endl;
}
/*
5 2
4 1   4 2  = 4 + 4 2 = 4 +6
3 1 3 2 = 3 + 3 2 = 3+ 3
2 1 2 2 = 2 + 2 2 = 2 + 1
1 1 1 2 = 1 + 0

*/