struct MCMF {
    struct edge {
        int to, flow, cost, capacity;
        edge(int _to, int _capacity, int _cost): to(_to), flow(0), cost(_cost), capacity(_capacity), rev(nullptr) {}
        edge* rev;
    };

    vector<vector<edge*>> graph;

    MCMF(int _n): graph(_n) {}

    void addEdge(int here, int to, int capacity, int cost, bool undirected = false)
    {
        edge* h = new edge(to, capacity, cost);
        edge* t = new edge(here, undirected ? capacity : 0, -cost);
        h->rev = t;
        t->rev = h;
        graph[here].push_back(h);
        graph[to].push_back(t);
    }

    pair<int,int> getMaxFlowMinCost(int source, int sink)
    {
        int maxFlow = 0, minCost = 0;
        while(true)
        {
            vector<pair<int,int>> parents(graph.size(), {-1, -1});
            parents[source] = {source, source};
            queue<int> q;
            q.push(source);
            vector<int> dist(graph.size(), 1e15);
            dist[source] = 0;
            vector<bool> inQueue(graph.size(), false);
            inQueue[source] = true;
            while(!q.empty())
            {
                int here = q.front();
                q.pop();
                inQueue[here] = false;
                int cnt = 0;
                for(edge* next : graph[here])
                {
                    if(next->capacity - next->flow > 0 && dist[next->to] > dist[here]+next->cost)
                    {
                        dist[next->to] = dist[here]+next->cost;
                        parents[next->to] = {here, cnt};
                        if(!inQueue[next->to])
                        {
                            q.push(next->to);
                            inQueue[next->to] = true;
                        }
                    }
                    ++cnt;
                }
            }

            if(parents[sink].first == -1)
                break;

            int flow = numeric_limits<int>::max();

            for(int i=sink;i!=source;i=parents[i].first)
            {
                flow = min(flow, graph[parents[i].first][parents[i].second]->capacity-graph[parents[i].first][parents[i].second]->flow);
            }
            maxFlow += flow;

            for(int i=sink;i!=source;i=parents[i].first)
            {
                minCost += flow * graph[parents[i].first][parents[i].second]->cost;
                graph[parents[i].first][parents[i].second]->flow += flow;
                graph[parents[i].first][parents[i].second]->rev->flow -= flow;
            }
        }
        return {maxFlow, minCost};
    }
};

struct Dinic
{
    int source, sink;
    vector<vector<int>> capacitys, graph;
    vector<int> level, work;

    void setFlow(int _source, int _sink)
    {
        source = _source;
        sink = _sink;
    }

    Dinic(int n) : capacitys(n, vector<int>(n)), graph(n), level(n, -1), work(n) {}

    void addEdge(int a, int b, int capacity, bool undirected=false)
    {
        capacitys[a][b] = capacity;
        if(undirected) capacitys[b][a] = capacity;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bool bfs()
    {
        queue<int> q;
        q.push(source);
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        while(!q.empty())
        {
            int here = q.front();
            q.pop();
            for(auto to : graph[here])
            {
                if(level[to] == -1 && capacitys[here][to] > 0)
                {
                    q.push(to);
                    level[to] = level[here] + 1;
                }
            }
        }
        return level[sink] != -1;
    }

    int dfs(int here, int flow)
    {
        if(here == sink) return flow;
        for(int& i = work[here];i < graph[here].size();++i)
        {
            int to = graph[here][i];
            int c = capacitys[here][to];
            if(c > 0 && level[here] + 1 == level[to])
            {
                int ret = dfs(to, min(flow, c));
                if(ret > 0)
                {
                    capacitys[here][to] -= ret;
                    capacitys[to][here] += ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    int getMaxFlow(int _source, int _sink)
    {
        int ret = 0;
        setFlow(_source, _sink);
        while(bfs())
        {
            fill(work.begin(), work.end(), 0);
            while(1)
            {
                int here = dfs(source, numeric_limits<int>::max());
                if(here <= 0) break;
                ret += here;
            }
        }
        return ret;
    }
};