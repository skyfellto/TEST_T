#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * 构建KMP算法的next数组
 * @param pattern 模式字符串
 * @return next数组，next[i]表示pattern[0..i]的最长公共前后缀长度
 */
vector<int> buildNext(const string &pattern)
{
    int n = pattern.size();
    vector<int> next(n, 0);
    for (int i = 1, j = 0; i < n; i++)
    {
        // 当字符不匹配时，利用next数组回退j
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = next[j - 1];
        }
        // 字符匹配时，j向前移动
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        next[i] = j;
    }
    return next;
}

/**
 * KMP算法匹配主函数
 * @param text 主字符串
 * @param pattern 模式字符串
 * @return 所有匹配位置的起始下标（从0开始）
 */
vector<int> kmpSearch(const string &text, const string &pattern)
{
    vector<int> matches;
    if (pattern.empty() || text.size() < pattern.size())
    {
        return matches; // 边界情况直接返回
    }

    vector<int> next = buildNext(pattern);
    int n = text.size(), m = pattern.size();

    for (int i = 0, j = 0; i < n; i++)
    {
        // 当前字符不匹配时，调整j的位置
        while (j > 0 && text[i] != pattern[j])
        {
            j = next[j - 1];
        }
        // 当前字符匹配，j向前移动
        if (text[i] == pattern[j])
        {
            j++;
        }
        // 完全匹配成功，记录位置并重置j
        if (j == m)
        {
            matches.push_back(i - m + 1);
            j = next[j - 1]; // 允许重叠匹配
        }
    }
    return matches;
}

// 测试示例
int main()
{
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    vector<int> pos = kmpSearch(text, pattern);

    if (pos.empty())
    {
        cout << "未找到匹配" << endl;
    }
    else
    {
        cout << "匹配起始位置：";
        for (int p : pos)
            cout << p << " ";
        cout << endl;
    }
    return 0;
}