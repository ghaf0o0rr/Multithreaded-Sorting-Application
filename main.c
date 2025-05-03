#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 1024

int a[MAX], temp[MAX];
int n;

typedef struct { int l, r; } range;

void insertion(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int x = arr[i], j = i - 1;
        while (j >= l && arr[j] > x) { arr[j + 1] = arr[j]; --j; }
        arr[j + 1] = x;
    }
}

void *sort_half(void *arg) {
    range *seg = (range *)arg;
    insertion(a, seg->l, seg->r);
    pthread_exit(NULL);
}

void *merge_halves(void *arg) {
    int mid = n / 2, i = 0, j = mid, k = 0;
    while (i < mid && j < n) temp[k++] = a[i] < a[j] ? a[i++] : a[j++];
    while (i < mid) temp[k++] = a[i++];
    while (j < n)   temp[k++] = a[j++];
    for (int t = 0; t < n; ++t) a[t] = temp[t];
    pthread_exit(NULL);
}

int main(void) {
    if (scanf("%d", &n) != 1) return 1;
    if (n < 2 || n % 2) {
        fprintf(stderr, "error: list size must be an even number ≥ 2\n");
        return 1;
    }
    for (int i = 0; i < n; ++i) if (scanf("%d", &a[i]) != 1) return 1;

    pthread_t tid[3];
    range left  = {0, n / 2 - 1};
    range right = {n / 2, n - 1};

    pthread_create(&tid[0], NULL, sort_half, &left);
    pthread_create(&tid[1], NULL, sort_half, &right);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    pthread_create(&tid[2], NULL, merge_halves, NULL);
    pthread_join(tid[2], NULL);

    for (int i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');
    return 0;
}
