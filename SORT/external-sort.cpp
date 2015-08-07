/**
 *  外部排序实现
 *  1.多路归并败者树
 *  2.置换选择排序
 */

 // 堆调整函数
void heaplify()
{

}

// 堆建立函数
void heapbuild()
{

}

// K路归并
int k_merge()
{

}

// 置换选择排序

// 快排划分 升序
int partition(int a[], int l, int r)
{
    int i = l, j = l;
    static auto swap = [&](int p, int q){int k = p; p = q; q = k;};
    for (; j <= r; ++j) {
        if (a[j] < a[i]) {
            swap(a[i], a[j]);
            ++i;
        }
    }
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
