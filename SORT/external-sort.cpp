/**
 *  外部排序实现
 *  1.多路归并败者树
 *  2.置换选择排序
 */

void swap(int &p, int &q) 
{
    int k = p;
    p = q;
    q = k;
}

 // 最小堆调整函数
void heaplify(int a[], int i, int size)
{
    int l = 2 * i; r = 2 * i + 1, m;
    m = (l <= size && a[l] < a[i]) ? l : i;
    m = (r <= size && a[r] < a[m]) ? r : m;
    if (m != i) {
        swap(a[m], a[i]);
        heaplify(a, m, size);
    }
}

// 堆建立函数
void heapbuild(int a[], int size)
{
    for (int i = size / 2; i >= 1; ++i) {
        heaplify(a, i, size);
    }
}

/**
*  败者树调整函数
*  数值较小者胜
*/
void ajustLosers(int leave[], int exnode[], int k, int i)
{
    int p = (i + k) >> 1;
    while (p > 0) {
        if (exnode[p] == -1) {
            exnode[p] = i;
            return;
        }
        if (leave[i] > leave[exnode[p]]) {
            swap(i, exnode[p]);
        }
        p /= 2;
    }
    exnode[0] = i;
}

/**
*  败者树建立函数，败者树为完全二叉树
*  其叶子节点保存值,内节点保存败者对应的叶节点索引
*  建立过程与堆建立过程相似
*/
void loserTree(int leave[], int exnode[], int k)
{
    fill_n(exnode, k, -1);
    for (int i = 0; i < k; ++i) {
        ajustLosers(leave, exnode, k, i);
    }
}

// K路归并
void k_merge(FILE *fp[], FILE *wfp, int k)
{
    int *tree = new int[2 * k];
    int *exnode = tree, *leave = tree + k;
    for (int i = 0; i < k; ++i) {
        fscanf(fp[i], "%d", leave + i);
    }
    loserTree(leave, exnode, k);
    while (leave[exnode[0]] != INT_MAX) {
        int i = exnode[0];
        fprintf(wfp, "%4d", leave[i]);
        // 读入数据，如果结束则设为INT_MAX
        if (feof(fp[i]) || fscanf(fp[i], "%d", leave + i) != 1) {
            leave[i] = INT_MAX;
        }
        ajustLosers(leave, exnode, k, i);
    }
    delete[] tree;
}

// 快排划分 升序
int partition(int a[], int l, int r)
{
    int i = l, j = l + 1;
    for (; j <= r; ++j) {
        if (a[j] < a[l]) {
            swap(a[++i], a[j]);
        }
    }
    swap(a[i], a[l]);
    return i;
}

// 快速排序
void quicksort(int a[], int l, int r)
{
    if (l >= r) {
        return;
    }
    int m = partition(a, l, r);
    quicksort(a, l, m - 1);
    quicksort(a, m + 1, r);
}
