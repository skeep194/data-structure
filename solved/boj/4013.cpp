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

vector<vector<int>> adj;
int n, m;
int num[500100];
int k;
int group[500100];
int sccnum;
int sccatm[500100];
stack<int> s;
int atm[500100];
bool sccrestaurant[500100];
bool restaurant[500100];
int ss, p;
int scc(int here)
{
    s.push(here);
    int ret = num[here] = ++k;
    for(auto next : adj[here])
    {
        if(!num[next]) ret = min(ret, scc(next));
        else if(!group[next]) ret = min(ret, num[next]);
    }
    if(ret == num[here])
    {
        sccnum++;
        while(!s.empty())
        {
            int x = s.top();
            group[x] = sccnum;
            sccatm[group[x]] += atm[x];
            if(restaurant[x])
            {
                sccrestaurant[group[x]] = true;
            }
            s.pop();
            if(x == here) break;
        }
    }
    return ret;
}





bool visited[500100];
vector<vector<int>> adj2;
int indegree[500100];

void make_graph(int here)
{
    // cout<<here<<endl;
    visited[here] = true;
    for(auto next : adj[here])
    {
        if(group[next] != group[here])
        {
            adj2[group[here]].push_back(group[next]);
            indegree[group[next]]++;
        }

        if(!visited[next])
        {
            make_graph(next);
        }
    }
}
int cache[500100];

void solve()
{
    cin>>n>>m;
    adj.assign(n+10, vector<int>());
    adj2.assign(n+10, vector<int>());
    for(int i=0;i<m;++i)
    {
        int a, b;
        cin>>a>>b;
        a--;
        b--;

        adj[a].push_back(b);
    }
    for(int i=0;i<n;++i)
    {
        cin>>atm[i];
    }
    cin>>ss>>p;
    ss--;
    for(int i=0;i<p;++i)
    {
        int x;
        cin>>x;
        restaurant[x-1] = true;
    }
    for(int i=0;i<n;++i)
    {
        if(!num[i])
        {
            scc(i);
        }
    }
    make_graph(ss);
    int ret = -1;
    queue<int> q;
    q.push(group[ss]);
    while(!q.empty())
    {
        int here = q.front();
        // cout<<here<<endl;
        q.pop();
        if(sccrestaurant[here])
            ret = max(ret, cache[here]+sccatm[here]);
        for(auto next : adj2[here])
        {
            cache[next] = max(cache[next], cache[here]+sccatm[here]);
            if(--indegree[next] == 0)
            {
                q.push(next);
            }
        }
    }
    assert(ret != -1);
    cout<<ret;
}