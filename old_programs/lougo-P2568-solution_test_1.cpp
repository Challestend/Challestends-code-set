#include <cstdio>
#include <algorithm>
#include <iostream>
#define oo 10000005
#define OO 10000006
using namespace std;
bool ok[OO];
int f[OO],p[6645480],n,tot;
long long ans,F[OO>>1];
int gcd(int a,int b)
{
    if (b==0) return a;
    if (a<b) return gcd(b,a);
    else return gcd(b,a%b);
}
int main()
{
    for (int i=2;i<=oo;i++) ok[i]=true;
    ok[1]=false;f[1]=1;
    for (int i=2;i<=oo;i++)
    {
        if (ok[i]==true)
        {
            f[i]=i-1;
            tot++; p[tot]=i;
        }
        for (int j=1;j<=tot;j++)
        {
            if (p[j]*i>oo) break;
            ok[p[j]*i]=false;
            if (gcd(p[j],i)==1) f[p[j]*i]=f[p[j]]*f[i];
            else f[p[j]*i]=p[j]*f[i];
            if (i%p[j]==0) break;
        }
    }
    for (int i=1;i<=oo/2;i++) F[i]=F[i-1]+2*f[i];
    cin >> n;
    for (int i=1;i<=tot;i++)
    {
        if (p[i]>n) break;
        ans+=F[n/p[i]]-1;
    }
    cout << ans << endl;
    return 0;
}
