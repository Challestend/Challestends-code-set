#include<cstdio>
#include<cstring>
#define re register
#define maxn 200000

int n,N,mx;
char s[maxn+5];
int sa[2*maxn+1],fst[maxn+1],sec[maxn+1],tak[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(re int i=1;i<=n;++i)
		s[n+i]=s[i];
	N=n<<1;
	mx=256;
	for(re int i=1;i<=N;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=mx;++i)
		tak[i]+=tak[i-1];
	for(re int i=N;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1;;k<<=1){
		re int cnt=0;
		for(re int i=N-k+1;i<=N;++i)
			sec[++cnt]=i;
		for(re int i=1;i<=N;++i)
			if(sa[i]>k)
				sec[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=N;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=N;i>=1;--i)
			sa[tak[fst[sec[i]]]--]=sec[i];
		for(re int i=1;i<=N;++i)
			sec[i]=fst[i];
		fst[sa[1]]=1;
		cnt=1;
		for(re int i=2;i<=N;++i)
			fst[sa[i]]=sec[sa[i]]==sec[sa[i-1]]&&sec[sa[i]+k]==sec[sa[i-1]+k]?cnt:++cnt;
		if(cnt==N)
			break;
		else
			mx=cnt;
	}
	for(re int i=1;i<=N;++i)
		if(sa[i]>1&&sa[i]<=n+1)
			putchar(s[sa[i]+n-1]);
	return 0;
}
