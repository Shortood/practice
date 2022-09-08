#include <iostream>
#include <queue>

using namespace std;
// 1655
int main()
{

    int n, en;

    priority_queue<int> minq;                            /// 1 2 3
    priority_queue<int, vector<int>, greater<int>> maxq; // 4 5

    cin >> n;
	
    for (int i = 0; i < n; i++)
    {
        cin >> en;

        if (minq.size() > maxq.size()) // 보통
            maxq.push(en);
        else
            minq.push(en);

        if (!maxq.empty() && maxq.top() < minq.top())
        {
           int temp = minq.top();
           int temp2 = maxq.top();
            minq.pop();
            maxq.pop();
            minq.push(temp2);
            maxq.push(temp);
        }
        cout << minq.top() << endl;
    }
}
