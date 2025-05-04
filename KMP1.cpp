#include <bits/stdc++.h>
int next[1000];

void getNext(char *s, int len)
{
    next[0] = 0;
    int k = 0; // k = next[0]
    int i = 1;
    while (i < len)
    {
        if (s[i] == s[k])
        {
            next[i++] = ++k; // next[j+1] = k+1;
        }
        else
        {
            if (k > 0)
                k = next[k - 1]; // k = next[k-1]
            else
            {
                next[i++] = k; // next[j+1] = 0 回溯到头了，找不到相同前缀，则最大相同前后缀长度=0
            }
        }
    }
}

void getNext(char *s, int len)
{
    next[0] = 0;
    int k = 0; // k = next[0]
    for (int i = 1; i < len; i++)
    {
        while (k > 0 && s[i] != s[k])
            k = next[k - 1]; // k = next[k-1]
        if (s[i] == s[k])
            k++;
        next[i] = k; // next[j+1] = k+1 | next[j+1] = 0
    }
}

// 返回模式串T中字串S第一次出现的位置下标，找不到则返回-1
int kmp(char *T, char *S)
{
    int len_T = strlen(T);
    int len_S = strlen(S);
    for (int i = 0, j = 0; i < len_T; i++)
    {
        while (j > 0 && T[i] != S[j])
            j = next[j - 1];
        if (T[i] == S[j])
            j++;
        if (j == len_S)
            return i - len_S + 1;
    }
    return -1;
}

// 返回模式串T中字串S出现的次数，找不到则返回0
int kmp(char *T, char *S)
{
    int sum = 0;
    int len_T = strlen(T);
    int len_S = strlen(S);
    for (int i = 0, j = 0; i < len_T; i++)
    {
        while (j > 0 && T[i] != S[j])
            j = next[j - 1];
        if (T[i] == S[j])
            j++;
        if (j == len_S)
        {
            sum++;
            j = next[j - 1];
        }
    }
    return sum;
}