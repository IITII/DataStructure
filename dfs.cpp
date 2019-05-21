//题目描述
//给出一个n* m的迷宫，其中标记为1的为障碍，标记为0的为可以通行的地方。
//
//迷宫的入口为左上角，出口为右下角，只能从一个位置走到这个它的上、下、左、右四个方向之一。
//
//如果能顺利走出迷宫就输出YES，否则输出NO
//
//输入描述 :
//输入一个n行m列的迷宫(0 < n <= 100，0 < m <= 100)
//    输出描述 :
//    输出YES或NO
//    示例1
//    输入
//    复制
//    2 2
//    0 1
//    1 0
//    输出
//    复制
//    NO
//    示例2
//    输入
//    复制
//    4 6
//    0 1 0 0 0 0
//    0 0 0 1 0 0
//    0 0 1 0 0 1
//    1 1 0 0 0 0
//    输出
//    复制
//    YES
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 100 + 10;

int n, m;
int a[maxn][maxn];
int dir[4][2] = { -1,0,1,0,0,1,0,-1 };
int flag[maxn][maxn];
int Flag = 0;

void dfs(int x, int y)
{
    if (x == n - 1 && y == m - 1) {
        Flag = 1; return;
    }
    for (int i = 0; i < 4; i++) {
        int Dx = x + dir[i][0];
        int Dy = y + dir[i][1];
        if (Dx >= 0 && Dx < n && Dy >= 0 && Dy < m && flag[Dx][Dy] == 0 && a[Dx][Dy] == 0) {
            flag[Dx][Dy] = 1;
            dfs(Dx, Dy);
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    }
    dfs(0, 0);
    if (Flag) cout << "YES" << endl;
    else cout << "NO" << endl;
}