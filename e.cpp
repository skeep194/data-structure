#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
// typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
template<typename T>
inline T midpoint(const T& a, const T& b) { return a+(b-a)/2; }
// #define MULTITC
#define endl '\n'
// #define int long long
void solve(int tc);
int32_t main()
{
    int tc = 1;
    #ifndef LOCAL
        fastio;
    #endif
    #ifdef MULTITC
        cin>>tc;
    #endif
    for(int i=1;i<=tc;++i)
        solve(i);
}

void update(int i, int k, vector<int>& segtree)
{
    for(segtree[i+=segtree.size()/2] = k; i > 1; i >>= 1)
    {
        segtree[i>>1] = max(segtree[i], segtree[i^1]);
    }
}

int sum(int a, int b, vector<int>& segtree)
{
    int res = 0;
    for(a+=segtree.size()/2,b+=segtree.size()/2;a<b;a>>=1,b>>=1) {
        if(a&1) res = max(res, segtree[a++]);
        if(b&1) res = max(res, segtree[--b]);
    }
    return res;
}

int parent[100100];
int indegree[100100];
int num[100100];

void solve(int tc)
{
    int n;
    cin>>n;
    for(int i=2;i<=n;++i)
    {
        cin>>parent[i];
        indegree[parent[i]]++;
    }
    fill(num, num+100100, 987654321);
    int here = 1;
    vector<int> arr;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<tuple<int,int,int>> p;
    for(int i=1;i<=n;++i)
    {
        if(indegree[i] == 0)
        {
            p.push_back({indegree[parent[i]],parent[i], i});
            // num[i] = here++;
            // pq.push({num[i], i});
        }
    }
    sort(p.rbegin(), p.rend());
    for(auto& [a, b, c] : p)
    {
        num[c] = here++;
        pq.push({num[c], c});
    }
    while(!pq.empty())
    {
        auto here = pq.top();
        pq.pop();
        arr.push_back(here.first);
        num[parent[here.second]] = min(num[parent[here.second]], here.first);
        if(--indegree[parent[here.second]] == 0)
        {
            pq.push({num[parent[here.second]], parent[here.second]});
        }
    }
    vector<int> segtree(200100);
    int ret = 0;
    for(int i : arr)
    {
        int here = sum(0, i+1, segtree)+1;
        update(i, here, segtree);
        ret = max(ret, here);
    }
    cout<<ret<<endl;
}