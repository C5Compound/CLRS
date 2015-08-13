/**
 *  最小生成树
 *  Kruskal算法的实现依赖于并查集
 *  Prim算法
 *  邻接表表示和邻接矩阵表示
 */
#define SET_MAX 2048
int parent[SET_MAX];
int rank[SET_MAX];

void make_set(int x)
{
    parent[x] = x;
    rank[x] = 0;
}

int find_set(int x)
{
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y)
{
    parent[find_set(x)] = find_set(y);
}

void Kruskal(vector<vector<int>> &graph)
{
    
}


void Prim(vector<vector<int>> &graph)
{

}