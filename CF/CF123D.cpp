#include<cstdio>
#include<cstring>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))

int n,top;
long long ans;
char s[maxn+5];
int fst[maxn+1],snd[2*maxn+1],tak[maxn+1];
int sa[maxn+1],rnk[maxn+1],het[maxn+1];
int p[maxn+1],q[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=122;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int mx=122,k=1;;k<<=1){
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
		for(re int i=1;i<=n;++i)
			fst[sa[i]]=fst[sa[i-1]]+(snd[sa[i]]!=snd[sa[i-1]]||snd[sa[i]+k]!=snd[sa[i-1]+k]);
		if(fst[sa[n]]==n)
			break;
		else
			mx=fst[sa[n]];
	}
	for(re int i=1;i<=n;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=n;++i)
		if(rnk[i]>1){
			j-=!!j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=n&&pos+j<=n&&s[i+j]==s[pos+j];++j);
			het[rnk[i]]=j;
		}
	het[0]=-1;
	for(re int i=1;i<=n;++i){
		re int tmp=0;
		for(;top&&het[i]<het[p[top]];
		ans+=1LL*(het[p[top]]-max(het[p[top-1]],het[i]))*(q[top]+tmp)*(q[top]+tmp+1)/2,tmp+=q[top],--top);
		if(het[i]>het[p[top]]){
			p[++top]=i;
			q[top]=tmp+1;
		}
		else
			q[top]+=tmp+1;
	}
	for(re int tmp=0;top;
	ans+=1LL*(het[p[top]]-het[p[top-1]])*(q[top]+tmp)*(q[top]+tmp+1)/2,tmp+=q[top],--top);
	printf("%lld",ans);
	return 0;
}
