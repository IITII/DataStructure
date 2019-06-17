#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> v[1000];
int vis[1005];
int n, m;
queue<int> q;
void dfs(int x, int y) {
    if (y == n) {
        return;
    }
    if (vis[x] == 1) {
        return;
    }
    vis[x] = 1;
    cout << x << " ";
    for (int i = 0; i < v[x].size(); i++) {
        if (vis[v[x][i]] == 0) {
            dfs(v[x][i], y + 1);
        }
    }
}

void bfs(int x) {
    memset(vis, 0, sizeof(vis));
    if (vis[x] == 0) {
        cout << x;
        q.push(x);
        vis[x] = 1;
    }
    while (!q.empty()) {
        x = q.front();
        q.pop();
        for (int i = 0; i < v[x].size(); i++) {
            if (vis[v[x][i]] == 0) {
                vis[v[x][i]] = 1;
                cout << " " << v[x][i];
                q.push(v[x][i]);
            }
        }
    }

}

int main() {
    int x, y;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 1);
    printf("\n");
    bfs(1);
}