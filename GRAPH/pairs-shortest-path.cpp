/**
 *  每对顶点的最短路径
 *  带全有向图，输入为邻接表
 */

/**
 *  Floyd-Warshall算法，时间复杂度为O(V^3)
 *  实质是一种动态规划
 */
void FloydWarshall(vector<vector<int>> dis)
{
    vector<vector<int>> exdis;
    for (int k = 0; k < adjs.size(); ++k) {
        exdis = dis;
        for (int i = 0; i < adjs.size(); ++i) {
            for (int j = 0; j < adjs.size(); ++j) {
                dis[i][j] = min(exdis[i][k] + exdis[k][j], exdis[i][j]);
            }
        }
    }
    for (int i = 0; i < adjs.size(); ++i) {
        for (int j = 0; j < adjs.size(); ++j) {
            printf("%4d", dis[i][j]);
        }
    }
}

/**
 *  稀疏图上的Johnson算法
 *  bellman-ford算法结合dijkstra算法
 */
void Johnson(vector<vector<node>> &adjs)
{
    
}
