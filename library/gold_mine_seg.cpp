struct gold_mine
{
    long long l, r, val, sum;
    gold_mine(): l(0), r(0), val(0), sum(0) {}
    gold_mine(int x): l(x), r(x), val(x), sum(x) {}
    gold_mine merge(const gold_mine& other) const {
        gold_mine ret;
        ret.sum = sum + other.sum;
        ret.l = max(l, sum+other.l);
        ret.r = max(other.r, other.sum+r);
        ret.val = max({val, other.val, r + other.l, ret.l, ret.r});
        return ret;
    }
};

gold_mine segtree[100100*4];

void update(int num, int start, int end, int val, int pos)
{
    if(start > pos || end < pos)
        return;
    segtree[num].val = segtree[num].l = segtree[num].r = segtree[num].sum = segtree[num].val + val;
    int mid = start+end>>1;
    if(start != end)
    {
        update(num*2, start, mid, val, pos);
        update(num*2+1, mid+1, end, val, pos);
        segtree[num] = segtree[num*2].merge(segtree[num*2+1]);
    }
}