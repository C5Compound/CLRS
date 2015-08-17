/**
 *  带权有向图的单源最短路径的几种算法实现
 */

struct node
{
    int v, w;
    node(int iv, int iw) : v(iv), w(iw) {};
};

// Bellman-Ford算法
bool BellmanFord(vector<char> &vertexs, vector<vector<node>> &adjs, int s)
{
    // 初始化
    vector<int> dis(adjs.size(), INT_MAX), pa(adjs.size(), s);
    dis[s] = 0;
    // 执行 |V| - 1 循环
    for (int i = 1; i < adjs.size(); ++i) {
        for (int j = 0; j < adjs.size(); ++j) {
            for (auto k : adjs[j]) {
                // 松弛过程
                if (dis[j] < INT_MAX && dis[k.v] > dis[j] + k.w) {
                    dis[k.v] = dis[j] + k.w;
                    pa[k.v] = j;
                }
            }
        }
    } 
    // 检测负权回路
    for (int j = 0; j < adjs.size(); ++j) {
        for (auto k : adjs[j]) {
            if (dis[k.v] > dis[j] + k.w) {
                return false;
            }
        }
    }
    // 格式化输出结果
    for (int i = 0; i < adjs.size(); ++i) {
        printf("dis of %c is: %d\n", vertexs[i], dis[i]);
        for (int j = i; j != s; j = pa[j]) {
            printf("%c<--", vertexs[j]);
        }
        printf("%c\n", vertexs[s]);
    }
    return true;
}

void testBellmanFord()
{
    char v[5] = { 's', 't', 'x', 'y', 'z' };
    vector<char> vertexs(v, v + 5);
    vector<vector<node>> adjs;
    vector<node> tmp;
    tmp.push_back(node(1, 6));
    tmp.push_back(node(3, 7));
    adjs.push_back(tmp);
    tmp.clear();
    tmp.push_back(node(2, 5));
    tmp.push_back(node(3, 8));
    tmp.push_back(node(4, -4));
    adjs.push_back(tmp);
    tmp.clear();
    tmp.push_back(node(1, -2));
    adjs.push_back(tmp);
    tmp.clear();
    tmp.push_back(node(2, -3));
    tmp.push_back(node(4, 9));
    adjs.push_back(tmp);
    tmp.clear();
    tmp.push_back(node(0, 2));
    tmp.push_back(node(2, 7));
    adjs.push_back(tmp);
    BellmanFord(vertexs, adjs, 0);
}

// 有向无回路图的单源最短路径算法
void DFS(vector<vector<node>> &adjs, vector<bool> &visited, vector<int> &topology, int u)
{
    if (visited[u]) {
        return;
    }
    for (auto i : adjs[u]) {
        DFS(adjs, visited, topology, i);
    }
    visited[u] = true;
    topology.push_back(u);
}
// 拓扑排序
void TopologySort(vector<vector<node>> &adjs, vector<int> &topology)
{
    vector<bool> visited(adjs.size(), false);
    for (int i = 0; i < adjs.size(); ++i) {
        if (!visited[i]) {
            DFS(adjs, visited, topology, i);
        }
    }
}

void DagShortestPaths(vector<char> &vertexs, vector<vector<node>> &adjs)
{
    vector<int> dis(adjs.size(), INT_MAX), pa(adjs.size(), 0), topology;
    DFS(adjs, topology);
    dis[0] = 0;
    for (int i = topology.size() - 1; i >= 0; --i) {
        for (auto j : adjs[i]) {
            // 松弛过程，带无穷判断
            if (dis[i] < INT_MAX && dis[j.v] > dis[i] + j.w) {
                dis[j.v] = dis[i] + j.w;
                pa[j.v] = i;
            }
        }
    }
    // 格式化输出结果
    
}

// Dijkstra算法