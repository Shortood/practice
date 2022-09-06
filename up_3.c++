#include <iostream>
#include <queue>

using namespace std;

// 3197
char hosu[1501][1501];
int check[1501][1501];
int main()
{
    int r, c;
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
            if (hosu[i][j] == 'L') //넣으면서 다음날 물 푸시할 수 있는지 확인!!!!
                Nowduck.push(make_pair(i, j));
            else if (hosu[i][j] == '.') //물
                Nowwater.push(make_pair(i, j));
        }
    }
    int x, y;
    int cnt = 0, fl = 0;
    while (1) //될 때까지 반복
    {
        cnt++;
        while (!Nowduck.empty()) //백조 만나는지 확인
        {
            x = Nowduck.front().first;
            y = Nowduck.front().second;
            if (hosu[x - 1][y] == 'L' || hosu[x + 1][y] == 'L' || hosu[x][y + 1] == 'L' || hosu[x][y - 1] == 'L') //만나는지 확인
            {
                fl = 1;
                break;
            }
            //상하좌우 확인 물, 다음날 갈 위치 푸시
            for (int i = 0; i < 4; i++) //상하좌우 확인
            {
                int nextx = x + dx[i];
                int nexty = y + dy[i];
                if (hosu[nextx][nexty] == '.' && check[nextx][nexty] == 0)
                {
                    check[nextx][nexty] = 1;
                    Nowduck.push(make_pair(nextx, nexty));
                }
                else if (hosu[nextx][nexty] == 'X')
                    Nextduck.push(make_pair(nextx, nexty));
            }
            Nowduck.pop();
        }

        if (fl == 1) //만났다면
        {
            cout << cnt << endl;
            break;
        }
        else
        {
            //물 푸시 한거 팝 하면서 주변얼음 녹이기, 다음날 백조가 갈 위치 현재로 넣으면서 녹이기
            while (!Nowwater.empty())
            {
                x = Nowwater.front().first;
                y = Nowwater.front().second;
                for (int i = 0; i < 4; i++) //상하좌우 얼음 있는지 확인
                {
                    int nextx = x + dx[i];
                    int nexty = y + dy[i];
                    if (hosu[nextx][nexty] == 'X') //녹을 얼음 녹이기
                    {
                        hosu[nextx][nexty] = '.'; //물로 만들기
                    }
                }
                Nowwater.pop();
            }
            while (!Nextduck.empty())
            { //다음날 갈 백조 위치 오늘로 바꿔주기
                Nowduck.push(make_pair(Nextduck.front().first, Nextduck.front().second));
                Nextduck.pop();
            }
            //백조가 이미 간 물들은 그냥 바로 팝
        }
    }
}