/**
 *  RMQ，全称为Range Minimum Query，顾名思义，则是区间最值查询，它被用来在数组中查找
 *  两个指定索引中最小值的位置。即RMQ相当于给定数组A[0, N-1]，找出给定的两个索引如 i、j 间的最小值的位置。
 */
int A[25] = { 7, 2, 4, 23, 11, 6, 13, 12, 21, 25, 8, 15, 18, 19, 9, 5, 3, 10, 20, 16, 17, 14, 22, 24, 1 };
/**
 *  动态规划的方法，预处理时间为O(N^2)，查询时间为O(1)，空间复杂度为O(N^2)
 *  表中保存的不是最小值的索引而是最小值
 */
void DP4RMQ(int A[], vector<vector<int>> &dp)
{
    for (int i = 0; i < dp.size(); ++i) {
        for (int j = i, minval = A[i]; j < dp.size(); ++j) {
            minval = min(minval, A[j]);
            dp[i][j] = minval;
        }
    }
}

/**
 *  Sparse Table 稀疏表方法，预处理时间为O(NlogN)，查询时间为O(1)，空间复杂度为O(NlogN)
 *  表中保存的是最小值对应的索引，可改为保存最小值
 */
// 表中保存最小值的索引
void SparseTable(int A[], vector<vector<int>> &dp)
{
    for (int i = 0; dp.size() >= 1 << i; ++i) {
        for (int j = 0; j + (1 << i) - 1 < dp.size(); ++j) {
            if (i > 0) {
                dp[j][i] = A[dp[j][i - 1]] < A[dp[j + (1 << i - 1)][i - 1]] ? dp[j][i - 1] : dp[j + (1 << (i - 1))][i - 1];
            }
            else {
                dp[j][i] = j;
            }
        }
    }
}
// 稀疏表查询过程
int querySparseTable(int A[], vector<vector<int>> &dp, int i, int j)
{
    int k = (int)floor(log2(j - i + 1));
    return A[dp[i][k]] < A[dp[j - (1 << k) + 1][k]] ? dp[i][k] : dp[j - (1 << k) + 1][k];
}

// 表中保存最小值
void SparseTable(int A[], vector<vector<int>> &dp)
{
    for (int i = 0; 1 << i <= dp.size(); ++i) {
        for (int j = 0; j + (1 << i) - 1 < dp.size(); ++j) {
            if (i > 0) {
                dp[j][i] = min(dp[j][i - 1], dp[j + (1 << i - 1)][i - 1]);
            } else {
                dp[j][i] = A[j];
            }
        }
    }
}
// 查询
int querySparseTable(int A[], vector<vector<int>> &dp, int i, int j)
{
    int k = (int)floor(log2(j - i + 1));
    return min(dp[i][k], dp[j - (1 << k) + 1][k]);
}