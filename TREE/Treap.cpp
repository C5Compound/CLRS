/**
 * 用数组初始化Treap
 */
#include <algorithm>
using namespace std;

struct node_t
{
    int a, b;
    node_t *left, *right;
};

struct pair_t
{
    int a, b;
};

node_t* recurBuild(pair_t* pair, int start, int end) 
{
    if (start >= end) {
        return NULL;
    }
    // 在子序列中找出最大的b的索引
    int i = start, imax = start;
    for (; i < end; ++i) {
        if (pair[i].b > pair[imax].b) {
            imax = i;
        }
    }
    node_t* root = new node_t;
    root->a = pair[imax].a;
    root->b = pair[imax].b;
    root->left = recurBuild(pair, start, imax);
    root->right = recurBuild(pair, imax + 1, end);
    return root;
}

node_t* build(pair_t* pair, int n) 
{
    if (pair == NULL || n <= 0) {
        return NULL;
    }
    // 按a升序排序
    sort(pair, pair + n, [](pair_t &x, pair_t &y){return x.a < y.a; });
    return recurBuild(pair, 0, n);
}