#include <string>
#include <vector>

using namespace std;

bool visited[51][51][2510];
string ret = "";
int nsz, msz;

bool chk(int n, int m)
{
    return n>=1&&m>=1&&n<=nsz&&m<=msz;
}

char dir1[4] = {'d', 'l', 'r', 'u'};
int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
int k1;
int rr, cc;

bool dfs(int n, int m, int depth)
{
    visited[n][m][depth] = true;
    if(depth == k1)
    {
        if(n == rr && m == cc)
            return true;
        else
            return false;
    }
    for(int i=0;i<4;++i)
    {
        int ny = n + dir[i][0];
        int nx = m + dir[i][1];
        if(chk(ny, nx) && !visited[ny][nx][depth+1])
        {
            ret.push_back(dir1[i]);
            if(dfs(ny, nx, depth+1))
                return true;
            ret.pop_back();
        }
    }
    return false;
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    nsz = n;
    msz = m;
    rr = r;
    cc = c;
    k1 = k;
    if(dfs(x, y, 0))
        answer = ret;
    else
        answer = "impossible";
    return answer;
}