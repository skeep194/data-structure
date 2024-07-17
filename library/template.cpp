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

void input()
{
}

void solve(int tc)
{
}