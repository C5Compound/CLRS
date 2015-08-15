/**
 *  最小生成树
 *  Kruskal算法的实现依赖于并查集
 *  Prim算法依赖于最小优先级队列
 *  邻接表表示和邻接矩阵表示
 */

struct Edge
{
    char x, y;
    int weight;
    Edge(char a, char b, int c) : x(a), y(b), weight(c) {};
};

/**
 *  基于数组的并查集实现
 */
#define SET_MAX 2048
int parent[SET_MAX];
int Rank[SET_MAX];

void make_set(int x)
{
    parent[x] = x;
    Rank[x] = 0;
}

// 路径压缩
int find_set(int x)
{
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

// 按秩合并
void union_set(int x, int y)
{
    int fx = find_set(x), fy = find_set(y);
    if (Rank[fx] > Rank[fy]) {
        parent[fy] = fx;
    } else {
        parent[fx] = fy;
    }
    if (Rank[fx] == Rank[fy]) {
        Rank[fy] += 1;
    }
}

/**
 * G(V,E), V为节点，char型,
 * 图以(u v weight)vector的形式输入
 */
void Kruskal(vector<char> &vertexs, vector<Edge> &v2emap)
{
    for (int i = 0; i < vertexs.size(); ++i) {
        make_set(vertexs[i]);
    }
    // 升序排列
    sort(v2emap.begin(), v2emap.end(), [](Edge x, Edge y){return x.weight < y.weight; });
    for (auto i : v2emap) {
        if (find_set(i.x) != find_set(i.y)) {
            printf("edge from %c to %c with weight %d\n", i.x, i.y, i.weight);
            union_set(i.x, i.y);
        }
    }
}

void testKruskal()
{
    char v[9] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    vector<char> vertexs(v, v + 9);
    vector<Edge> v2emap;
    auto addEdge = [&v2emap](char x, char y, int weight){v2emap.push_back(Edge(x, y, weight));};
    addEdge('a', 'b', 4);
    addEdge('a', 'h', 8);
    addEdge('b', 'c', 8);
    addEdge('b', 'h', 11);
    addEdge('c', 'd', 7);
    addEdge('c', 'f', 4);
    addEdge('c', 'i', 2);
    addEdge('d', 'e', 9);
    addEdge('d', 'f', 14);
    addEdge('e', 'f', 10);
    addEdge('f', 'g', 2);
    addEdge('g', 'h', 1);
    addEdge('g', 'i', 6);
    addEdge('h', 'i', 7);
    Kruskal(vertexs, v2emap);
}

/**
 *  用数组实现的版本
 *  输入为邻接矩阵，不相连的节点权值为INT_MAX
 */
void Prim(vector<char> &vertexs, vector<vector<int>> &graph)
{
    // lowcost和closest数组中分别保存到点i距离最近的点及其距离
    vector<int> lowcost(graph.size()), closest(graph.size());
    // 如果点已经出现在MST中，则置为false
    vector<bool> A(graph.size(), true);
    // 初始化
    for (int i = 1; i < graph.size(); ++i) {
        lowcost[i] = graph[0][i];
        closest[i] = 0;
    }
    A[0] = false;
    for (int i = 1; i < graph.size(); ++i) {
        int mincost = INT_MAX, k;
        // 找出与已有的最小生成树距离最小的点
        for (int j = 1; j < graph.size(); ++j) {
            if (A[j] && lowcost[j] < mincost) {
                mincost = lowcost[j];
                k = j;
            }
        }
        // 将该点加入最小生成树
        A[k] = false;
        printf("%c→%c\n", vertexs[closest[k]], vertexs[k]);
        // 更新各点与最小生成树的距离
        for (int j = 1; j < graph.size(); ++j) {
            if (A[j] && graph[k][j] < lowcost[j]) {
                lowcost[j] = graph[k][j];
                closest[j] = k;
            }
        }
    }
}

void testPrim()
{
    char v[9] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
    vector<char> vertexs(v, v + 9);
    int table[9][9] = {{0, 4, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX},
                       {4, 0, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 11, INT_MAX},
                       {INT_MAX, 8, 0, 7, INT_MAX, 4, INT_MAX, INT_MAX, 2},
                       {INT_MAX, INT_MAX, 7, 0, 9, 14, INT_MAX, INT_MAX, INT_MAX},
                       {INT_MAX, INT_MAX, INT_MAX, 9, 0, 10, INT_MAX, INT_MAX, INT_MAX},
                       {INT_MAX, INT_MAX, 4, 14, 10, 0, 2, INT_MAX, INT_MAX},
                       {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 2, 0, 1, 6},
                       {8, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 1, 0, 7},
                       {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, 6, 7, 0}};
    vector<vector<int>> graph;
    for (int i = 0; i < 9; ++i) {
        graph.push_back(vector<int>(&table[i][0], &table[i + 1][0]));
    }
    Prim(vertexs, graph);
}

/**
 *  基于优先队列实现的版本
 *  输入为邻接矩阵，不相连的节点权值为INT_MAX
 */
