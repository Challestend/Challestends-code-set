#include<cstdio>
#define re register
#define maxn 200
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
	#define size 1048576
	char cltin[size+1],*ih=cltin,*it=cltin;
	inline char gc(){
		#ifdef ONLINE_JUDGE
			if(ih==it){
				it=(ih=cltin)+fread(cltin,1,size,stdin);
				if(ih==it)
					return EOF;
			}
			return *ih++;
		#else
			return getchar();
		#endif
	}

	char cltout[size+1],*oh=cltout,*ot=cltout+size;
	inline void pc(char c){
		if(oh==ot){
			fwrite(cltout,1,size,stdout);
			oh=cltout;
		}
		*oh++=c;
	}
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout),cltstream::oh=cltstream::cltout
	#undef size

	template <typename _tp>
	inline void read(_tp& x){
		int sn=1;
		char c=gc();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
		if(c==45&&c!=EOF)
			sn=-1,c=gc();
		for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
		x*=sn;
	}

	template <typename _tp>
	inline void write(_tp x,char text=-1){
		if(x<0)
			pc(45),x=-x;
		if(!x)
			pc(48);
		else{
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

int n,m;
int a[maxn+1][maxn+1],dis[maxn+1][maxn+1],f[maxn+1],g[maxn+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n;++j)
			dis[i][j]=(i!=j)*1E9;
	for(re int i=1;i<=m;++i){
		int u,v,w;
		cltstream::read(u);
		cltstream::read(v);
		cltstream::read(w);
		a[u][v]=dis[u][v]=w;
		a[v][u]=dis[v][u]=w;
	}
	for(re int k=1;k<=n;++k)
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<=n;++j)
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	re int p=0,res=2E9;
	for(re int i=1;i<=n;res>f[i]&&(p=i,res=f[i]),++i)
		for(re int j=1;j<=n;++j)
			f[i]=max(f[i],dis[i][j]);
	re int ans=0;
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=n;++j){
			re int tmp=0;
			for(re int k=1;k<=n;++k)
				if(dis[p][i]==dis[p][k]+dis[k][i]&&dis[p][j]==dis[p][k]+dis[k][j])
					tmp=max(tmp,dis[p][k]);
			ans=max(ans,dis[p][i]+dis[p][j]-2*tmp);
		}
	printf("%0.16lf",ans/2.0);
	return 0;
}
