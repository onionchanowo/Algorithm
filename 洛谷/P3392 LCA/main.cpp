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
const int N = 500005;
int n, m, s, cnt, k, first[N], parent[N], head[N];
bool vis[N];
struct Edge{
    int v, next;
}edge[2 * N];
struct Query{
    int v, lca, next;
}query[2 * N];
void addEdge(int a, int b){
    edge[cnt].v = b;
    edge[cnt].next = first[a];
    first[a] = cnt ++;
}
void addQuery(int a, int b){
    query[k].v = b;
    query[k].next = head[a];
    head[a] = k ++;
}
void init(){
    cnt = 0;
    k = 1;
    fill(first, first + N, -1);
    fill(vis, vis + N, false);
    fill(head, head + N, -1);
}
int find(int p){
    while(p != parent[p]){
        parent[p] = parent[parent[p]];
        p = parent[p];
    }
    return p;
}
void unionElements(int p, int q){
    int pRoot = find(p);
    int qRoot = find(q);
    if(pRoot == qRoot) return;
    parent[pRoot] = qRoot;  // q 是 p 的父亲
}
void tarjan(int s){

    vis[s] = true;
    for(int i = first[s]; i != -1; i = edge[i].next){
        int u = edge[i].v;
        if(!vis[u]){
            tarjan(u);
            unionElements(u, s);
        }
    }
    for(int i = head[s]; i != -1; i = query[i].next){
        int u = query[i].v;
        if(vis[u]){
            query[i].lca = find(u);
            if(i & 1) query[i + 1].lca = query[i].lca;
            else query[i - 1].lca = query[i].lca;
        }
    }
}
int main(){

    init();
    n = read(), m = read(), s = read();
    for(int i = 0; i <= n; i ++){
        parent[i] = i;
    }
    for(int i = 0; i < n - 1; i ++){
        int x, y;
        x = read(), y = read();
        addEdge(x, y);
        addEdge(y, x);
    }
    for(int i = 0; i < m; i ++){
        int x, y;
        x = read(), y = read();
        addQuery(x, y);
        addQuery(y, x);
    }
    tarjan(s);
    for(int i = 1; i <= m; i ++){
        cout << query[i * 2].lca << endl;
    }
    return 0;
}