long long modpow(long long a, long long b, long long mod)
{
    if(b == 0) return 1;
    if(b%2 == 1) return (__int128_t) a * modpow(a, b-1, mod) % mod;
    long long half = modpow(a, b/2, mod);
    return (__int128_t)half*half%mod;
}

namespace prime
{
    bool primeCheck(long long n, int a)
    {
        if(a%n == 0) return true;
        long long k = n-1;
        while(1)
        {
            long long t = modpow(a, k, n);
            if(t == n-1) return true;
            if(k%2) return t == 1;
            k /= 2;
        }
        return false;
    }

    int int32[3] = {2, 7, 61};
    int int64[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    bool isPrime(long long n)
    {
        int* c = n > 1ll<<32 ? int64 : int32;
        int sz = n > 1ll<<32 ? 13 : 3;
        for(int i=0;i<sz;++i)
        {
            if(!primeCheck(n, c[i]))
            {
                return false;
            }
        }
        return true;
    }
};

namespace pollard
{
    long long go(long long x, long long c, long long n)
    {
        return ((__int128_t)x * (__int128_t)x + (__int128_t)c) % (__int128_t)n;
    }
    long long factor(long long n)
    {
        long long a, b;
        a = b = rand()%(n-2)+2;
        long long c = rand()%20+1;
        long long ret = 1;
        while(ret == 1)
        {
            a = go(a, c, n);
            b = go(go(b, c, n), c, n);
            ret = gcd(abs(a-b), n);
            if(ret == n)
            {
                return factor(n);
            }
        }
        return ret;
    }
    void factors(long long n, vector<long long>& arr)
    {
        if(n == 1) return;
        if(n%2 == 0)
        {
            arr.push_back(2);
            factors(n>>1, arr);
            return;
        }
        if(prime::isPrime(n))
        {
            arr.push_back(n);
            return;
        }
        long long here = factor(n);
        factors(here, arr);
        factors(n/here, arr);
    }
};