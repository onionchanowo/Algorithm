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
int cnt, head[N], anc[N][20], deepth[N];
bool vis[N];
struct Edge{
    int v, next;
}edge[2 * N];
void addEdge(int a, int b){
    edge[cnt].v = b;
    edge[cnt].next = head[a];
    head[a] = cnt ++;
}
void init(){
    cnt = 0;
    fill(head, head + N, -1);
    fill(anc[0], anc[0] + N * 20, -1);
    fill(vis, vis + N, false);
    fill(deepth, deepth + N, 1);
}
void dfs(int cur, int parent){

    vis[cur] = true;
    deepth[cur] = deepth[parent] + 1;
    anc[cur][0] = parent;

    // 往前跳一半，也就是 2^(n - 1) 个节点
    for(int i = 1; (1 << i) <= deepth[cur]; i ++){
        anc[cur][i] = anc[anc[cur][i - 1]][i - 1];
    }

    for(int i = head[cur]; i != -1; i = edge[i].next){
        int u = edge[i].v;
        if(!vis[u]) dfs(u, cur);
    }
}
int onlineLCA(int x, int y){

    if(deepth[x] < deepth[y]) swap(x, y);
    for(int i = 19; i >= 0; i --){
        if(deepth[y] <= deepth[x] - (1 << i))
            x = anc[x][i];
    }
    if(x == y) return x;

    // LCA
    for(int i = 19; i >= 0; i --){
        if(anc[x][i] != anc[y][i]){
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}
int main(){

    init();
    int n, m, s;
    n = read(), m = read(), s = read();
    for(int i = 0; i < n - 1; i ++){
        int x, y;
        x = read(), y = read();
        addEdge(x, y);
        addEdge(y, x);
    }
    dfs(s, 0);
    for(int i = 0; i < m; i ++){
        int x, y;
        x = read(), y = read();
        printf("%d\n", onlineLCA(x, y));
    }
    return 0;
}