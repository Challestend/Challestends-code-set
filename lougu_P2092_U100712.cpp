#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define maxn 4000005
long long n , prime[maxn] , isprime[maxn] ,fac[maxn], cntprime , p[maxn] ;
void euler()
{
    int k = std::sqrt(n);
    for(int i = 2 ; i <= k ; ++i)
    {
        if(!isprime[i]) prime[++cntprime] = i;
        for(int j = 1 ; j <= cntprime && i*prime[j] <= k ; ++j)
        {
            isprime[i*prime[j]] = 1;
            if(!(i%prime[j])) break;
        }

    }
}
int main()
{
    scanf("%lld",&n);
    if(n == 2 || n == 1)
    {
        printf("1\n0");
        return 0;
    }
    euler();
    int k = n;
    for(int i = 1 ; i <= cntprime ; ++i)
    {
        if(n == 1)
            break;
        if(!(n%prime[i])) ++fac[0] , fac[fac[0]] = prime[i];
        while(!(n%prime[i])) n /= prime[i] , ++p[fac[0]];
    }
    if(k == n)
    {printf("1\n0");return 0;}
    if(fac[0] == 1 && p[1] == 1)
    {printf("1\n0");return 0;}
    if(n != 1) prime[++cntprime] = n , ++fac[0], fac[fac[0]] = n , p[fac[0]] = 1 ;
    int ans = 0;
    for(int i = 1 ; i <= fac[0] ; ++i)
        ans += p[i];
    if(ans > 2)
    {
        // printf("%d\n",ans);
        printf("1\n");
        if(p[1] > 1)
        {
            printf("%lld",1ll*fac[1]*fac[1]);
            return 0;
        }
        printf("%lld",1ll*fac[1]*fac[2]);
    }
    else printf("2");
}
