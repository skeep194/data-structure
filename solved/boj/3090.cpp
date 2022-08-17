
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

struct disjointset
{
    vector<int> parents;
    disjointset(int n) : parents(n) {
        for(int i=0;i<n;++i)
        {
            parents[i] = i;
        }
    }
    int find(int x)
    {
        return parents[x] == x ? x : (parents[x] = find(parents[x]));
    }
    void Union(int x, int y)
    {
        x = find(x);
        y = find(y);
        parents[y] = x;
    }
};
//saigo nankade sonna yume watashi tsuburarinn..

void solve()
{
    int n, t;
    cin>>n>>t;
    vector<int> reconstruct;
    vector<int> arr(n);
    for(auto& i : arr) cin>>i;
    int low = 0, high = 1e9;
    auto avail = [&](int x) {
        vector<int> a = arr;
        int cnt = t;
        disjointset dsu(n);
        for(int i=0;i<n-1;++i)
        {
            //내일 풀기위해..
            //이거 k차이나면 계속 분리집합 연쇄해서 내리면됨
            //그리고 마지막에 t>=0이면 성공
            //재구성은 avail함수 돌리고 분리집합 안에 있는 원소들이 k차이난다
            int p = dsu.find(i);
            int here = a[p] - (i-p)*x;
            if(here + x < a[i+1])
            {
                cnt -= a[i+1] - (here + x);
                a[i+1] = here + x;
            }
            else if(here - x >= a[i+1])
            {
                int nxt = i+1;
                for(int j=i;j>=0;j--)
                {
                    int p = j;
                    j = dsu.find(j);
                    int sz = p - j + 1;
                    here = a[j] - (sz-1)*x;
                    if(!(here - x >= a[nxt])) break;
                    cnt -= sz * (here - a[nxt] - x);
                    a[j] -= here - a[nxt] - x;
                    dsu.Union(j, nxt);
                    nxt = j;
                }
            }
        }
        reconstruct.clear();
        for(int i=0;i<n;++i)
        {
            if(dsu.find(i) == i)
                reconstruct.push_back(a[i]);
            else
                reconstruct.push_back(reconstruct.back() - x);
        }
        return cnt >= 0;
    };
    while(low < high)
    {
        int mid = (low+high)/2;
        if(!avail(mid))
            low = mid +1;
        else
            high = mid;
        
    }
    avail(low);
    for(auto i : reconstruct)
        cout<<i<<' ';
}