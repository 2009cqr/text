#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define CLOSE ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define isd(c) ('0' <= (c) && (c) <= '9')
#define isa(c) ('a' <= (c) && (c) <= 'z')
#define isA(c) ('A' <= (c) && (c) <= 'Z')
#define mem(a, b) memset(a, b, sizeof a);
#define N 1005
#define M 2000005
#define mod 1000000007
#define inf 0x3f3f3f3f
#define infll 0x3f3f3f3f3f3f3f3f
#define ll long long
#define PI acos(-1)
#define endl "\n"
#define bug cout << endl << " .....here!...." << endl;
//#pragma GCC optimize("O3")
using namespace std;
int n, m, f[N];
struct Node
{
    int x, y, l;
    bool used;
} node[M];
struct Edge
{
    int to, next, w;
} edge[M * 2];
int head[N], cnt;
void add(int a, int b, int l)
{
    edge[cnt].to = b;
    edge[cnt].w = l;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}
int max1[N][N], max2[N][N];
void init()
{
    cnt = 0;
    memset(head, -1, sizeof head);
    for (int i = 1; i <= n; i++)
        f[i] = i;
}
int cmp(Node a, Node b)
{
    return a.l < b.l;
}
int Find(int x)
{
    if (x == f[x])
        return f[x];
    return f[x] = Find(f[x]);
}
ll kruskal()
{
    sort(node + 1, node + 1 + m, cmp);
    int k = 0;
    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        if (k == n - 1)
            return ans;
        int xx = Find(node[i].x);
        int yy = Find(node[i].y);
        if (xx == yy)
            continue;
        f[xx] = yy;
        ans += node[i].l;
        k++;
        node[i].used = 1;
        add(node[i].x, node[i].y, node[i].l);
        add(node[i].y, node[i].x, node[i].l);
    }
    return ans;
}
void dfs(int s, int u, int fa, int maxx, int maxy)
{ // s起点，u当前点，fa当前点的父节点，maxx最大值，maxy次大值
    max1[s][u] = maxx;
    max2[s][u] = maxy;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int d1 = maxx, d2 = maxy;
        int v = edge[i].to;
        int w = edge[i].w;
        if (v == fa)
            continue;
        if (w > d1)
            d1 = w, d2 = maxx;
        else if (w > d2 && w < d1)
            d2 = w;
        dfs(s, v, u, d1, d2);
    }
}
int main()
{
    cin >> n >> m;
    init();
    for (int i = 1; i <= m; i++)
        cin >> node[i].x >> node[i].y >> node[i].l;
    ll Min = kruskal();
    // cout<<Min<<endl;
    for (int i = 1; i <= n; i++)
        dfs(i, i, -1, -inf, -inf);
    ll ans = infll;
    for (int i = 1; i <= m; i++)
    {
        if (node[i].used == 0)
        {
            if (node[i].l > max1[node[i].x][node[i].y])
                ans = min(ans, Min - max1[node[i].x][node[i].y] + node[i].l);
            else if (node[i].l > max2[node[i].x][node[i].y])
                ans = min(ans, Min - max2[node[i].x][node[i].y] + node[i].l);
        }
    }
    cout << ans << endl;
    return 0;
}
