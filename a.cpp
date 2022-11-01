#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> adj;
vector<vector<int>> childs;
int dfsorder[200100];
int range[210000];
int cntchild[200100];
int cnt;
long long precal[200100];

int dfs(int here, int prev)
{
    dfsorder[here] = cnt++;
    cntchild[here] = 1;
    for(auto next : adj[here])
    {
        if(next != prev)
        {
            childs[here].push_back(next);
            cntchild[here] += dfs(next, here);
        }
    }
    for(auto next : adj[here])
    {
        if(next != prev)
            precal[here] += (long long)(n-1-cntchild[next]) * (long long)cntchild[next];
    }
    int up = n - cntchild[here];
    precal[here] += (long long)(n-1-up) * (long long)up;
    precal[here] /= 2;
    range[here] = dfsorder[here] + cntchild[here] - 1;
    return cntchild[here];
}

int32_t main()
{
    int q;
    cin>>n>>q;
    childs.resize(n+1, vector<int>());
    adj.resize(n+1, vector<int>());
    for(int i=0;i<n-1;++i)
    {
        int a, b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    int root = 1;
    while(q--)
    {
        int a, x;
        cin>>a>>x;
        if(a == 1)
        {
            root = x;
        }
        else
        {
            long long except = 0;
            if(dfsorder[x] < dfsorder[root] && dfsorder[root] <= range[x])
            {
                int low = 0;
                int high = childs[x].size()-1;
                while(low < high)
                {
                    int mid = (low+high)/2;
                    if(dfsorder[childs[x][mid]] < dfsorder[root])
                    {
                        low = mid + 1;
                    }
                    else
                    {
                        high = mid;
                    }
                }
                except = cntchild[childs[x][low]];
            }
            else
            {
                except = n - cntchild[x];
            }
            cout<<precal[x] - except*(n-1-except) + n-1 - except<<endl;
        }
    }
}

//a1*a2 + a2*a3 + a1*a3
//(a1(a2+a3) + a2(a1+a3) + a3(a2+a1)) /2