/**
 *  希尔排序
 */

// 步长为len >> 2^k的希尔排序
void shellsort(int arr[], int len)
{
    for (int step = len >> 1; step > 1; step >>= 1) {
        for (int i = step;  i < len; ++i) {
            int tmp = arr[i];
            for (int j = i - step; j >= 0 && arr[j] > tmp; j -= step) {
                arr[j + step] = arr[j];
            }
            arr[j + step] = tmp;
        }
    }
}