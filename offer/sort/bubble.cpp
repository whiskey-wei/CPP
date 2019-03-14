#include <bits/stdc++.h>
using namespace std;

int bubblesort(int *a, int n) {
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= i; ++j) {
            if (a[j-1] > a[j]) {
                int tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
    }
}

int midsearch(int *a, int n, int key) {
    int l = 0, r = n;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] == key) {
            return mid;
        } 
        else if (a[mid] < key) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return -1;
}

int main() {
    int a[10] = {5, 1, 3, 2, 4, 9, 7, 8, 6, 5};
    bubblesort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("%d\n", midsearch(a, 10, 9));
    return 0;
}