/**
 *  树的最近公共祖先问题的几种实现,节点不包含父节点指针
 *  按照WIKI的定义，每个节点都是自身的祖先
 */
struct node
{
    int key;
    node *left, *right;
    node(int k) : key(k), left(NULL), right(NULL) {};
};

/**
 *  树满足二叉搜索树性质的情况
 *  二叉搜索树包含父节点，但是不使用这个条件
 */
node* queryLCA(node *root, node *n1, node *n2)
{
    if (root == NULL || n1 == NULL || n2 == NULL) {
        return NULL;
    }
    if (n1->key > n2->key) {
        swap(n1, n2);
    }
    while (true) {
        if (root == NULL) {
            return NULL;
        }
        if (root->key < n1->key) {
            root = root->right;
        } else if (root->key > n2->key) {
            root = root->left;
        } else {
            return root;
        }
    }
}

/**
 *  普通的树，递归方式寻找LCA
 */
node* queryLCA(node *root, node *n1, node *n1)
{
    if (root == NULL) {
        return NULL;
    }
    if (root == n1 || root == n2) {
        return root;
    }
    node *left = queryLCA(root->left, n1, n2);
    node *right = queryLCA(root->right, n1, n2);
    if (left != NULL && right != NULL) {
        return root;
    }
    return left != NULL ? left : right;
}

/**
 *  并查集
 */
int parent[MAX_SET], rank[MAX_SET];

void MakeSet(int x)
{
    parent[x] = x;
}

// 路径压缩
int FindSet(int x)
{
    if (parent[x] != x) {
        parent[x] = FindSet(parent[x]);
    }
    return parent[x];
}

// 按秩合并
void UnionSet(int x, int y)
{
    int px = FindSet(x), py = FindSet(y);
    if (px == py) {
        return;
    }
    if (rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[px] = py;
        if (rank[px] == rank[py]) {
            ++rank[py];
        }
    }
}

/**
 *  Tarjan算法离线处理，采用并查集的情况下时间复杂度为O(n)
 *  见算法导论P319
 */
int ancestor[MAX_SET];
bool visited[MAX_SET];

TarjanLCA(u)
{
    MakeSet(u);
    ancestor[FindSet(u)] = u;
    // 对每个儿子递归
    for each child v of u in T:
        TarjanLCA(v)
        UnionSet(u, v)
        ancestor[FindSet(u)] = u
    visited[u] = true
    // 输出所有的LCA
    for each v that [u, v] in P:
        if visited[v] is true
            print "the least common ancestor of" u "and" v "is" ancestor[FindSet(v)]
}
