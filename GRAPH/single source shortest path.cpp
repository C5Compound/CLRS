/**
 *  带权有向图的单源最短路径的几种算法实现
 */

struct node
{
    int v, w;
    node(int iv, int iw) : v(iv), w(iw) {};
    bool operator < (const node &other) {
        return other.w < w;
    }
};

// 格式化输出结果
void formate(vector<char> &vertexs, vector<int> &dis, vector<int> pa, int s)
{
    for (int i = 0; i < vertexs.size(); ++i) {
        printf("dis of %c is: %d\n", vertexs[i], dis[i]);
        for (int j = i; j != s; j = pa[j]) {
            printf("%c<--", vertexs[j]);
        }
        printf("%c\n", vertexs[s]);
    }
}

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
    formate(vertexs, dis, pa, s);
    return true;
}

// void testBellmanFord()
// {
//     char v[5] = { 's', 't', 'x', 'y', 'z' };
//     vector<char> vertexs(v, v + 5);
//     vector<vector<node>> adjs;
//     vector<node> tmp;
//     tmp.push_back(node(1, 6));
//     tmp.push_back(node(3, 7));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(2, 5));
//     tmp.push_back(node(3, 8));
//     tmp.push_back(node(4, -4));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(1, -2));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(2, -3));
//     tmp.push_back(node(4, 9));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(0, 2));
//     tmp.push_back(node(2, 7));
//     adjs.push_back(tmp);
//     BellmanFord(vertexs, adjs, 0);
// }

// 有向无回路图的单源最短路径算法
void DFS(vector<vector<node>> &adjs, vector<bool> &visited, vector<int> &topology, int u)
{
    if (visited[u]) {
        return;
    }
    for (auto i : adjs[u]) {
        DFS(adjs, visited, topology, i.v);
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
// 求最短路径
void DagShortestPaths(vector<char> &vertexs, vector<vector<node>> &adjs, int s)
{
    vector<int> dis(adjs.size(), INT_MAX), pa(adjs.size(), s), topology;
    TopologySort(adjs, topology);
    dis[0] = 0;
    for (int i = topology.size() - 1; i >= 0; --i) {
        for (auto j : adjs[topology[i]]) {
            // 松弛过程，带无穷判断
            if (dis[topology[i]] < INT_MAX && dis[j.v] > dis[topology[i]] + j.w) {
                dis[j.v] = dis[topology[i]] + j.w;
                pa[j.v] = topology[i];
            }
        }
    }
    formate(vertexs, dis, pa, s);
}

// void testDagShortestPaths()
// {
//     char v[6] = {'s', 'r', 't', 'x', 'y', 'z'};
//     vector<char> vertexs(v, v + 6);
//     vector<vector<node>> adjs;
//     vector<node> tmp;
//     tmp.push_back(node(2, 2));
//     tmp.push_back(node(3, 6));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(0, 5));
//     tmp.push_back(node(2, 3));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(3, 7));
//     tmp.push_back(node(4, 4));
//     tmp.push_back(node(5, 2));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(4, -1));
//     tmp.push_back(node(5, 1));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(5, -2));
//     adjs.push_back(tmp);
//     tmp.clear();
//     adjs.push_back(tmp);
//     DagShortestPaths(vertexs, adjs, 0);
// }

// Dijkstra算法，基于最小优先级队列
void dijkstra(vector<char> &vertexs, vector<vector<node>> &adjs, int s)
{
    vector<int> dis(adjs.size(), INT_MAX), pa(adjs.size(), s);
    vector<bool> visited(adjs.size(), false);
    priority_queue<node> Q;
    // 初始化
    Q.push(node(s, 0));
    dis[s] = 0;
    while (!Q.empty()) {
        node it = Q.top();
        Q.pop();
        if (visited[it.v]) {
            continue;
        }
        visited[it.v] = true;
        for (auto i : adjs[it.v]) {
            if (!visited[i.v] && dis[i.v] > dis[it.v] + i.w) {
                dis[i.v] = dis[it.v] + i.w;
                pa[i.v] = it.v;
                Q.push(node(i.v, dis[i.v]));
            }
        } 
    }
    formate(vertexs, dis, pa, s);
}

// void testDijkstra()
// {
//     char v[5] = { 's', 't', 'x', 'y', 'z' };
//     vector<char> vertexs(v, v + 5);
//     vector<vector<node>> adjs;
//     vector<node> tmp;
//     tmp.push_back(node(1, 10));
//     tmp.push_back(node(3, 5));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(2, 1));
//     tmp.push_back(node(3, 2));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(4, 4));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(1, 3));
//     tmp.push_back(node(2, 9));
//     tmp.push_back(node(4, 2));
//     adjs.push_back(tmp);
//     tmp.clear();
//     tmp.push_back(node(0, 7));
//     tmp.push_back(node(2, 6));
//     adjs.push_back(tmp);
//     dijkstra(vertexs, adjs, 0);
// }