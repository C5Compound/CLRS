/**
 *  希尔排序
 *  最差时间复杂度随步长序列的不同而不同
 *  已知最好的最差时间复杂度为O(n(logn)^2)
 *  最优时间复杂度为O(n)
 */

// 步长为len >> 2^k的希尔排序
void shellsort(int arr[], int len)
{
    for (int step = len >> 1; step > 0; step >>= 1) {
        for (int i = step; i < len; ++i) {
            int j, tmp = arr[i];
            for (j = i - step; j >= 0 && arr[j] > tmp; j -= step) {
                arr[j + step] = arr[j];
            }
            arr[j + step] = tmp;
        }
    }
}