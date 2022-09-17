#include <iostream>

using namespace std;

// 10830
int hag[6][6] = {0,}, hag2[6][6] = {0,};

int result(int x)
{
    if (x % 2 == 0)
        return result(x / 2);
}

int mul(int n){

}

int main()
{

    int n, b;

    cin >> n >> b;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cin >> hag[i][j];
            hag2[i][j]=hag[i][j];
        }
    }

    result(b);
}