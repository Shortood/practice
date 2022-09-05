#include <iostream>
#include <queue>

using namespace std;

// 3197
char hosu[1501][1501];

int main()
{
    int r, c;

    queue<pair<int, int>> now;
    queue<pair<int, int>> next;

    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> hosu[i][j];
            if (hosu[i][j] == '.')
            {
                now.push(make_pair(i, j));   
            }
        }
    }

    while (!now.empty())
    {
        cout << now.front().first << " " << now.front().second << endl;
        now.pop();
    }
}