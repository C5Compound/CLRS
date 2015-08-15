struct Edge
{
    char x, y;
    int weight;
    Edge(char a, char b, int c) : x(a), y(b), weight(c) {};
};

/**
*  最小生成树
*  Kruskal算法的实现依赖于并查集
*  Prim算法
*  邻接表表示和邻接矩阵表示
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
    }
    else {
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

/**
 *
 *
 */
void Prim(vector<vector<int>> &graph)
{
    
}