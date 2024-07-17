#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
// typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
const int INTINF = numeric_limits<i32>::max();
const long long LONGINF = numeric_limits<i64>::max();
template <typename T>
inline T midpoint(const T &a, const T &b) { return a + (b - a) / 2; }
// #define MULTITC
#define endl '\n'
// #define int long long
void solve(int tc);
void input();
int32_t main()
{
    int tc = 1;
#ifndef LOCAL
    fastio;
#endif
#ifdef MULTITC
    cin >> tc;
#endif
    for (int i = 1; i <= tc; ++i)
    {
        input();
        solve(i);
    }
}
template <typename T>
istream &operator>>(istream &is, vector<T> &arr)
{
    for (auto &i : arr)
        is >> i;
    return is;
}
template <typename T>
ostream &operator<<(ostream &os, vector<T> &arr)
{
    for (auto &i : arr)
        os << i << ' ';
    return os;
}
// saigo nankade sonna yume watashi tsuburarinn..

int n;
vector<vector<pair<int, int>>> adj;
int group[100100];
int group_sz[100100] = {
    1,
};
int depth[100100];
int seg_num[100100];
int parent[100100];
int group_root[100100] = {
    1,
};
int group_cnt;

int cache[100100];

int subtree(int here, int prev)
{
    int &ret = cache[here];
    if (ret != -1)
        return ret;
    ret = 1;
    for (auto [next, _] : adj[here])
    {
        if (next == prev)
            continue;
        ret += subtree(next, here);
    }
    return ret;
}

vector<vector<int>> seg;

void update(int i, int k, vector<int> &segtree)
{
    i++;
    for (segtree[i += segtree.size() / 2] = k; i > 1; i >>= 1)
    {
        segtree[i >> 1] = max(segtree[i], segtree[i ^ 1]);
    }
}

int sum(int a, int b, vector<int> &segtree)
{
    a++;
    b += 2;
    int res = 0;
    for (a += segtree.size() / 2, b += segtree.size() / 2; a < b; a >>= 1, b >>= 1)
    {
        if (a & 1)
            res = max(res, segtree[a++]);
        if (b & 1)
            res = max(res, segtree[--b]);
    }
    return res;
}

vector<tuple<int, int, int>> edges;

int edge_to_vertex[100100];

void numbering(int here, int prev, int d)
{
    parent[here] = prev;
    depth[here] = d;
    int idx = -1;
    int maxi = 0;
    int x = 0;
    for (auto [next, _] : adj[here])
    {
        if (next == prev)
            continue;
        if (maxi < subtree(next, here))
        {
            maxi = subtree(next, here);
            idx = x;
        }
        x++;
    }
    x = 0;
    for (auto [next, _] : adj[here])
    {
        if (next == prev)
            continue;
        if (idx == x)
        {
            group[next] = group[here];
            seg_num[next] = seg_num[here] + 1;
            group_sz[group[next]] = seg_num[next] + 1;
        }
        else
        {
            group[next] = ++group_cnt;
            group_root[group[next]] = next;
            group_sz[group[next]] = 1;
        }
        numbering(next, here, d + 1);
        x++;
    }
}

void input()
{
    cin >> n;
    adj.resize(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        edges.push_back({a, b, c});
    }
}

int query(int a, int b)
{
    int ret = 0;
    while (group[a] != group[b])
    {
        if (depth[group_root[group[a]]] < depth[group_root[group[b]]])
            swap(a, b);
        ret = max(ret, sum(seg_num[group_root[group[a]]], seg_num[a], seg[group[a]]));
        a = parent[group_root[group[a]]];
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ret = max(ret, sum(seg_num[a] + 1, seg_num[b], seg[group[a]]));
    return ret;
}

void solve(int tc)
{
    memset(cache, -1, sizeof(cache));
    numbering(1, 0, 1);
    seg.resize(group_cnt + 1);
    for (int i = 0; i <= group_cnt; ++i)
    {
        seg[i].resize(group_sz[i] * 2 + 5);
    }
    int x = 1;
    for (auto [a, b, c] : edges)
    {
        if (depth[a] < depth[b])
        {
            swap(a, b);
        }
        edge_to_vertex[x] = a;
        update(seg_num[a], c, seg[group[a]]);
        ++x;
    }
    int q;
    cin >> q;
    while (q--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            b = edge_to_vertex[b];
            update(seg_num[b], c, seg[group[b]]);
        }
        else
        {
            cout << query(b, c) << endl;
        }
    }
}