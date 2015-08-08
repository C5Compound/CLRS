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
    for (int i = size >> 1; i >= 1; ++i) {
        heaplify(a, i, size);
    }
}

// 败者树调整函数



/**
 *  败者树建立函数，败者树为完全二叉树
 *  建立过程与堆建立过程相似
 */
void loserTree(int a[], int k)
{
    for (int i = k; i >= 0; ++i) {
        ajustLosers(a, i, 2 * k);
    }
}


// K路归并
int k_merge()
{

}

// 置换选择排序

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
