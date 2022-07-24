
//bottom up segtree. example for sum query
void update(int i, int k)
{
	for(segtree[i+=n] = k; i > 1; i >>= 1)
	{
		segtree[i>>1] = segtree[i]+segtree[i^1];
	}
}

int sum(int a, int b)
{
	int res = 0;
	for(a+=n,b+=n;a<b;a>>=1,b>>=1) {
		if(a&1) res += segtree[a++];
		if(b&1) res += segtree[--b];
	}
	return res;
}