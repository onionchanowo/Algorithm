#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cmath>
#include <cassert>
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
inline int lowbit(int x){ return x & (-x); }
inline int read(){
    int f = 1, x = 0;
    char ch;
    do{
        ch = getchar();
        if(ch == '-')f = -1;
    }while(ch < '0' || ch > '9');
    do{
        x = x * 10 + ch - '0';
        ch = getchar();
    }while(ch >= '0' && ch <= '9');
    return f * x;
}
inline int gcd(int a, int b){ return a % b ? gcd(b, a % b) : b; }
inline int lcm(int a, int b){ return a / gcd(a, b) * b; }
template<typename T>
inline T max(T x, T y, T z){ return max(max(x, y), z); }
template<typename T>
inline T min(T x, T y, T z){ return min(min(x, y), z); }
template<typename A, typename B, typename C>
inline A fpow(A x, B p, C yql){
    A ans = 1;
    for(; p; p >>= 1, x = 1LL * x * x % yql)if(p & 1)ans = 1LL * x * ans % yql;
    return ans;
}
const int N = 100005;
int n, m, p;
int arr[N];
class SegementTree{

private:
    int *data;
    int *tree;
    int *lazyAdd;
    int *lazyMul;

    void pushUp(int treeIndex){

        tree[treeIndex] = tree[treeIndex << 1] + tree[treeIndex << 1 | 1];
    }

    void pushDown(int treeIndex, int l, int r){

        int lc = treeIndex << 1, rc = treeIndex << 1 | 1;
        //cout << lc << " " << rc << endl;

        lazyMul[lc] = (lazyMul[treeIndex] * lazyMul[lc]) % p;
        lazyAdd[lc] = (lazyAdd[lc] * lazyMul[treeIndex] + lazyAdd[treeIndex]) % p;
        lazyMul[rc] = (lazyMul[treeIndex] * lazyMul[rc]) % p;
        lazyAdd[rc] = (lazyAdd[rc] * lazyMul[treeIndex] + lazyAdd[treeIndex]) % p;
        int mid = (r + l) >> 1;
        tree[lc] = (tree[lc] * lazyMul[treeIndex] + lazyAdd[treeIndex] * (mid - l + 1)) % p;
        tree[rc] = (tree[rc] * lazyMul[treeIndex] + lazyAdd[treeIndex] * (r - mid)) % p;
        lazyMul[treeIndex] = 1;
        lazyAdd[treeIndex] = 0;
    }

    void buildTree(int treeIndex, int l, int r){

        if(l == r){
            tree[treeIndex] = data[l];
            return;
        }

        int mid = (r + l) >> 1;
        buildTree(treeIndex << 1, l, mid);
        buildTree(treeIndex << 1 | 1, mid + 1, r);
        pushUp(treeIndex);
        //cout << tree[treeIndex] << endl;
    }

    void upDateOfAdd(int treeIndex, int l, int r, int upDateL, int upDateR, int k){

        if(l == upDateL && r == upDateR){
            lazyAdd[treeIndex] += k;
            lazyAdd[treeIndex] %= p;
            tree[treeIndex] = (tree[treeIndex] + k * (r - l + 1)) % p;
            return;
        }

        pushDown(treeIndex, l, r);

        int mid = (r + l ) >> 1;
        if(upDateL > mid){
            upDateOfAdd(treeIndex << 1 | 1, mid + 1, r, upDateL, upDateR, k);
        }
        else if(upDateR <= mid){
            upDateOfAdd(treeIndex << 1, l, mid, upDateL, upDateR, k);
        }
        else{
            upDateOfAdd(treeIndex << 1, l, mid, upDateL, mid, k);
            upDateOfAdd(treeIndex << 1 | 1, mid + 1, r, mid + 1, upDateR, k);
        }

        pushUp(treeIndex);
    }

    void upDateOfMul(int treeIndex, int l, int r, int upDateL, int upDateR, int k){

        if(l == upDateL && r == upDateR){
            lazyMul[treeIndex] *= k;
            lazyAdd[treeIndex] = (lazyAdd[treeIndex] * k) % p;
            tree[treeIndex] = (tree[treeIndex] * k) % p;
            return;
        }

        pushDown(treeIndex, l, r);

        int mid = (r + l ) >> 1;
        if(upDateL > mid){
            upDateOfMul(treeIndex << 1 | 1, mid + 1, r, upDateL, upDateR, k);
        }
        else if(upDateR <= mid){
            upDateOfMul(treeIndex << 1, l, mid, upDateL, upDateR, k);
        }
        else{
            upDateOfMul(treeIndex << 1, l, mid, upDateL, mid, k);
            upDateOfMul(treeIndex << 1 | 1, mid + 1, r, mid + 1, upDateR, k);
        }

        pushUp(treeIndex);
    }

    int query(int treeIndex, int l, int r, int queryL, int queryR){

        if(l == queryL && r == queryR){
            //printf("tree[%d]: %d\n", treeIndex, tree[treeIndex]);
            return tree[treeIndex];
        }

        pushDown(treeIndex, l, r);

        int mid = (r + l) >> 1;
        if(queryL > mid){
            return query(treeIndex << 1 | 1, mid + 1, r, queryL, queryR);
        }
        else if(queryR <= mid){
            return query(treeIndex << 1, l, mid, queryL, queryR);
        }

        int left = query(treeIndex << 1, l, mid, queryL, mid) % p;
        int right = query(treeIndex << 1 | 1, mid + 1, r, mid + 1, queryR) % p;
        return (left + right) % p;
    }

public:
    SegementTree(int arr[], int n){

        data = new int[n];
        tree = new int[4 * n];
        lazyAdd = new int[4 * n];
        lazyMul = new int[4 * n];
        fill(lazyAdd, lazyAdd + 4 * n, 0);
        fill(lazyMul, lazyMul + 4 * n, 1);

        for(int i = 0; i < n; i ++)
            data[i] = arr[i];

        buildTree(1, 0, n - 1);
        //for(int i = 1; i < 4 * n; i ++) cout << tree[i] << endl;
        //cout << "tree[2]: " << tree[2] << endl;
    }

    ~SegementTree(){
        delete [] data;
        delete [] tree;
        delete [] lazyAdd;
        delete [] lazyMul;
    }

    void upDateOfAdd(int upDateL, int upDateR, int k){
        upDateOfAdd(1, 0, n - 1, upDateL, upDateR, k);
    }

    void upDateOfMul(int upDateL, int upDateR, int k){
        upDateOfMul(1, 0, n - 1, upDateL, upDateR, k);
    }

    int query(int queryL, int queryR){
        return query(1, 0, n - 1, queryL, queryR);
    }
};
int main(){

    int x, y, k, t;
    n = read(), m = read(), p = read();
    for(int i = 0; i < n; i ++){
        arr[i] = read();
    }
    SegementTree sgt = SegementTree(arr, n);
    while(m --){
        t = read(), x = read(), y = read();
        if(t == 1){
            k = read();
            sgt.upDateOfMul(x - 1, y - 1, k);
        }
        else if(t == 2){
            k = read();
            sgt.upDateOfAdd(x - 1, y - 1, k);
        }
        else{
            cout << sgt.query(x - 1, y - 1) << endl;
        }
    }
    return 0;
}