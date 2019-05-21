//��Ŀ����
//����һ��n* m���Թ������б��Ϊ1��Ϊ�ϰ������Ϊ0��Ϊ����ͨ�еĵط���
//
//�Թ������Ϊ���Ͻǣ�����Ϊ���½ǣ�ֻ�ܴ�һ��λ���ߵ���������ϡ��¡������ĸ�����֮һ��
//
//�����˳���߳��Թ������YES���������NO
//
//�������� :
//����һ��n��m�е��Թ�(0 < n <= 100��0 < m <= 100)
//    ������� :
//    ���YES��NO
//    ʾ��1
//    ����
//    ����
//    2 2
//    0 1
//    1 0
//    ���
//    ����
//    NO
//    ʾ��2
//    ����
//    ����
//    4 6
//    0 1 0 0 0 0
//    0 0 0 1 0 0
//    0 0 1 0 0 1
//    1 1 0 0 0 0
//    ���
//    ����
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