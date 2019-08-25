#include<cstdio>
#include<cstring>
#define re register
#define maxn 1048576
#define mod 998244353
#define swap(a,b) a^=b,b^=a,a^=b

int unit[2][24],rev[maxn],inv[maxn];
char s[maxn];
int n;
int F[maxn],G[maxn];

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;x=1LL*x*x%mod,y>>=1)
		if(y&1)
			res=1LL*res*x%mod;
	return res;
}

inline void NTT(re int* F,re int n,re int tp){
	for(re int i=0;i<n;++i)
		if(i<(rev[i]=(rev[i>>1]>>1)|((i&1)?(n>>1):0)))
			swap(F[i],F[rev[i]]);
	for(re int k=1,p=1;p<n;++k,p<<=1)
		for(re int i=0;i<n;i+=p<<1)
			for(re int j=i,tmp=1;j<i+p;++j,tmp=1LL*tmp*unit[tp][k]%mod){
				re int x=F[j],y=1LL*F[j+p]*tmp%mod;
				F[j]=(x+y)%mod;
				F[j+p]=(x-y+mod)%mod;
			}
	re int v=cltpow(n,tp*(mod-2));
	for(re int i=0;i<n;++i)
		F[i]=1LL*F[i]*v%mod;
}

int main(){
	unit[0][23]=cltpow(3,119);
	unit[1][23]=cltpow(332748118,119);
	for(re int i=0;i<2;++i)
		for(re int j=22;j>=0;--j)
			unit[i][j]=1LL*unit[i][j+1]*unit[i][j+1]%mod;
	scanf("%s",s);
	n=strlen(s);
	for(re int i=0;i<n;++i){
		F[i]=s[i]=='0';
		G[i]=s[i]=='1';
	}
	re int N=1;
	for(;N<(n<<1);N<<=1);
	NTT(F,N,0);
	NTT(G,N,0);
	for(re int i=0;i<N;++i)
		F[i]=1LL*F[i]*G[i]%mod;
	NTT(F,N,1);
	for(re int i=0;i<n;++i)
		printf("%d ",F[i]);
	puts("");
	re long long ans=0LL*n*n;
	for(re int i=0;i<n/2;++i)
		F[i]||(ans^=1LL*(i+1)*(i+1));
	for(re int i=1;i<(n+1)/2-1;++i){
		re int tmp=0;
		for(re int j=i;j<n;j+=i)
			tmp|=F[n-j-1]>0;
		tmp||(ans^=1LL*(n-i)*(n-i));
	}
	printf("%lld",ans);
	return 0;
}
