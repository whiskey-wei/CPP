#include <bits/stdc++.h>
using namespace std;


void swp(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}


int part(int *a, int l, int r) {
    int key = a[r];
    int len = r;
    while(l < r-1){
        /* code */
        while(a[l] <= key && l < r) {
            l++;
        }
        while(a[r] >= key && l < r){
            /* code */
            r--;
        }
        swp(a[l], a[r]);
    }
    swp(a[l], a[len]);
    return l;
}

void quicksort(int *a, int l, int r) {
    if (l >= r) {
        return;
    }
    int x = part(a, l, r);
    quicksort(a, l, x-1);
    quicksort(a, x+1, r);
}

int main() {
    int a[10] = {5, 1, 3, 2, 4, 9, 7, 8, 6, 5};
    quicksort(a, 0, 9);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    cout << endl;
    return 0;
}