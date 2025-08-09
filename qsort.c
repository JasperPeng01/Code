#include <stdio.h>
#include <stdlib.h>

// 比较函数，qsort需要
int compare_float(const void *a, const void *b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    if (fa < fb) return -1;
    else if (fa > fb) return 1;
    else return 0;
}

int main() {
    float *arr = NULL;
    int capacity = 10;  // 初始容量
    int size = 0;       // 实际输入个数
    float temp;

    arr = (float*)malloc(capacity * sizeof(float));
    if (!arr) {
        printf("内存分配失败！\n");
        return 1;
    }

    printf("请输入float类型数字，输入非数字或回车结束输入：\n");

    // 读入数据直到输入非数字或回车结束
    while (scanf("%f", &temp) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            float *new_arr = (float*)realloc(arr, capacity * sizeof(float));
            if (!new_arr) {
                printf("内存重新分配失败！\n");
                free(arr);
                return 1;
            }
            arr = new_arr;
        }
        arr[size++] = temp;
    }

    // 排序
    qsort(arr, size, sizeof(float), compare_float);

    // 输出排序结果
    printf("排序后的结果为：\n");
    for (int i = 0; i < size; i++) {
        printf("%.4f ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
