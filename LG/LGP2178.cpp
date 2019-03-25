#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 300000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define updmax(a,b,x) {if(x>a){b=a;a=x;}else{if(x>b)b=x;}}
#define updmin(a,b,x) {if(x<a){b=a;a=x;}else{if(x<b)b=x;}}
#define swap(a,b) a^=b,b^=a,a^=b

int n;
char s[maxn+5];
int a[maxn+1];
int fst[maxn+1],snd[2*maxn+1],tak[maxn+1];
int sa[maxn+1],rnk[maxn+1],het[maxn+1];
int f[maxn+1],size[maxn+1],l1[maxn+1],l2[maxn+1],s1[maxn+1],s2[maxn+1],p[maxn+1],mrk[maxn+1];
long long sum[maxn+1],ans[maxn+1];

inline bool cmp(re int p1,re int p2){
	return het[p1]>het[p2];
}

int find(re int x){
	return f[x]==x?f[x]:f[x]=find(f[x]);
}

inline long long merge(re int x,re int y){
	if(find(x)!=find(y)){
		x=f[x];
		y=f[y];
		if(x<y)
			swap(x,y);
		f[x]=y;
		size[y]+=size[x];
		updmax(l1[y],l2[y],l1[x]);
		updmax(l1[y],l2[y],l2[x]);
		updmin(s1[y],s2[y],s1[x]);
		updmin(s1[y],s2[y],s2[x]);
		return 1LL*size[x]*(size[y]-size[x]);
	}
	else
		return 0;
}

int main(){
	scanf("%d%s",&n,s+1);
	for(re int i=1;i<=n;++i)
		scanf("%d",&a[i]);
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
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=n&&pos+j<=n&&s[i+j]==s[pos+j];++j);
			het[rnk[i]]=j;
		}
	for(re int i=2;i<=n;++i){
		f[i]=i;
		size[i]=1;
		l1[i]=a[sa[i]];
		l2[i]=-2E9;
		s1[i]=a[sa[i]];
		s2[i]=2E9;
		p[i-1]=i;
	}
	std::sort(p+1,p+n,cmp);
	ans[het[p[1]]]=-9E18;
	for(re int i=1;i<n;++i){
		++mrk[p[i]];
		++sum[het[p[i]]];
		if(p[i]>2&&mrk[p[i]-1])
			sum[het[p[i]]]+=merge(p[i]-1,p[i]);
		if(p[i]<n&&mrk[p[i]+1])
			sum[het[p[i]]]+=merge(p[i]+1,p[i]);
		find(p[i]);
		l1[0]=l1[f[p[i]]];
		l2[0]=l2[f[p[i]]];
		s1[0]=s1[f[p[i]]];
		s2[0]=s2[f[p[i]]];
		updmax(l1[0],l2[0],a[sa[f[p[i]]-1]]);
		updmin(s1[0],s2[0],a[sa[f[p[i]]-1]]);
		ans[het[p[i]]]=max(ans[het[p[i]]],max(1LL*l1[0]*l2[0],1LL*s1[0]*s2[0]));
		if(het[p[i+1]]<het[p[i]]){
			sum[het[p[i+1]]]=sum[het[p[i]]];
			ans[het[p[i+1]]]=ans[het[p[i]]];
		}
	}
	for(re int i=0;i<n;++i)
		printf("%lld %lld\n",sum[i],ans[i]);
	return 0;
}
