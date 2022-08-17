struct disjointset
{
    vector<int> parents;
    vector<int> sz;
    disjointset(int n) : parents(n), sz(n) {
        for(int i=0;i<n;++i)
        {
            parents[i] = i;
            sz[i] = 1;
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
        sz[x] += sz[y];
    }
    int size(int x)
    {
        x = find(x);
        return sz[x];
    }
};