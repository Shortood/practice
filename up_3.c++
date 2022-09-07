#include <iostream>
#include <queue>

using namespace std;

// 3197
char hosu[1501][1501];
bool check[1501][1501];

int main()
{
    int r, c;
    int duckcheck = 0;
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    queue<pair<int, int>> Nowduck;   //백조 오늘 갈수 있는 길
    queue<pair<int, int>> Nextduck;  //백조 다음날 갈수 있는 길
    queue<pair<int, int>> Nowwater;  //지금 물
    queue<pair<int, int>> Nextwater; //다음날 녹을 물

    cin >> r >> c;

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> hosu[i][j];
            if (hosu[i][j] == 'L' && duckcheck == 0)
            {
                Nowduck.push(make_pair(i, j));
                duckcheck = 1;
                check[i][j] = 1;
            }
            else if (hosu[i][j] != 'X')
            { //물
                Nowwater.push(make_pair(i, j));
            }
        }
    }
    int x, y;
    int cnt = 0;
    while (1) //될 때까지 반복
    {
        while (!Nowduck.empty()) //백조 만나는지 확인
        {
            x = Nowduck.front().first;
            y = Nowduck.front().second;
            for (int i = 0; i < 4; i++) //상하좌우 얼음 있는지 확인
            {
                int nextx = x + dx[i];
                int nexty = y + dy[i];
                if (nextx >= 0 && nexty >= 0 && nextx < r && nexty < c)
                {
                    if (hosu[nextx][nexty] == 'L' && check[nextx][nexty] == 0) //만나는지 확인
                    {
                        cout << cnt << endl;
                        return 0;
                    }
                    /*상하좌우 확인 물, 다음날 갈 위치 푸시*/
                    if (hosu[nextx][nexty] == '.' && check[nextx][nexty] == 0)
                    {
                        check[nextx][nexty] = 1;
                        Nowduck.push(make_pair(nextx, nexty));
                    }
                    else if (hosu[nextx][nexty] == 'X' && check[nextx][nexty] == 0)
                    {
                        Nextduck.push(make_pair(nextx, nexty));
                        check[nextx][nexty] = 1;
                    }
                }
            }
            Nowduck.pop();
        }

        while (!Nowwater.empty()) //현재 물 확인
        {
            x = Nowwater.front().first;
            y = Nowwater.front().second;
            for (int i = 0; i < 4; i++) //상하좌우 얼음 있는지 확인
            {
                int nextx = x + dx[i];
                int nexty = y + dy[i];
                if (nextx >= 0 && nexty >= 0 && nextx < r && nexty < c)
                {
                    if (hosu[nextx][nexty] == 'X') //녹을 얼음 확인
                    {
                        hosu[nextx][nexty] = '.';
                        Nextwater.push(make_pair(nextx, nexty)); //얼음 넣어주기
                    }
                }
            }
            Nowwater.pop();
        }
        Nowduck = Nextduck;
        Nowwater = Nextwater;
        while (!Nextduck.empty())
        { //다음날 갈 백조 위치 오늘로 바꿔주기
            Nextduck.pop();
        }
        while (!Nextwater.empty())
        { //다음날 녹을 얼음 녹이기
            Nextwater.pop();
        }
        cnt++;
    }
}