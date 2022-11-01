#include <string>
#include <vector>
#include <bitset>
#include <iostream>
using namespace std;

bitset<64> k;
bool ret = true;
int cnt = 0;
int v;
void dfs(int depth, int num, bool ok)
{
    // cout<<(v-num-1)<<' ';
    if(!ok && (k[v - num-1]))
        ret = false;
    if(!k[v - num - 1])
        ok = false;
    else
        ++cnt;
    if(depth == 0)
    {
        return;
    }
    dfs(depth-1, num-(1ll<<depth)/2, ok);
    dfs(depth-1, num+(1ll<<depth)/2, ok);
}

int chk(long long here)
{
    k = here;
    ret = true;
    for(int i=1;i<7;++i)
    {
        cnt = 0;
        ret = true;
        v = (1ll<<i);
        dfs(i-1, (1ll<<i) / 2, true);
        // cout<<cnt<<endl;
        // cout<<cnt<<endl;
        if(ret && cnt == k.count())
            return true;
    }

    return false;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    for(auto here : numbers)
    {
        answer.push_back(chk(here));
    }
    return answer;
}