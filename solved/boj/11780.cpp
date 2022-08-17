#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
// #define MULTITC
#define endl '\n'
#define int long long
void solve();
int32_t main()
{
    int tc = 1;
    #ifndef LOCAL
        fastio;
    #endif
    #ifdef MULTITC
        cin>>tc;
    #endif
    while(tc--)
        solve();
}
//saigo nankade sonna yume watashi tsuburarinn..

int n, m;
int arr[101][101];
int reconstruct[101][101];
const int INF = 1e15;

void solve()
{
    cin>>n>>m;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            arr[i][j] = INF;
            reconstruct[i][j] = -1;
        }
    }
    for(int i=0;i<m;++i)
    {
        int a, b, c;
        cin>>a>>b>>c;
        a--;b--;
        arr[a][b] = min(arr[a][b], c);
        reconstruct[a][b] = a;
    }
    for(int k=0;k<n;++k)
    {
        for(int i=0;i<n;++i)
        {
            for(int j=0;j<n;++j)
            {
                if(i == j) continue;
                if(arr[i][j] > arr[i][k]+arr[k][j])
                {
                    arr[i][j] = arr[i][k]+arr[k][j];
                    if(reconstruct[k][j] != -1)
                    {
                        reconstruct[i][j] = reconstruct[k][j];
                    }
                    else
                    {
                        reconstruct[i][j] = k;
                    }
                }
            }
        }
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            cout<<(arr[i][j] == INF ? 0 : arr[i][j])<<' ';
        }
        cout<<endl;
    }
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if(arr[i][j] == INF)
            {
                cout<<0<<endl;
                continue;
            }
            vector<int> v;
            v.push_back(j);
            while(reconstruct[i][v.back()] != -1)
            {
                v.push_back(reconstruct[i][v.back()]);
            }
            reverse(v.begin(), v.end());
            cout<<v.size()<<' ';
            for(auto i : v) cout<<i+1<<' ';
            cout<<endl;
        }
    }
}