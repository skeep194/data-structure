void update(int i, int k, vector<int>& segtree)
{
    for(segtree[i+=segtree.size()/2] = k; i > 1; i >>= 1)
    {
        segtree[i>>1] = segtree[i]+segtree[i^1];
    }
}

int sum(int a, int b, vector<int>& segtree)
{
    int res = 0;
    for(a+=segtree.size()/2,b+=segtree.size()/2;a<b;a>>=1,b>>=1) {
        if(a&1) res += segtree[a++];
        if(b&1) res += segtree[--b];
    }
    return res;
}


template<typename T>
struct SegmentTreeLazy
{
    SegmentTreeLazy(size_t n): tree(n*4), lazy(n*4) {}
    vector<T> tree, lazy;
    void propagate(int num, int low, int high)
    {
        int len = high - low + 1;
        tree[num] = tree[num] + lazy[num] * len;
        if(len > 1)
        {
            lazy[num*2] += lazy[num];
            lazy[num*2+1] += lazy[num];
        }
        lazy[num] = 0;
    }
    T query(int num, int low, int high, int start, int end)
    {
        propagate(num, low, high);
        if(high < start || end < low) return 0;
        if(start <= low && high <= end) return tree[num];
        int mid = (low+high)/2;
        T left = query(num*2, low, mid, start, end);
        T right = query(num*2+1, mid+1, high, start, end);
        return left + right;
    }
    void update(int num, int low, int high, int start, int end, T val)
    {
        propagate(num, low, high);
        if(high < start || end < low) return;
        if(start <= low && high <= end)
        {
            lazy[num] = val;
            propagate(num, low, high);
            return;
        }
        int mid = (low+high)/2;
        update(num*2, low, mid, start, end, val);
        update(num*2+1, mid+1, high, start, end, val);
        tree[num] = tree[num*2]+tree[num*2+1];
    }
    T query(int start, int end)
    {
        return query(1, 0, tree.size()/4-1, start, end);
    }
    void update(int start, int end, T val)
    {
        update(1, 0, tree.size()/4-1, start, end, val);
    }
};