struct MCMF {
    struct edge {
        int to, flow, cost, capacity;
        edge(int _to, int _capacity, int _cost): to(_to), flow(0), cost(_cost), capacity(_capacity), rev(nullptr) {}
        edge* rev;
    };

    vector<vector<edge*>> graph;

    MCMF(int _n): graph(_n) {}

    void addEdge(int here, int to, int capacity, int cost)
    {
        edge* h = new edge(to, capacity, cost);
        edge* t = new edge(here, 0, -cost);
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
            vector<int> dist(graph.size(), INF);
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