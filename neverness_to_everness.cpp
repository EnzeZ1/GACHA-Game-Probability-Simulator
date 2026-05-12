#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const double pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = (ll)1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e7 + 10, M = 2 * N;

// 大棋盘: 54
// 奖励棋盘：9 * 2

const int s = 54;
ld dp[91][s + 2 * 9][2][2];

struct gacha{
    vector<int> grid = {
        0, 1, 0, 2, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 2, 1, 1, 0, 1,
        1, 2, 0, 1, 0, 1, 0, 2, 1, 0, 0, 1, 1, 2, 0, 1, 0, 0, 1, 2, 
        0, 1, 0, 1, 1, 2, 1, 1, 0, 0, 1, 2, 1, 1
    };

    vector<vector<int>> mp[2] = {
        {{3, 0, 2, 1, 2, 1, 2, 1, 2},
         {2, 0, 0, 2, 2, 2, 2, 2, 2}},
        {{3, 0, 3, 1, 3, 1, 3, 1, 3},
         {3, 0, 0, 2, 3, 2, 3, 2, 3}}
    };
};

ld prob[4] = {0, 0.002, 0.03, 1};

void solve(){
    int pos;
    cin >> pos;
    gacha g;
    
    dp[0][pos][0][0] = 1;

    for(int i = 1; i <= 90; i++){
        for(int j = 0; j < s + 2 * 9; j++){
            for(int k = 1; k <= 6; k++){
                int nxt = j + k;

                if(j == 1){ // out -> special 1
                    nxt = s + k - 1;
                    int r = g.mp[i >= 70][0][k - 1];
                    ld q = (i == 90 ? 1.0 : prob[r]);

                    dp[i][nxt][1][1] += dp[i - 1][j][0][0] * q / 6;
                    dp[i][nxt][1][0] += dp[i - 1][j][0][0] * (1 - q) / 6;
                }
                else if(j == 28){ // out -> special 2
                    nxt = s + 9 + k - 1;
                    int r = g.mp[i >= 70][1][k - 1];
                    ld q = (i == 90 ? 1.0 : prob[r]);

                    dp[i][nxt][1][1] += dp[i - 1][j][0][0] * q / 6;
                    dp[i][nxt][1][0] += dp[i - 1][j][0][0] * (1 - q) / 6;
                }
                else{
                    if(j >= s){
                        if(j < 63){
                            if(nxt >= 63){ // special 1 -> out
                                int to = (3 + nxt - 63) % s, r = g.grid[to];
                                if(i >= 70 && (to + 3) % 6 == 0){
                                    r = 3;
                                }

                                ld q = (i == 90 ? 1.0 : prob[r]);

                                dp[i][to][0][1] += dp[i - 1][j][1][0] * q / 6;
                                dp[i][to][0][0] += dp[i - 1][j][1][0] * (1 - q) / 6;
                            }   
                            else{ // special 1 -> special 1
                                int r = g.mp[i >= 70][0][nxt - s];
                                ld q = (i == 90 ? 1.0 : prob[r]);

                                dp[i][nxt][1][1] += dp[i - 1][j][1][0] * q / 6;
                                dp[i][nxt][1][0] += dp[i - 1][j][1][0] * (1 - q) / 6;
                            }
                        }
                        else{
                            if(nxt >= 72){ // special 2 -> out
                                int to = (28 + nxt - 72) % s, r = g.grid[to];
                                if(i >= 70 && (to + 3) % 6 == 0){
                                    r = 3;
                                }

                                ld q = (i == 90 ? 1.0 : prob[r]);

                                dp[i][to][0][1] += dp[i - 1][j][1][0] * q / 6;
                                dp[i][to][0][0] += dp[i - 1][j][1][0] * (1 - q) / 6;
                            }
                            else{ // special 2 -> special 2
                                int r = g.mp[i >= 70][1][nxt - 63];
                                ld q = (i == 90 ? 1.0 : prob[r]);

                                dp[i][nxt][1][1] += dp[i - 1][j][1][0] * q / 6;
                                dp[i][nxt][1][0] += dp[i - 1][j][1][0] * (1 - q) / 6;
                            }
                        }
                    }
                    else{ // out -> out
                        nxt %= s;
                        int r = g.grid[nxt];

                        if(i >= 70 && (nxt + 3) % 6 == 0){
                            r = 3;
                        }

                        ld q = (i == 90 ? 1.0 : prob[r]);

                        dp[i][nxt][0][1] += dp[i - 1][j][0][0] * q / 6;
                        dp[i][nxt][0][0] += dp[i - 1][j][0][0] * (1 - q) / 6; 
                    }
                }
            }
        }
    }

    for(int i = 0; i <= 90; i++){
        ld p = 0;
        
        for(int j = 0; j < s + 2 * 9; j++){
            p += dp[i][j][0][1] + dp[i][j][1][1];
        }

        cout << fixed << setprecision(20) << p << "\n";
    }
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
 
    while(t--){
        solve();
    }

    return 0;
}
