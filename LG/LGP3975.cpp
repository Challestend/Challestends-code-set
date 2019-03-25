#include<cstdio>
#include<cstring>
#define re register
#define maxn 500000
#define maxlog 19
#define min(a,b) ((a)<=(b)?(a):(b))
#define stmin(a,b) (min(st[a][lg[b-a+1]],st[b-(1<<lg[b-a+1])+1][lg[b-a+1]]))

int n,m,tp;
char s[maxn+5];
int fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[2*maxn+1],rnk[maxn+1],st[maxn+1][maxlog+1],lg[maxn+1];
long long len[maxn+1];

int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	scanf("%d %d",&tp,&m);
	for(re int i=1;i<=n;++i)
		++tak[fst[i]=s[i]];
	for(re int i=1;i<=122;++i)
		tak[i]+=tak[i-1];
	for(re int i=n;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1,mx=122;;k<<=1){
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
			st[rnk[i]][0]=j;
		}
	if(!tp){
		for(re int i=1;i<=n;++i)
			if(m>n-sa[i]-st[i][0]+1)
				m-=n-sa[i]-st[i][0]+1;
			else{
				for(re int j=1;j<=m+st[i][0];++j)
					putchar(s[sa[i]+j-1]);
				return 0;
			}
	}
	else{
		for(re int i=2;i<=n;++i)
			lg[i]=lg[i>>1]+1;
		for(re int i=1,p=1;i<=lg[n];++i,p<<=1)
			for(re int j=1;j+(p<<1)-1<=n;++j)
				st[j][i]=min(st[j][i-1],st[j+p][i-1]);
		for(re int i=1;i<=n;++i)
			len[i]=len[i-1]+n-sa[i]+1;
		for(re int i=1,j=1;i<=n;){
			if(st[i+1][0]>=j){
				re int l=i+1,r=n;
				for(;l<r;){
					re int mid=(l+r+1)>>1;
					if(stmin(i+1,mid)>=j)
						l=mid;
					else
						r=mid-1;
				}
				if(m>len[l]-len[i-1]+(l-i+1)*j){
					m-=len[l]-len[i-1]+(l-i+1)*j;
					i=l+1;
				}
				else{
					m-=l-i+1;
					++j;
				}
			}
			else{
				if(m>n-sa[i]-j+1){
					m-=n-sa[i]-j+1;
					++i;
				}
				else{
					for(re int k=1;k<m+j;++k)
						putchar(s[sa[i]+k-1]);
					return 0;
				}
			}
		}
	}
	printf("-1");
	return 0;
}
