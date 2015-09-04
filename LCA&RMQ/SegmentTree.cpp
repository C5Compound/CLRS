/**
*  线段树解RMQ
*  RMQ，全称为Range Minimum Query，顾名思义，则是区间最值查询，它被用来在数组中查找
*  两个指定索引中最小值的位置。即RMQ相当于给定数组A[0, N-1]，找出给定的两个索引如 i、j 间的最小值的位置。
*
*  线段树的方法也是一种离线的处理办法，预处理时间为O(N)，查找时间为O(logN)，即正比于数的高度
*  这里使用的线段树以堆的形式组织，基于数组创建，但由于线段树的性质，有部分节点不会被使用
*  线段树不是完全二叉树而是一棵满二叉树，其非叶子节点有两个儿子
*/

// A数组为需要求区间最值的数组
#define MAX_LEN 1024

int A[25] = { 7, 2, 4, 23, 11, 6, 13, 12, 21, 25, 8, 15, 18, 19, 9, 5, 3, 10, 20, 16, 17, 14, 22, 24, 1 };
// 线段树中保存的是最小值的索引，考虑到索引为0的位置闲置，数组长度至少要为 2 ^ ceil(logN)，即2N
// 线段树不能改为保存最小值，原因在于递归的过程最小值可能为-1
int S[MAX_LEN];

// 初始化线段树，S中索引为0的点不使用
int initialSegmentTree(int A[], int S[], int l, int r, int i = 1)
{
    if (l == r) {
        S[i] = l;
        return l;
    }
    // 初始化左子树
    int minleft = initialSegmentTree(A, S, l, (l + r) / 2, 2 * i);
    int minright = initialSegmentTree(A, S, (l + r) / 2 + 1, r, 2 * i + 1);
    if (A[minleft] < A[minright]) {
        S[i] = minleft;
        return minleft;
    } else {
        S[i] = minright;
        return minright;
    }
}

// 查询线段树
int querySegmentTree(int A[], int S[], int l, int r, int i, int j, int p = 1)
{
    // 请求的范围在给定的范围之外
    if (i > r || j < l) {
        return -1;
    }
    // 请求的范围包含给定的范围
    if (l >= i && r <= j) {
        return S[p];
    }
    int minleft = querySegmentTree(A, S, l, (l + r) / 2, i, j, 2 * p);
    int minright = querySegmentTree(A, S, (l + r) / 2 + 1, r, i, j, 2 * p + 1);
    if (minleft != -1 && minright != -1) {
        return A[minleft] < A[minright] ? minleft : minright;
    }
    return minleft != -1 ? minleft : minright;
}