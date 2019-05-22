#include <bits/stdc++.h>
#define Pair pair<int,string>
using namespace std;
struct node
{
    int data;
    double a;
    int left;
    int right;
}tree[1005];
map<string, int>mp;
auto cmp = [](int q, int w) {
    return tree[q].a > tree[w].a;
};
priority_queue<int, vector<int>, decltype(cmp) >q(cmp);

void BFS(int rot)
{
    //BFS
    queue<int>qq;
    qq.push(rot);
    while (!qq.empty())
    {
        int temp = qq.front();
        qq.pop();
        if (tree[temp].left == 0 && tree[temp].right == 0)
            printf("%d ", tree[temp].data);
        if (tree[temp].left != 0)
            qq.push(tree[temp].left);
        if (tree[temp].right != 0)
            qq.push(tree[temp].right);
    }
}

void Code(int rot)
{
    //BFS
    cout << endl << "¹þ·òÂü±àÂëÎª:" << endl;
    queue<Pair>qq;
    qq.push(Pair{ rot,"" });
    while (!qq.empty())
    {
        Pair temp = qq.front();
        qq.pop();
        if (tree[temp.first].left == 0 && tree[temp.first].right == 0)
        {
            printf("%d : ", tree[temp.first].data);
            cout << temp.second << endl;
            mp[temp.second] = tree[temp.first].data;
        }
        if (tree[temp.first].left != 0)
            qq.push(Pair{ tree[temp.first].left ,temp.second + '0' });
        if (tree[temp.first].right != 0)
            qq.push(Pair{ tree[temp.first].right,temp.second + '1' });
    }
    cout << endl;
}
void Decode()
{
    cout << "ÊäÈëÒ»¸ö±àÂë£º" << endl;
    string s, t;
    cin >> s;
    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        t += s[i];
        if (mp[t] != 0)
        {
            printf("%d", mp[t]);
            t.clear();
        }
    }
}
int main()
{
    int n, cnt = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%lf", &tree[cnt].data, &tree[cnt].a);
        q.push(cnt++);
    }
    while (q.size() != 1)
    {
        node rot;
        rot.left = q.top();
        q.pop();
        rot.right = q.top();
        q.pop();
        rot.a = tree[rot.left].a + tree[rot.right].a;
        rot.data = ' ';
        tree[cnt] = rot;
        q.push(cnt++);
    }
    int rot;
    rot = q.top();
    q.pop();
    //BFS(rot);
    Code(rot);
    Decode();
}
/*
8
4 25
8 5
5 4
3 20
2 10
6 4
7 2
1 30
11100000110101101101010010111
*/