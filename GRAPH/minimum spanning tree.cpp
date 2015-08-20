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
 *  用vector实现的版本,可直接修改为数组实现
 *  输入为邻接矩阵，不相连的节点权值为INT_MAX
 *  复杂度为O(V^2)
 */
void Prim(vector<char> &vertexs, vector<vector<int>> &graph)
{
    // lowcost和closest数组中分别保存点i到MST的最小距离及对应的MST中的点
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
/*  另一个版本的测试  
    vector<vector<node>> adjs;
    for (int i = 0; i < 9; ++i) {
        vector<node> tmp;
        for (int j = 0; j < 9; ++j) {
            if (table[i][j] != INT_MAX) {
                tmp.push_back(node(j, table[i][j]));
            }
        }
        adjs.push_back(tmp);
    }
    Prim(vertexs, adjs);*/
}

/**
 *  基于数组的二叉堆实现
 */

struct BinaryHeap
{
    int size;
    vector<pair<int, int>> ls;
    BinaryHeap() : size(0) {ls.push_back(make_pair(0, 0));};
    void minHeapify(int i);
    void heapInsert(pair<int, int> node);
    void decreaseKey(int i, int key);
    pair<int, int> extractMin()
};

void BinaryHeap::minHeapify(int i)
{
    int l = i << 1, r = i << 1 + 1, m;
    m = l <= size && ls[l].second < ls[i].second ? l : i;
    m = r <= size && ls[r].second < ls[m].second ? r : m;
    if (m != i) {
        swap(ls[i], ls[m]);
        minHeapify(m);
    }
}

void BinaryHeap::heapInsert(pair<int, int> node)
{
    ++size;
    ls.push_back(node);
    decreaseKey(size, node.second);
}

void BinaryHeap::decreaseKey(int i, int key)
{
    ls[i].second = key;
    while (i > 1 && ls[i].second < ls[i / 1].second) {
        swap(ls[i], ls[i / 2]);
        i /= 2;
    }
}

pair<int, int> BinaryHeap::extractMin()
{
    pair<int, int> ret = ls[1];
    ls[1] = ls[size--];
    minHeapify(1);
    return ret;
}

/**
 *  基于priority queue的版本
 *  与基于vector的版本不同的地方在于：寻找距离MST最小距离的点用优先队列实现
 *  输入为邻接表，所以更新点到MST的距离时只更新对应表中的点
 */
struct node
{
    int u, w;
    node(int iu, int iw) : u(iu), w(iw) {};
    bool operator < (const node &other) const {return other.w  < w;};
};

// 如果要求输出所有的边，则需要像上面的版本一样，加入一个closest数组
void Prim(vector<char> &vertexs, vector<vector<node>> &adjs)
{
    vector<int> lowcost(adjs.size(), INT_MAX);
    vector<bool> A(adjs.size(), true);
    priority_queue<node> Q;
    // 初始化
    Q.push(node(0, 0));
    while (!Q.empty()) {
        node it = Q.top();
        Q.pop();
        if (!A[it.u]) {
            continue;
        }
        A[it.u] = false;
        printf("%c->", vertexs[it.u]);
        for (auto i : adjs[it.u]) {
            if (A[i.u] && i.w < lowcost[i.u]) {
                lowcost[i.u] = i.w; 
                Q.push(node(i.u, i.w));
            }
        }
    }
}