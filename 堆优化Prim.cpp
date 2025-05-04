#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii; // (权重, 节点)

const int INF = 0x3f3f3f3f;
const int MAX_N = 5005; // 根据题目调整最大节点数
vector<pii> adj[MAX_N]; // 邻接表
int dist[MAX_N];        // 存储节点到生成树的最小边权
bool vis[MAX_N];        // 标记节点是否已加入生成树
int n, m;

ll prim()
{
    fill(dist, dist + n + 1, INF);
    fill(vis, vis + n + 1, false);
    dist[1] = 0; // 从节点 1 开始

    priority_queue<pii, vector<pii>, greater<pii>> pq; // 小根堆
    pq.push({0, 1});

    ll total = 0;
    int node_cnt = 0; // 已加入生成树的节点数

    while (!pq.empty())
    {
        auto [w, u] = pq.top();
        pq.pop();

        if (vis[u])
            continue; // 已处理过的节点直接跳过
        vis[u] = true;
        total += w;
        node_cnt++;

        // 遍历邻接边，更新未访问节点的最小边权
        for (auto &[v, weight] : adj[u])
        {
            if (!vis[v] && weight < dist[v])
            {
                dist[v] = weight;
                pq.push({dist[v], v});
            }
        }
    }

    return (node_cnt == n) ? total : -1;
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
        adj[x].emplace_back(y, z); // 无向图双向添加
        adj[y].emplace_back(x, z);
    }

    ll ans = prim();
    if (ans == -1)
        cout << "orz\n";
    else
        cout << ans << "\n";

    return 0;
}