#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 120;
vector<int> graph[N];
int d[N];
int price[N];
int n, s = 0, f;

int dijkstra() {
    priority_queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        int x = q.top().second, pd = -q.top().first;
        q.pop();
        if (pd > d[x]) continue;

        for (auto y : graph[x]) {
            if (d[y] > d[x] + price[x]) {
                d[y] = d[x] + price[x];
                q.push({-d[y], y});
            }
        }
    }
}
