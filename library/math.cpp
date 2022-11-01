long long modpow(long long a, int b, int mod)
{
    if(b == 0) return 1;
    if(b%2 == 1) return a * modpow(a, b-1, mod) % mod;
    long long half = modpow(a, b/2, mod);
    return half*half%mod;
}

long long isqrt(long long x)
{
    
}