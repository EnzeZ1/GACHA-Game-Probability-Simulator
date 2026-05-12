#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const double pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = (ll)4e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e5 + 10, M = 2 * N; 

ld dp[2][81][7][2];
ld _p[1201];
// #num, #pulls, #up, #120 or not

void distr() {
    ofstream fout("result.txt");
    if (!fout.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }

    fout << "Pulls\tProbability\n";
    for (int i = 1; i <= 1200; i++) {
        fout << i << "\t" << fixed << setprecision(20) << _p[i] << "\n";
    }
    fout.close();
}

void solve(){
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][1] = 1;

    for(int s = 0; s <= 1200; s++){
        int i = s & 1, _ = i ^ 1;
        memset(dp[_], 0, sizeof(dp[_]));
        
        for(int j = 0; j <= chmin(s, 79); j++){
            ld p = (j >= 65 ? (j - 64) * 0.05 + 0.008 : 0.008);
            for(int k = 0; k <= 5; k++){
                if(!k && s == 119){
                    dp[_][0][k + 1][0] += dp[i][j][k][1];
                }
                else if(j == 79){
                    dp[_][0][k + 1][0] += dp[i][j][k][1] * 0.5;
                    dp[_][0][k + 1][0] += dp[i][j][k][0] * 0.5;
                    dp[_][0][k][1] += dp[i][j][k][1] * 0.5;
                    dp[_][0][k][0] += dp[i][j][k][0] * 0.5;
                }
                else{
                    if(s < 119){    
                        dp[_][0][k + 1][0] += dp[i][j][k][1] * p * 0.5;
                        dp[_][0][k][1] += dp[i][j][k][1] * p * 0.5;
                        dp[_][j + 1][k][1] += dp[i][j][k][1] * (1 - p);
                    }

                    dp[_][0][k + 1][0] += dp[i][j][k][0] * p * 0.5;
                    dp[_][0][k][0] += dp[i][j][k][0] * p * 0.5;
                    dp[_][j + 1][k][0] += dp[i][j][k][0] * (1 - p);
                } 
            }
        }

        if((s + 1) % 240 == 0 && (s + 1) >= 240){
            for(int j = 0; j <= chmin(79, s + 1); j++){
                for(int k = 5; k >= 0; k--){
                    dp[_][j][k + 1][0] += dp[_][j][k][0];
                    dp[_][j][k][0] = 0;
                }
            }
        }

        for(int j = 0; j <= 80; j++){
            _p[s + 1] += dp[_][j][6][0] + dp[_][j][6][1];
        }
    }
    distr();
}
 
int main(){
    ios::sync_with_stdio(true);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
 
    while(t--){
        solve();
    }
    return 0;
}
