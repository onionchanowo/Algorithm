#include <iostream>
#include <vector>
using namespace std;

int rmqMax(int a, int b){ return max(a, b); }
int rmqMin(int a, int b){ return min(a, b); }

// RMQ
// ST表预处理
// dp[i][j]表示从v[i]开始长度为j的连续序列中maximum / minimum
class RMQ{

private:
    vector<int> v;
    vector<vector<int>> dp;
    int (*cmp)(int, int);

    void st(){

        for(int i = 0; i < v.size(); i ++){
            dp[i][0] = v[i];
        }

        for(int j = 1; (1 << j) <= v.size(); j ++){
            for(int i = 0; i + (1 << j) - 1 < v.size(); i ++){
                dp[i][j] = cmp(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

public:

    RMQ(const vector<int> &v, int (*cmp)(int, int)){
        this->v = v;
        dp = vector<vector<int>>(v.size(), vector<int>(v.size(), 0));
        this->cmp = cmp;

        // ST
        st();
    }

    // 查询区间[l,r]的maximum / minimum
    int query(int l, int r){

        int length = r - l + 1;

        int k = 0;
        while((1 << (k + 1)) <= length) k ++;

        return cmp(dp[l][k], dp[r - (1 << k) + 1][k]);
    }

};

int main(){

    // test for RMQ
    vector<int> v = {1, 2, 5, -2, 10};
    RMQ rmq = RMQ(v, rmqMax);

    int n;
    cin >> n;
    while(n --){
        int l, r;
        cin >> l >> r;
        cout << rmq.query(l, r) << endl;
    }

    return 0;

}