#include <iostream>
using namespace std;
/*
函数名：dijkstra()  迪科斯彻最短路径算法
参数：vs：源点的索引;f：终点的索引;
      pre[]：前驱数组,即pre[i]为从vs到i最短路径时,i前面那个顶点的索引
      dist[]：距离数组，即dist[i]是vs到i的最短路径的长度
全局变量q：点的数量
功能：算出从源点下标vs到其余点最短路径,轨迹记录在pre[],距离记录在dist[]。
*/
const int INF = 0x3f3f3f3f;
const int q = 1e3 + 10;
int martix[q][q];

void dijkstra(int vs, int prev[], int dist[], int f)
{

    int i, j, k;
    int min;
    int tmp;
    int flag[q]; // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
                 /* 1.  初始化*/
    for (i = 0; i < q; i++)
    {
        flag[i] = 0;             // 顶点i的最短路径还没获取到。
        prev[i] = vs;            // 顶点i的前驱顶点为0。
        dist[i] = martix[vs][i]; // 顶点i的最短路径为vs到i的权。
    }

    flag[vs] = 1; // 对顶点vs自身进行初始化
    dist[vs] = 0;

    /* 2.  遍历q-1次，每次找出vs到另一个顶点的最短路径 */
    for (i = 1; i < q; i++)
    {

        /* 2.1 在未获取最短路径的顶点中，找到离vs最近的顶点k */
        min = INF;
        for (j = 0; j < q; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            // 若从vs到顶点j距离小于min,而且从vs到j的最短路径还未获取。
            {
                min = dist[j]; // 改变最近距离
                k = j;         // 记录j
            }
        }

        /* 2.2  对刚刚已找到最短距离的顶点k进行标记判断     */
        flag[k] = 1; // 标记顶点k,dist[k]已确定。
        if (k == f)  // 判断k是否是终点索引,若是则退出
            break;

        /*  2.3   已知顶点k的最短路径后,更新未获取最短路径的顶点的最短路径和前驱顶点   */
        for (j = 0; j < q; j++)
        {
            tmp = (martix[k][j] == INF ? INF : (min + martix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp < dist[j]))                      // 若j还不是最短距离且从k到j距离比记录的距离短
            {
                // 更新k的前驱和最短距离
                prev[j] = k;
                dist[j] = tmp;
            }
        }
    }
}
