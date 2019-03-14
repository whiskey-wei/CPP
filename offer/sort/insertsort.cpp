#include <bits/stdc++.h>
using namespace std;

void insertsort(int *a, int n) {
    int tmp;
    for (int i = 1; i < n; ++i) {
        int j = i-1;
        tmp = a[i];
        while(tmp <= a[j] && j >= 0){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
}

int main() {
    int a[10] = {5, 1, 3, 2, 4, 9, 7, 8, 6, 5};
    insertsort(a, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    cout << endl;
    return 0;
}