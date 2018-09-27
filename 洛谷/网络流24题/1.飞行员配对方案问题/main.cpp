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

// 网络流24题 - 1
const int N = 500;
int m, n, cnt, t, head[N], depth[N];
struct Edge{
    int v, f, next;
}edge[10 * N];
void addEdge(int a, int b){
    edge[cnt].v = b;
    edge[cnt].f = 1;
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
    q.push(0);
    depth[0] = 1;

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
    return depth[t] != 0;
}
int dfs(int s, int flow){

    if(s == t) return flow;
    for(int i = head[s]; i != -1; i = edge[i].next){
        int u = edge[i].v;
        if(depth[u] == depth[s] + 1 && edge[i].f > 0){
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
        while(int d = dfs(0, inf)) ret += d;
    }
    return ret;
}
int main(){

    ios::sync_with_stdio(false);
    init();
    cin >> m >> n;
    int x, y;
    while(cin >> x >> y && x != -1 && y != -1){
        addEdge(x, y);
    }
    t = n + 1;
    for(int i = 1; i <= m; i ++) addEdge(0, i);
    for(int i = m + 1; i <= n; i ++) addEdge(i, t);
    cout << dinic() << endl;
    for(int i = 1; i <= m; i ++){
        for(int k = head[i]; k != -1; k = edge[k].next){
            if(edge[k].f == 0 && edge[k].v != 0 && edge[k].v != t) {
                cout << i << " " << edge[k].v << endl;
                break;
            }
        }
    }
    return 0;
}