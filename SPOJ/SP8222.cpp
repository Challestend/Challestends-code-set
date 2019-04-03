#include<cstdio>
#include<cstring>
#define re register
#define maxn 250000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

int n,top;
char s[maxn+5];
int fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[maxn+1],rnk[maxn+1],het[maxn+1];
int p[maxn+1],cnt[maxn+1],ans[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=122;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1,mx=122;;k<<=1,mx=fst[sa[n]]){
		re int cnt=0;
		for(re int i=n-k+1;i<=n;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=n;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=n;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=n;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=n;++i)
			snd[i]=fst[i];
		fst[sa[1]]=1;
		for(re int i=2;i<=n;++i)
			fst[sa[i]]=fst[sa[i-1]]+(snd[sa[i]]!=snd[sa[i-1]]||snd[sa[i]+k]!=snd[sa[i-1]+k]);
		if(fst[sa[n]]==n)
			break;
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
	for(re int i=1;i<=n;++i){
		re int tmp=0;
		for(;p[top]>het[i];ans[p[top]]=max(ans[p[top]],cnt[top]+tmp),tmp+=cnt[top],--top);
		if(p[top]<het[i]){
			p[++top]=het[i];
			cnt[top]=tmp+1;
		}
		else
			cnt[top]+=tmp+1;
	}
	for(re int tmp=0;top;ans[p[top]]=max(ans[p[top]],cnt[top]+tmp),tmp+=cnt[top],--top);
	for(re int i=1;i<=n;++i)
		printf("%d\n",ans[i]+1);
	return 0;
}
