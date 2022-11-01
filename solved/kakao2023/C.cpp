#include <string>
#include <vector>
#include <iostream>
using namespace std;
pair<int,int> answer;
int arr[10];

void dfs(int here, vector<vector<int>>& users, vector<int>& emoticons)
{
    if(here == emoticons.size())
    {
        pair<int,int> ret = {0, 0};
        for(auto& p : users)
        {
            long long a = p[0];
            long long b = p[1];
            bool k = false;
            long long sum = 0;
            for(int i=0;i<emoticons.size();++i)
            {
                if(a <= arr[i])
                {
                    long long buy = emoticons[i] * (100-arr[i]) / 100;
                    long long u = b;
                    // cout<<a<<' '<<arr[i]<<' '<<buy<<' '<<u<<endl;
                    sum += buy;
                }
            }
            if(sum >= b)
            {
                ret.first++;
            }
            else
            {
                ret.second += sum;
            }
        }
        // cout<<endl;
        // cout<<ret.first<<' '<<ret.second<<endl;
        answer = max(ret, answer);
        return;
    }
    arr[here] = 10;
    dfs(here+1, users, emoticons);
    arr[here] = 20;
    dfs(here+1, users, emoticons);
    arr[here] = 30;
    dfs(here+1, users, emoticons);
    arr[here] = 40;
    dfs(here+1, users, emoticons);
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    
    dfs(0, users, emoticons);
    vector<int> a = {answer.first, answer.second};
    return a;
}