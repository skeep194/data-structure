#include <bits/stdc++.h>
using namespace std;
#define fastio cin.tie(0)->sync_with_stdio(0);
// typedef __int128_t i128;
typedef int64_t i64;
typedef int32_t i32;
template<typename T>
inline T midpoint(const T& a, const T& b) { return a+(b-a)/2; }
#define MULTITC
#define endl '\n'
// #define int long long
void solve(int tc);
int32_t main()
{
    int tc = 1;
    #ifndef LOCAL
        fastio;
    #endif
    #ifdef MULTITC
        cin>>tc;
    #endif
    for(int i=1;i<=tc;++i)
        solve(i);
}
//saigo nankade sonna yume watashi tsuburarinn..

void solve(int tc)
{
    int n, m, k;
    cin>>n>>m>>k;
    vector<int> arr(k);
    for(auto& i : arr)cin>>i;
    int cnt = n*m-3;
    int here = k;
    priority_queue<int> pq;
    for(int i=0;i<k;++i)
    {
        while(!pq.empty() && pq.top() == here)
        {
            pq.pop();
            --here;
            ++cnt;
        }
        if(arr[i] == here)
        {
            --here;
        }
        else
        {
            pq.push(arr[i]);
            if(--cnt <= 0)
            {
                cout<<"TIDAK"<<endl;
                return;
            }
        }
    }
    cout<<"YA"<<endl;
}