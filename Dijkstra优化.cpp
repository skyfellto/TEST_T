#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int N, M;
typedef struct Edge
{
    int index;
    int value;
} Edge;
// 自定义对运算符的重载
struct cmp
{
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second; // 小顶堆
    }
};

void dijkstra(priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> &q, vector<list<Edge>> &graph, vector<int> &minDist, vector<int> &isvisited)
{
    while (!q.empty())
    { // 第一步是找到目前距离起点最近的没有被访问过的点，如果堆顶杯被访问过则直接弹出
        int index = q.top().first;
        int minlen = q.top().second;
        q.pop();
        if (isvisited[index] == 1) // 被访问过
        {
            continue;
        }
        // 访问该点
        isvisited[index] = 1;
        // 第三步要更新最近的路径了
        for (auto x : graph[index])
        {
            // 遍历index节点可以到达的点x，或者说边
            if (isvisited[x.index] == 0 && minDist[x.index] > minDist[index] + x.value)
            {
                minDist[x.index] = minDist[index] + x.value;
                q.push(pair<int, int>(x.index, minDist[x.index])); // 每次去更新minDist时其实无论更没更新成功都可以将"新"的minDist[i]与i进堆进行维护，因为一开始只有起点自己是有0的最短路径所以只入堆了起点，但后面开始从index开始遍历index连接的节点时，这些节点也要入堆这样后面小顶堆返回的值才是整个图中最短路径的节点
            } // q.push(pair<int,int>(x.index,minDist[x.value]));均可
        }
    }
}

int main()
{
    cin >> N >> M;
    vector<list<Edge>> graph(N + 1); // 使用邻接表进行储存
    for (int i = 0; i < M; i++)
    {
        int s, e, v;
        cin >> s >> e >> v;
        Edge edge;
        edge.index = e;
        edge.value = v;
        graph[s].push_back(edge);
    }
    // 这里要清楚优先队列存的什么，因为优先队列是对每次遍历n的顺序查找的优化，
    // 变成有些队列直接返回那个离起点最近的没被访问过的点,所以作为小顶堆存的是minDist的值以及节点编号，故不能存Edge进去，使用pair
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q; // first存节点编号，second存目前距离起点的最小值
    vector<int> minDist(N + 1, INT_MAX);
    vector<int> isvisited(N + 1, 0);
    // 初始化，注意这里需要同时初始化优先队列和minDist数组
    minDist[1] = 0;
    q.push(pair<int, int>(1, 0));
    // q.push()
    dijkstra(q, graph, minDist, isvisited);
    if (minDist[N] == INT_MAX)
    {
        cout << -1;
    }
    else
    {
        cout << minDist[N];
    }
    return 0;
}