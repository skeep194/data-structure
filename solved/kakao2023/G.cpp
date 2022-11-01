#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;

int point[110];
int cnt[110];

int dfs(int here)
{
    // cout<<here<<endl;
    if(adj[here].size() == 0)
        return here;
    return dfs(adj[here][(point[here]++)%adj[here].size()]);
}

vector<int> solution(vector<vector<int>> edges, vector<int> target) {
    adj.resize(edges.size()+1);
    for(auto& i : edges)
    {
        adj[i[0]-1].push_back(i[1]-1);
    }
    for(auto& i : adj)
        sort(i.begin(), i.end());
    for(int i=0;i<target.size();++i)
    {
        if(!adj[i].empty() && target[i] != 0)
        {
            return {-1};
        }
    }
    vector<int> target2 = target;
    int sum = accumulate(target.begin(), target.end(), 0);
    vector<int> answer;
    vector<int> v;
    while(sum)
    {
        int here = dfs(0);
        v.push_back(here);
        cnt[here]++;
        if(target[here] > 0)
        {
            target[here] -= 3;
            if(target[here] <= 0)
                sum -= target2[here];
        }
    }
    // for(auto i : v)
    //     cout<<i<<' ';
    for(int i=0;i<v.size();++i)
    {
        answer.push_back(1);
        target2[v[i]]--;
    }
    for(int i=0;i<target2.size();++i)
    {
        if(target2[i] < 0)
        {
            return {-1};
        }
    }
    for(int i=(int)v.size()-1;i>=0;--i)
    {
        if(target2[v[i]] > 1)
        {
            answer[i] = 3;
            target2[v[i]] -= 2;
        }
        else if(target2[v[i]] > 0)
        {
            answer[i] = 2;
            target2[v[i]] -= 1;
        }
    }
    for(int i=0;i<target2.size();++i)
    {
        if(target2[i] != 0)
        {
            return {-1};
        }
    }
    return answer;
}
