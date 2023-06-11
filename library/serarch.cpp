#include <bits/stdc++.h>

//0 0 0 0 .. (1) 1 1 if not found return b+1
long long find_first_true(long long a, long long b, const std::function<bool(long long x)>& avail)
{
    b++;
    while(a < b)
    {
        long long mid = a+(b-a)/2;
        if(avail(mid)) a = mid + 1;
        else b = mid;
    }
    return a;
}