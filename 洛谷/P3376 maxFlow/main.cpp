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
const int N = 10005;
const int MAXN = 100005;
int n, m, s, t, cnt, head[N], depth[N];
struct Edge{
    int v, f, next;
}edge[2 * MAXN];
void addEdge(int a, int b, int w){
    edge[cnt].v = b;
    edge[cnt].f = w;
    edge[cnt].next = head[a];
    head[a] = cnt ++;
    edge[cnt].v = a;
    edge[cnt].f = 0;
    edge[cnt].next = head[b];
    head[b] = cnt ++;
}
void init(){
    cnt = 0;
    fill(head, head + N, -1);
}
bool bfs(){

    fill(depth, depth + N, 0);
    queue<int> q;
    q.push(s);
    depth[s] = 1;

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int i = head[cur]; i != -1; i = edge[i].next){
            int u = edge[i].v;
            if((!depth[u]) && edge[i].f > 0){
                depth[u] = depth[cur] + 1;
                q.push(u);
            }
        }
    }
    //cout << depth[t] << endl;
    return depth[t] != 0;
}
int dfs(int cur, int flow){

    if(cur == t) return flow;

    for(int i = head[cur]; i != -1; i = edge[i].next){
        int u = edge[i].v;
        if(depth[u] == depth[cur] + 1 && edge[i].f > 0){
            int sub = dfs(u, min(flow, edge[i].f));
            if(sub > 0){
                edge[i].f -= sub;
                edge[i^1].f += sub;
                return sub;
            }
        }
    }
    return 0;
}
int dinic(){

    int ret = 0;
    while(bfs()){
        while(int d = dfs(s, inf)) ret += d;
    }
    return ret;
}
int main(){

    init();
    n = read(), m = read(), s = read(), t = read();
    for(int i = 0; i < m; i ++){
        int x, y, k;
        x = read(), y = read(), k = read();
        addEdge(x, y, k);
    }
    cout << dinic() << endl;
}