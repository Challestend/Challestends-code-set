#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 1000000

int n,mx;
char s[maxn+5];
int sa[2*maxn+1],x[maxn+1],y[maxn+1],c[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	mx=122;
	for(re int i=1;i<=n;++i)
		++c[x[i]=s[i]];
	for(re int i=1;i<=mx;++i)
		c[i]+=c[i-1];
	for(re int i=n;i>=1;--i)
		sa[c[x[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=n-k+1;i<=n;++i)
			y[++cnt]=i;
		for(re int i=1;i<=n;++i)
			if(sa[i]>k)
				y[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			c[i]=0;
		for(re int i=1;i<=n;++i)
			++c[x[i]];
		for(re int i=1;i<=mx;++i)
			c[i]+=c[i-1];
		for(re int i=n;i>=1;--i)
			sa[c[x[y[i]]]--]=y[i];
		for(re int i=1;i<=n;++i)
			y[i]=x[i];
		cnt=1;
		x[sa[1]]=1;
		for(re int i=2;i<=n;++i)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?cnt:++cnt;
		if(cnt==n)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=n;++i)
		printf("%d ",sa[i]);
}
