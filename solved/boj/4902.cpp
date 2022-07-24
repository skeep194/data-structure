#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
// #define MULTITC
#define endl '\n'
// #define int long long
void solve();
int32_t main()
{
    int tc = 1;
    fastio;
    #ifdef MULTITC
        cin>>tc;
    #endif
    while(tc--)
        solve();
}
//saigo nankade sonna yume watashi tsuburarinn..

bool chk(int sz, int k)
{
    return k >= 0 && k < sz;
}

void solve()
{
    int t = 0;
    while(true)
    {
        ++t;
        int n;
        cin>>n;
        if(n == 0) return;
        vector<vector<i64>> arr;
        i64 ret = numeric_limits<i64>::min();
        for(int i=1;i<=n;++i)
        {
            arr.push_back(vector<i64>());
            for(int j=0;j<i*2-1;++j)
            {
                i64 x;
                cin>>x;
                arr.back().push_back(x);
                ret = max(ret, x);
            }
        }
        vector<vector<i64>> dp = arr;
        for(int i=0;i<arr.size();++i)
        {
            for(int j=1;j<arr[i].size();++j)
            {
                arr[i][j] += arr[i][j-1];
            }
        }
        
        for(int i=2;i<=n;++i)
        {
            int rng = i*2-1;
            for(int j=0;j<arr.size();++j)
            {
                for(int k=0;k<arr[j].size();++k)
                {
                    if(k%2 == 0)
                    {
                        if(!chk(arr.size(), j+i-1)) continue;
                        int start = k;
                        int end = k+i*2-2;
                        // cout<<arr[j+i-1].size()<<' '<<j<<' '<<k<<' '<<start<<' '<<end<<chk(arr[j+i-1].size(), start)<<' '<<chk(arr[j+i-1].size(), end)<<' '<<endl;
                        if(!chk(arr[j+i-1].size(), start) || !chk(arr[j+i-1].size(), end))  continue;
                        // cout<<arr[j+i-1].size()<<' '<<j<<' '<<k<<' '<<start<<' '<<end<<chk(arr[j+i-1].size(), start)<<' '<<chk(arr[j+i-1].size(), end)<<' '<<endl;
                        dp[j][k] = dp[j][k]+(arr[j+i-1][end] - (start == 0 ? 0 : arr[j+i-1][start-1]));
                        // cout<<dp[j][k]<<endl;
                        ret = max(ret, dp[j][k]);
                    }
                    else
                    {
                        if(!chk(arr.size(), j-i+1)) continue;
                        int end = k;
                        int start = k-i*2+2;
                        // cout<<j-i+1<<' '<<j<<' '<<k<<' '<<start<<' '<<end<<endl;
                        if(!chk(arr[j-i+1].size(), start) || !chk(arr[j-i+1].size(), end)) continue;
                        // cout<<j-i+1<<' '<<j<<' '<<k<<' '<<start<<' '<<end<<endl;
                        dp[j][k] = dp[j][k]+(arr[j-i+1][end] - (start == 0 ? 0 : arr[j-i+1][start-1]));
                        ret = max(ret, dp[j][k]);
                    }
                }
            }
        }
        cout<<t<<". "<<ret<<endl;
    }
}