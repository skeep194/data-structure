struct edge
{
    edge() {}
    edge(int x): next(x) {}
    int next;
};

template<class T>
struct weightedEdge : edge {
    T weight;
    bool operator<(const weightedEdge& other) const {
        return weight > other.weight;
    }
};


namespace Graph
{
    struct scc
    {
        scc(vector<vector<edge>> adj): adj(adj), num(adj.size(), -1), sccnum(adj.size(), -1) {}
        vector<int> num, sccnum, s;
        int cnt = 0;
        int scccnt = 0;
        vector<vector<edge>> adj;
        int sccdfs(int here)
        {
            int ret = num[here] = cnt++;
            s.push_back(here);
            for(auto [next] : adj[here])
            {
                if(num[next] == -1) ret = min(ret, sccdfs(next));
                else if(sccnum[next] == -1) ret = min(ret, num[next]);
            }
            if(ret == num[here])
            {
                while(1)
                {
                    int k = s.back();
                    sccnum[s.back()] = scccnt;
                    s.pop_back();
                    if(k == here)
                        break;
                }
                scccnt++;
            }
            return ret;
        }
        vector<int> getScc()
        {
            for(int i=0;i<adj.size();++i)
            {
                if(num[i] == -1)
                {
                    sccdfs(i);
                }
            }
            return sccnum;
        }
    };
};