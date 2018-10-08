#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define max(a,b) ((a)>(b) ? (a): (b))
#define min(a,b) ((a)<(b) ? (a): (b))
#define LL  long long
using namespace std;

LL i,m,n,j,a[1000001],t,l,r,k;

int main()
{
	scanf("%lld",&t);
	for(;t;t--)
	{
		int ans=0;
		scanf("%lld%lld%lld",&l,&r,&k);
		if(l==k && k==0) ans+=1, printf("0 ");
		if(l<=1) ans+=1,printf("1 ");
		LL m=k;

		for(;m>0;m*=(LL)k)
		{
			if(m>=l && m<=r && (!(m%k))) ans+=1, printf("%lld ",m);
			if(m>=r) break;
			if(m%k) break;
		}
		if(ans) printf("\n");
		else printf("None.\n");
	}
}
