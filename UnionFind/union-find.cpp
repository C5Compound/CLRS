/**
 *  poj1182 AC
 *  并查集实现
 *  并查集实现可以用链表，也可以用森林
 *  有了优化操作，采用按秩合并和路径压缩
 *  可以达到O(α(n))的时间复杂度
 */
#include <cstdio>
using namespace std;

int father[50002];
/**
 *  0表示father[x]和x是同类
 *  1表示father[x]吃x
 *  2表示x吃father[x]
 */
int rank[50002];

void Make_Set(int x)
{
    father[x] = x;
    rank[x] = 0;
}

// 查找并回溯路径压缩
int Find_Set(int x)
{
    int t;
    if (father[x] != x) {
        t = father[x];
        father[x] = Find_Set(father[x]);
        rank[x] = (rank[t] + rank[x]) % 3;
    }
    return father[x];
}

// 把x所在集合合并到y所在集合
void Union(int x, int y, int w)
{
    int fx = Find_Set(x), fy = Find_Set(y);
    father[fx] = fy;
    rank[fx] = (rank[y] - rank[x] + 3 + w) % 3;
}

int main()
{
    int x, fx, y, fy, n, k, w, lies = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        Make_Set(i);
    }
    while (k--) {
        scanf("%d%d%d", &w, &x, &y);
        if (x > n || y > n || (w == 2 && x == y)) {
            ++lies;
        } else {
            fx = Find_Set(x);
            fy = Find_Set(y);
            if (fx == fy) {
                if ((rank[x] - rank[y] + 3) % 3 != w - 1) {
                    ++lies;
                }
            }
            else {
                Union(x, y, w - 1);
            }
        }
    }
    printf("%d\n", lies);
    return 0;
}
