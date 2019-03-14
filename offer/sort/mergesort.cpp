#include <bits/stdc++.h>
using namespace std;

void Merge(int *a, int l, int r, int mid) {
    //printf("[%d,%d],[%d,%d]\n",l ,mid, mid+1, r);
    int p1 = l, p2 = mid+1;
    int tmp[10];
    int cnt = 0;
    //printf("l:%d r:%d mid:%d\n",l, r, mid);
    while((p1 <= mid) && (p2 <= r)){
        /* code */
        if (a[p1] < a[p2]) {
            //printf("p1:%d\n",a[p1]);
            tmp[cnt++] = a[p1];
            p1++;
        } else {
            //printf("p2:%d\n",a[p2]);
            tmp[cnt++] = a[p2];
            p2++;
        }      
    }
    //printf("%d %d\n",tmp[0], tmp[1]);
    //printf("p1:%d p2:%d\n", p1, p2);
    while(p1 <= mid){
            /* code */
        tmp[cnt++] = a[p1];
        p1++;
    }
    while(p2 <= r) {
        tmp[cnt++] = a[p2];
        p2++;
    }
    for (int i = 0, j = l; i < cnt; i++, j++) {
        a[j] = tmp[i];
        //printf("%d ",a[j]);
    }
    //printf("\n");
}

void mergesort(int *a, int l, int r) {
    if (l >= r) {
        return ;
    }
    int mid = (l+r) >> 1;
    mergesort(a, l, mid);
    mergesort(a, mid+1, r);
    Merge(a, l, r, mid);
}

int main() {
    int a[10] = {5, 1, 3, 2, 4, 9, 7, 8, 6, 5};
    mergesort(a, 0, 9);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    cout << endl;
    return 0;
}