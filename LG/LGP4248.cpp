#include<cstdio>
#include<cstring>
#define re register
#define maxn 500000

int n,mx;
char s[maxn+5];
int fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[2*maxn+1],rnk[maxn+1],het[maxn+1];
int p[maxn+1],q[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	mx=122;
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=n-k+1;i<=n;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=n;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=1;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=n;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=n;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=n;++i)
			snd[i]=fst[i];
		cnt=1;
		fst[sa[1]]=1;
		for(re int i=2;i<=n;++i)
			fst[sa[i]]=snd[sa[i]]==snd[sa[i-1]]&&snd[sa[i]+k]==snd[sa[i-1]+k]?cnt:++cnt;
		if(cnt==n)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=n;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=n;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=n&&pos+j<=n&&s[i+j]==s[pos+j];++j);
			het[rnk[i]]=j;
		}
	re long long res=0,ans=1LL*(n-1)*n*(n+1)/2;
	re int top=0;
	for(re int i=1;i<=n;++i){
		re int tmp=0;
		for(;top&&p[top]>=het[i];res-=1LL*q[top]*p[top],tmp+=q[top],--top);
		p[++top]=het[i];
		q[top]=tmp+1;
		res+=1LL*q[top]*p[top];
		ans-=2*res;
	}
	printf("%lld",ans);
	return 0;
}
