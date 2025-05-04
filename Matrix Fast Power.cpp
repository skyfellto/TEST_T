#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

typedef long long int ll;
const int mod = (int)1e9 + 7;
const int MAX_N = 1e3;
int A[MAX_N][MAX_N], res[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

// A = A*B
void MXMP(int a[][MAX_N], int b[][MAX_N], int n)
{
    // 重置临时矩阵temp
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            temp[i][j] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                temp[i][j] = (temp[i][j] + (a[i][k] * b[k][j]) % mod) % mod; // 防止超界

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            a[i][j] = temp[i][j];
}

// A = A**x
void PowerMod(int A[][MAX_N], int n, int x) // x为次幂，n为矩阵行/列
{
    memset(res, 0, sizeof(res));
    for (int i = 1; i <= n; i++)
        res[i][i] = 1; // 初始化为单位矩阵
    while (x)
    {
        if (x & 1)
            MXMP(res, A, n);
        MXMP(A, A, n);
        x >>= 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            A[i][j] = res[i][j];
}

int main()
{
    // 读入A矩阵
    int n, x;
    cin >> n >> x; // n行n列，x为次幂
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> A[i][j];
    //_______________________________
    PowerMod(A, n, x);
    // 检查A矩阵
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    //________________________________

    return 0;
}