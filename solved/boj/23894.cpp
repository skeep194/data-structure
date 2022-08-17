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
int cache[200200][30];
int visited[200100];
int dist[200100];
vector<int> arr;

vector<vector<int>> adj;

void solve()
{
    memset(dist, -1, sizeof(dist));
    int m;
    cin>>m;
    arr.resize(m);
    adj.assign(m, vector<int>());
    for(int i=0;i<m;++i)
    {
        cin>>arr[i];
        arr[i]--;
        adj[arr[i]].push_back(i);
    }

    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while(!q.empty())
    {
        int here = q.front();
        q.pop();
        for(auto next : adj[here])
        {
            if(dist[next] == -1)
            {
                dist[next] = dist[here]+1;
                q.push(next);
            }
        }
    }

    int qx;
    cin>>qx;
    
    for(int i=0;i<m;++i)
    {
        cache[i][0] = arr[i];
    }
    for(int i=1;i<30;++i)
    {
        for(int j=0;j<m;++j)
        {
            cache[j][i] = cache[cache[j][i-1]][i-1];
        }
    }
    while(qx--)
    {
        int x;
        cin>>x;
        if(x == 2)
        {
            int a, b;
            cin>>a>>b;
            b--;
            int ret = b;
            if(dist[ret] != -1)
            {
                int d = dist[ret];
                if(d < a)
                {
                    a -= d;
                    ret = 0;
                    if(dist[arr[0]] != -1)
                    {
                        int cycle_size = dist[arr[0]]+1;
                        a %= cycle_size;
                    }
                    if(a > 0)
                    {
                        a--;
                        ret = arr[0];
                    }
                }
            }
            for(int i=0;i<30;++i)
            {
                if(a & (1<<i))
                {
                    ret = cache[ret][i];
                }
            }
            cout<<ret+1<<endl;
        }
        else
        {
            int y;
            cin>>y;
            arr[0] = y-1;
        }
    }
}

/*
합성함수와 쿼리 2
m제한 잘못봐서 2^20이 아니라 2^30까지 봐야하는데 실수함
이동해서 0으로 갈 수 있는 정점을 찾는 방법에서 플러드필 사용하려다 반례 발견

정점 == 간선인 그래프일 때 x로 가는 정점 구하는 방법
그냥 역그래프 만들고 x에서 bfs 돌리는게 맞음
*/
