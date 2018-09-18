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
int n, m;
int cnt, first[N], disTo[N];
bool inq[N];
struct Edge{
    int v, next, w;
}edge[N * 10];
void addEdge(int a, int b, int c){
    edge[cnt].v = b;
    edge[cnt].w = c;
    edge[cnt].next = first[a];
    first[a] = cnt ++;
}
bool spfa(int s){

    inq[s] = true;
    for(int i = first[s]; i != -1; i = edge[i].next){
        int u = edge[i].v;
        if(disTo[u] < disTo[s] + edge[i].w){
            disTo[u] = disTo[s] + edge[i].w;
            if(inq[u]) return false;
            if(!spfa(u)) return false;
        }
    }
    inq[s] = false;
    return true;
}
void init(){
    cnt = 0;
    fill(first, first + N, -1);
    fill(inq, inq + N, false);
    fill(disTo, disTo + N, -inf);
}
int main(){

    init();
    int a, b, c, t;
    n = read(); m = read();
    for(int i = 0; i < m; i ++){
        t = read();
        if(t == 1){
            a = read();
            b = read();
            c = read();
            addEdge(a, b, c);
        }
        else if(t == 2){
            a = read();
            b = read();
            c = read();
            addEdge(b, a, -c);
        }
        else if(t == 3){
            a = read();
            b = read();
            addEdge(a, b, 0);
            addEdge(b, a, 0);
        }
    }
    for(int i = 1; i <= n; i ++){
        addEdge(n + 1, i, 0);
    }
    disTo[n + 1] = 0;
    if(spfa(n + 1)) cout << "Yes" << endl;
    else cout << "No" << endl;
    //for(int i = 1; i <= n; i ++)
        //cout << disTo[i] << endl;
    return 0;
}