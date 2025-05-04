#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge
{
    int u, v, w;
    // 重载运算符，用于按边权从小到大排序
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
};

vector<Edge> edges; // 存储所有边
int parent[5005];   // 并查集父节点数组（根据题目最大节点数调整）
int n, m;

// 并查集：查找根节点（路径压缩优化）
int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// 并查集：合并两个集合（按秩合并优化）
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        parent[y] = x; // 简单合并，可按需添加秩优化
}

ll kruskal()
{
    // 1. 按边权升序排序
    sort(edges.begin(), edges.end());

    // 2. 初始化并查集
    for (int i = 1; i <= n; i++)
        parent[i] = i;

    ll total = 0;
    int edge_cnt = 0; // 已选边数

    // 3. 遍历所有边
    for (auto &e : edges)
    {
        if (find(e.u) != find(e.v))
        {
            unite(e.u, e.v);
            total += e.w;
            edge_cnt++;
            if (edge_cnt == n - 1)
                break; // 生成树已形成
        }
    }

    // 判断是否连通
    return (edge_cnt == n - 1) ? total : -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        edges.push_back({x, y, z}); // 无向图只需添加一次
    }

    ll ans = kruskal();
    if (ans == -1)
        cout << "orz\n";
    else
        cout << ans << "\n";

    return 0;
}